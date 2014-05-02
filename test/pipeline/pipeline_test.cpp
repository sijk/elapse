#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QPointer>
#include <QSignalSpy>
#include <elapse/elements/datasource.h>
#include <elapse/elements/decoder.h>
#include <elapse/elements/featurextractor.h>
#include <elapse/elements/classifier.h>
#include <elapse/elements/datasinkdelegate.h>
#include "elementset.h"
#include "pipeline.h"
#include "../test_utils.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AnyNumber;
using ::testing::InSequence;
//using ::testing::ExpectationSet;
using ::elapse::Signal;


class MockDataSource : public elapse::DataSource
{
    Q_OBJECT
public:
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(stop, void());

    void emitEeg(quint64 timestamp)
    {
        emit eegReady(QByteArray::number(timestamp));
    }

    void emitVid(quint64 timestamp)
    {
        emit videoReady(QByteArray::number(timestamp));
    }

    void emitImu(quint64 timestamp)
    {
        emit imuReady(QByteArray::number(timestamp));
    }
};

template<typename SampleType>
elapse::SamplePtr createSample(const QByteArray &data)
{
    SampleType *sample = new SampleType;
    sample->timestamp = data.toULongLong() * 1e6;
    return elapse::SamplePtr(sample);
}

class MockEegDecoder : public elapse::SampleDecoder
{
    Q_OBJECT
public:
    MOCK_METHOD1(onData, void(QByteArray));

    MockEegDecoder()
    {
        ON_CALL(*this, onData(_))
                .WillByDefault(Invoke(this, &MockEegDecoder::handleData));
    }

    void handleData(QByteArray data)
    {
        emit newSample(createSample<elapse::EegSample>(data));
    }
};

class MockVidDecoder : public elapse::SampleDecoder
{
    Q_OBJECT
public:
    MOCK_METHOD1(onData, void(QByteArray));

    MockVidDecoder()
    {
        ON_CALL(*this, onData(_))
                .WillByDefault(Invoke(this, &MockVidDecoder::handleData));
    }

    void handleData(QByteArray data)
    {
        emit newSample(createSample<elapse::VideoSample>(data));
    }
};

class MockImuDecoder : public elapse::SampleDecoder
{
    Q_OBJECT
public:
    MOCK_METHOD1(onData, void(QByteArray));

    MockImuDecoder()
    {
        ON_CALL(*this, onData(_))
                .WillByDefault(Invoke(this, &MockImuDecoder::handleData));
    }

    void handleData(QByteArray data)
    {
        emit newSample(createSample<elapse::ImuSample>(data));
    }
};

class MockFeatureExtractor : public elapse::BaseFeatureExtractor
{
    Q_OBJECT
public:
    MOCK_METHOD1(analyseSample, void(elapse::SamplePtr));
    MOCK_METHOD0(features, QVector<double>());
    MOCK_METHOD1(removeDataBefore, void(quint64));
    MOCK_METHOD1(setStartTime, void(quint64));

    MockFeatureExtractor()
    {
        ON_CALL(*this, setStartTime(_))
                .WillByDefault(Invoke(this, &MockFeatureExtractor::_setStartTime));
    }

    void _setStartTime(quint64 time)
    {
        BaseFeatureExtractor::setStartTime(time);
    }

    void ignoreCalls()
    {
        EXPECT_CALL(*this, analyseSample(_)).Times(AnyNumber());
        EXPECT_CALL(*this, features()).Times(AnyNumber());
        EXPECT_CALL(*this, removeDataBefore(_)).Times(AnyNumber());
        EXPECT_CALL(*this, setStartTime(_)).Times(AnyNumber());
    }
};

class MockEegFeatureExtractor : public MockFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")
};

class MockVidFeatureExtractor : public MockFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "VIDEO")
};

class MockImuFeatureExtractor : public MockFeatureExtractor
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "IMU")
};

class MockClassifier : public elapse::BaseClassifier
{
    Q_OBJECT
public:
    MOCK_METHOD1(classify, elapse::CognitiveState(QList<elapse::FeatureVector>));
    MOCK_METHOD0(reset, void());

    MockClassifier()
    {
        ON_CALL(*this, reset())
                .WillByDefault(Invoke(this, &MockClassifier::_reset));
    }

    void _reset()
    {
        BaseClassifier::reset();
    }
};

class MockDataSinkDelegate : public elapse::DataSinkDelegate
{
    Q_OBJECT
public:
    MOCK_METHOD0(start, bool());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD0(needsNewSessionData, bool());
    MOCK_METHOD0(getSessionData, bool());
    MOCK_METHOD1(saveDeviceConfig, void(const QMap<QString, QVariantMap>&));
    MOCK_METHOD2(saveData, void(elapse::Signal::Type, QByteArray));
    MOCK_METHOD2(saveSample, void(elapse::Signal::Type, elapse::SamplePtr));
    MOCK_METHOD1(saveFeatureVector, void(elapse::FeatureVector));
    MOCK_METHOD1(saveCognitiveState, void(elapse::CognitiveState));

    MockDataSinkDelegate()
    {
        // Ignore session data calls - these are tested elsewhere.
        EXPECT_CALL(*this, needsNewSessionData()).WillRepeatedly(Return(false));
        EXPECT_CALL(*this, getSessionData()).Times(0);
        ON_CALL(*this, start()).WillByDefault(Return(true));
    }

    void ignoreCalls()
    {
        EXPECT_CALL(*this, start()).Times(AnyNumber());
        EXPECT_CALL(*this, stop()).Times(AnyNumber());
        EXPECT_CALL(*this, saveDeviceConfig(_)).Times(AnyNumber());
        EXPECT_CALL(*this, saveData(_,_)).Times(AnyNumber());
        EXPECT_CALL(*this, saveSample(_,_)).Times(AnyNumber());
        EXPECT_CALL(*this, saveFeatureVector(_)).Times(AnyNumber());
        EXPECT_CALL(*this, saveCognitiveState(_)).Times(AnyNumber());
    }
};


class PipelineTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        dataSource = new MockDataSource;
        eegDecoder = new MockEegDecoder;
        vidDecoder = new MockVidDecoder;
        imuDecoder = new MockImuDecoder;
        eegFeatEx = new MockEegFeatureExtractor;
        vidFeatEx = new MockVidFeatureExtractor;
        imuFeatEx = new MockImuFeatureExtractor;
        classifier = new MockClassifier;
        dataSink = new MockDataSinkDelegate;

        elements = ElementSetPtr::create();
        elements->dataSource = dataSource;
        elements->sampleDecoders[Signal::EEG] = eegDecoder;
        elements->sampleDecoders[Signal::VIDEO] = vidDecoder;
        elements->sampleDecoders[Signal::IMU] = imuDecoder;
        elements->featureExtractors[Signal::EEG] = eegFeatEx;
        elements->featureExtractors[Signal::VIDEO] = vidFeatEx;
        elements->featureExtractors[Signal::IMU] = imuFeatEx;
        elements->classifier = classifier;
        elements->dataSink = dataSink;
    }

public:
    QPointer<MockDataSource> dataSource;
    QPointer<MockEegDecoder> eegDecoder;
    QPointer<MockVidDecoder> vidDecoder;
    QPointer<MockImuDecoder> imuDecoder;
    QPointer<MockEegFeatureExtractor> eegFeatEx;
    QPointer<MockVidFeatureExtractor> vidFeatEx;
    QPointer<MockImuFeatureExtractor> imuFeatEx;
    QPointer<MockClassifier> classifier;
    QPointer<MockDataSinkDelegate> dataSink;

    ElementSetPtr elements;
    Pipeline pipeline;

    SuppressLogging nolog;
};


/*
 * Check that data emitted from the DataSource gets to the SampleDecoders
 * and the DataSinkDelegate.
 */
TEST_F(PipelineTest, DataSourceToDecodersAndSink)
{
    EXPECT_CALL(*classifier, reset()).Times(1);
    EXPECT_CALL(*dataSource, start()).Times(1);
    EXPECT_CALL(*dataSource, stop()).Times(1);

    EXPECT_CALL(*eegDecoder, onData(_)).Times(1);
    EXPECT_CALL(*vidDecoder, onData(_)).Times(1);
    EXPECT_CALL(*imuDecoder, onData(_)).Times(1);

    eegFeatEx->ignoreCalls();
    vidFeatEx->ignoreCalls();
    imuFeatEx->ignoreCalls();

    EXPECT_CALL(*dataSink, start()).Times(1);
    EXPECT_CALL(*dataSink, saveData(Signal::EEG,_)).Times(1);
    EXPECT_CALL(*dataSink, saveData(Signal::VIDEO,_)).Times(1);
    EXPECT_CALL(*dataSink, saveData(Signal::IMU,_)).Times(1);
    EXPECT_CALL(*dataSink, saveSample(Signal::EEG,_)).Times(1);
    EXPECT_CALL(*dataSink, saveSample(Signal::VIDEO,_)).Times(1);
    EXPECT_CALL(*dataSink, saveSample(Signal::IMU,_)).Times(1);
    EXPECT_CALL(*dataSink, stop()).Times(1);

    pipeline.setElements(elements);
    pipeline.start();

    dataSource->emitEeg(1);
    dataSource->emitVid(1);
    dataSource->emitImu(1);

    pipeline.stop();
}

TEST_F(PipelineTest, FeatureExtractorWindowing)
{
    QVector<double> features = { 1, 2, 3 };
    elapse::CognitiveState state = { 42 };

    EXPECT_CALL(*dataSink, saveData(_,_)).Times(15);
    EXPECT_CALL(*dataSink, saveSample(_,_)).Times(15);
    EXPECT_CALL(*dataSink, saveFeatureVector(_)).Times(6);
    EXPECT_CALL(*dataSink, saveCognitiveState(_)).Times(2);

    QSignalSpy error(&pipeline, SIGNAL(error(QString)));
    pipeline.setElements(elements);
    pipeline.setWindowLength(100);
    pipeline.setWindowStep(50);

    // Start pipeline
    {
        InSequence s;
        EXPECT_CALL(*dataSink, start());
        EXPECT_CALL(*classifier, reset());
        EXPECT_CALL(*dataSource, start());

        pipeline.start();
    }

    // Simulate 5 samples. First is used to set start time, then discarded.
    // Subsequent ones form two (and a half) windows.
    //
    //  1  2  3  4  5
    //  X
    //    |----|
    //       |----|

    // 1: set start time, reset state, discard sample
    {
        {
            InSequence eeg;

            // First sample: reset and set start time
            EXPECT_CALL(*eegDecoder, onData(_));
            EXPECT_CALL(*eegFeatEx, setStartTime(10e6 + 1e9));
            EXPECT_CALL(*eegFeatEx, removeDataBefore(_));
        }
        {
            InSequence vid;

            // Start time set by first EEG sample
            EXPECT_CALL(*vidFeatEx, setStartTime(10e6 + 1e9));
            EXPECT_CALL(*vidFeatEx, removeDataBefore(_));

            // First video sample
            EXPECT_CALL(*vidDecoder, onData(_));
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuFeatEx, setStartTime(10e6 + 1e9));
            EXPECT_CALL(*imuFeatEx, removeDataBefore(_));
            EXPECT_CALL(*imuDecoder, onData(_));
        }

        dataSource->emitEeg(10);
        dataSource->emitVid(30);
        dataSource->emitImu(20);
    }

    // 2: within first window: analyse
    {
        {
            InSequence eeg;
            EXPECT_CALL(*eegDecoder, onData(_));
            EXPECT_CALL(*eegFeatEx, analyseSample(_));
        }
        {
            InSequence vid;
            EXPECT_CALL(*vidDecoder, onData(_));
            EXPECT_CALL(*vidFeatEx, analyseSample(_));
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuDecoder, onData(_));
            EXPECT_CALL(*imuFeatEx, analyseSample(_));
        }

        dataSource->emitEeg(1050);
        dataSource->emitVid(1050);
        dataSource->emitImu(1050);
    }

    // 3: within first window: analyse
    {
        {
            InSequence eeg;
            EXPECT_CALL(*eegDecoder, onData(_));
            EXPECT_CALL(*eegFeatEx, analyseSample(_));
        }
        {
            InSequence video;
            EXPECT_CALL(*vidDecoder, onData(_));
            EXPECT_CALL(*vidFeatEx, analyseSample(_));
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuDecoder, onData(_));
            EXPECT_CALL(*imuFeatEx, analyseSample(_));
        }

        dataSource->emitEeg(1100);
        dataSource->emitVid(1100);
        dataSource->emitImu(1100);
    }

    // 4: past first window:
    //   - emit features for first window, classify
    //   - update window
    //   - analyse
    {
        {
            InSequence eeg;
            EXPECT_CALL(*eegDecoder, onData(_));
            EXPECT_CALL(*eegFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*eegFeatEx, removeDataBefore(1060e6));
            EXPECT_CALL(*eegFeatEx, analyseSample(_));
        }
        {
            InSequence video;
            EXPECT_CALL(*vidDecoder, onData(_));
            EXPECT_CALL(*vidFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*vidFeatEx, removeDataBefore(1060e6));
            EXPECT_CALL(*vidFeatEx, analyseSample(_));
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuDecoder, onData(_));
            EXPECT_CALL(*imuFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*imuFeatEx, removeDataBefore(1060e6));
            EXPECT_CALL(*imuFeatEx, analyseSample(_));
        }

        EXPECT_CALL(*classifier, classify(_)).WillOnce(Return(state));

        dataSource->emitEeg(1150);
        dataSource->emitVid(1150);
        dataSource->emitImu(1150);
    }

    // 5: past second window:
    //   - emit features for second window, classify
    //   - update window
    //   - analyse
    {
        {
            InSequence eeg;
            EXPECT_CALL(*eegDecoder, onData(_));
            EXPECT_CALL(*eegFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*eegFeatEx, removeDataBefore(1110e6));
            EXPECT_CALL(*eegFeatEx, analyseSample(_));
        }
        {
            InSequence video;
            EXPECT_CALL(*vidDecoder, onData(_));
            EXPECT_CALL(*vidFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*vidFeatEx, removeDataBefore(1110e6));
            EXPECT_CALL(*vidFeatEx, analyseSample(_));
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuDecoder, onData(_));
            EXPECT_CALL(*imuFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*imuFeatEx, removeDataBefore(1110e6));
            EXPECT_CALL(*imuFeatEx, analyseSample(_));
        }

        EXPECT_CALL(*classifier, classify(_)).WillOnce(Return(state));

        dataSource->emitEeg(1200);
        dataSource->emitVid(1200);
        dataSource->emitImu(1200);
    }

    // Stop pipeline
    {
        InSequence s;
        EXPECT_CALL(*dataSource, stop());
        EXPECT_CALL(*dataSink, stop());

        pipeline.stop();
    }

    EXPECT_EQ(error.count(), 0);
}


#include "pipeline_test.moc"

