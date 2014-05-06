#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QPointer>
#include <QSignalSpy>
#include <elapse/elements/datasource.h>
#include <elapse/elements/decoder.h>
#include <elapse/elements/featurextractor.h>
#include <elapse/elements/classifier.h>
#include <elapse/elements/outputaction.h>
#include <elapse/elements/datasinkdelegate.h>
#include "elementset.h"
#include "pipeline.h"
#include "featurextractor_p.h"
#include "../test_utils.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AnyNumber;
using ::testing::InSequence;
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

template<typename SampleType = elapse::Sample>
elapse::SamplePtr createSample(quint64 time)
{
    SampleType *sample = new SampleType;
    sample->timestamp = time * 1e6;
    return elapse::SamplePtr(sample);
}

template<typename SampleType>
elapse::SamplePtr createSample(const QByteArray &data)
{
    return createSample<SampleType>(data.toULongLong());
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
    MOCK_METHOD0(reset, void());

    MockFeatureExtractor()
    {
        ON_CALL(*this, setStartTime(_))
                .WillByDefault(Invoke(this, &MockFeatureExtractor::_setStartTime));
        ON_CALL(*this, reset())
                .WillByDefault(Invoke(this, &MockFeatureExtractor::_reset));
    }

    void _setStartTime(quint64 time)
    {
        BaseFeatureExtractor::setStartTime(time);
    }

    void _reset()
    {
        EXPECT_CALL(*this, removeDataBefore(_));
        BaseFeatureExtractor::reset();
    }

    void ignoreCalls()
    {
        EXPECT_CALL(*this, analyseSample(_)).Times(AnyNumber());
        EXPECT_CALL(*this, features()).Times(AnyNumber());
        EXPECT_CALL(*this, removeDataBefore(_)).Times(AnyNumber());
        EXPECT_CALL(*this, setStartTime(_)).Times(AnyNumber());
        EXPECT_CALL(*this, reset()).Times(AnyNumber());
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

class MockOutputAction : public elapse::OutputAction
{
    Q_OBJECT
public:
    MOCK_METHOD1(onState, void(elapse::CognitiveState));
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
        action = new MockOutputAction;
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
        elements->action = action;
        elements->dataSink = dataSink;

        eegFeatExPriv = elapse::BaseFeatureExtractorPrivate::expose(eegFeatEx);
        vidFeatExPriv = elapse::BaseFeatureExtractorPrivate::expose(vidFeatEx);
        imuFeatExPriv = elapse::BaseFeatureExtractorPrivate::expose(imuFeatEx);
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
    QPointer<MockOutputAction> action;
    QPointer<MockDataSinkDelegate> dataSink;

    elapse::BaseFeatureExtractorPrivate *eegFeatExPriv;
    elapse::BaseFeatureExtractorPrivate *vidFeatExPriv;
    elapse::BaseFeatureExtractorPrivate *imuFeatExPriv;

    ElementSetPtr elements;
    Pipeline pipeline;

    SuppressLogging nolog;

    void expectPipelineStart()
    {
        InSequence s;
        EXPECT_CALL(*dataSink, start());
        EXPECT_CALL(*classifier, reset());
        EXPECT_CALL(*dataSource, start());
        pipeline.start();
    }

    void expectPipelineStop()
    {
        InSequence s;
        EXPECT_CALL(*dataSource, stop());
        EXPECT_CALL(*dataSink, stop());
        pipeline.stop();
    }

    void expectFirstSampleWithTimestamp(quint64 time)
    {
        const quint64 startTime = time * 1e6 + 1e9;

        {
            InSequence eeg;
            EXPECT_CALL(*eegDecoder, onData(_));
            EXPECT_CALL(*eegFeatEx, setStartTime(startTime));
            EXPECT_CALL(*eegFeatEx, reset());
        }
        {
            InSequence vid;
            EXPECT_CALL(*vidFeatEx, setStartTime(startTime));
            EXPECT_CALL(*vidFeatEx, reset());
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuFeatEx, setStartTime(startTime));
            EXPECT_CALL(*imuFeatEx, reset());
        }

        dataSource->emitEeg(time);

        EXPECT_EQ(eegFeatExPriv->windowStart, startTime);
        EXPECT_EQ(vidFeatExPriv->windowStart, startTime);
        EXPECT_EQ(imuFeatExPriv->windowStart, startTime);
    }
};


/*
 * Test BaseFeatureExtractor's windowing algorithm without a Pipeline
 */
TEST_F(PipelineTest, BaseFeatureExtractorWindowing)
{
    EXPECT_CALL(*eegFeatEx, reset());
    EXPECT_CALL(*eegFeatEx, setStartTime(1010e6));
    eegFeatEx->setStartTime(1010e6);
    eegFeatEx->setWindowLength(1000);
    eegFeatEx->setWindowStep(500);

    eegFeatEx->onSample(createSample(10));
    eegFeatEx->onSample(createSample(1000));

    EXPECT_CALL(*eegFeatEx, analyseSample(_)).Times(2);

    eegFeatEx->onSample(createSample(1010));
    eegFeatEx->onSample(createSample(1020));

    QVector<double> features = { 1, 2, 3 };
    EXPECT_CALL(*eegFeatEx, features()).WillOnce(Return(features));
    EXPECT_CALL(*eegFeatEx, removeDataBefore(_));
    EXPECT_CALL(*eegFeatEx, analyseSample(_));

    eegFeatEx->onSample(createSample(2010));
}

/*
 * Test BaseFeatureExtractor's windowing algorithm with a Pipeline
 */
TEST_F(PipelineTest, BaseFeatureExtractorWindowingInPipeline)
{
    pipeline.setElements(elements);
    pipeline.setWindowLength(1000);
    pipeline.setWindowStep(500);
    dataSink->ignoreCalls();
    expectPipelineStart();
    EXPECT_CALL(*eegDecoder, onData(_)).Times(5);

    // Before start time
    {
        EXPECT_CALL(*eegFeatEx, reset());
        EXPECT_CALL(*eegFeatEx, setStartTime(1010e6));
        EXPECT_CALL(*vidFeatEx, reset());
        EXPECT_CALL(*vidFeatEx, setStartTime(1010e6));
        EXPECT_CALL(*imuFeatEx, reset());
        EXPECT_CALL(*imuFeatEx, setStartTime(1010e6));

        dataSource->emitEeg(10);
        dataSource->emitEeg(1000);
    }

    // After start time, within first window
    {
        EXPECT_CALL(*eegFeatEx, analyseSample(_)).Times(2);

        dataSource->emitEeg(1010);
        dataSource->emitEeg(1020);
    }

    // After first window
    {
        QVector<double> features = { 1, 2, 3 };
        EXPECT_CALL(*eegFeatEx, features()).WillOnce(Return(features));
        EXPECT_CALL(*eegFeatEx, removeDataBefore(_));
        EXPECT_CALL(*eegFeatEx, analyseSample(_));

        dataSource->emitEeg(2010);
    }
}

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

TEST_F(PipelineTest, IgnoreSamplesBeforeStartTime)
{
    dataSink->ignoreCalls();

    QSignalSpy error(&pipeline, SIGNAL(error(QString)));
    pipeline.setElements(elements);
    pipeline.setWindowLength(1000);
    pipeline.setWindowStep(500);

    // We'll set the start time and then simulate a bunch of samples with
    // timestamps before the start time. They should all be discarded, so
    // should never reach the feature extractors or beyond.
    EXPECT_CALL(*classifier, classify(_)).Times(0);
    EXPECT_CALL(*action, onState(_)).Times(0);

    expectPipelineStart();
    expectFirstSampleWithTimestamp(10);

    // A bunch more samples before startTime: should all be discarded
    {
        EXPECT_CALL(*eegDecoder, onData(_)).Times(99);
        EXPECT_CALL(*vidDecoder, onData(_)).Times(99);
        EXPECT_CALL(*imuDecoder, onData(_)).Times(99);

        for (uint time = 20; time < 1010; time += 10) {
            dataSource->emitEeg(time);
            dataSource->emitVid(time);
            dataSource->emitImu(time);
        }
    }

    // More samples after startTime but before first windowEnd: should be
    // analysed but no feature vectors yet
    {
        EXPECT_CALL(*eegDecoder, onData(_)).Times(100);
        EXPECT_CALL(*vidDecoder, onData(_)).Times(100);
        EXPECT_CALL(*imuDecoder, onData(_)).Times(100);
        EXPECT_CALL(*eegFeatEx, analyseSample(_)).Times(100);
        EXPECT_CALL(*vidFeatEx, analyseSample(_)).Times(100);
        EXPECT_CALL(*imuFeatEx, analyseSample(_)).Times(100);

        for (uint time = 1010; time < 2010; time += 10) {
            dataSource->emitEeg(time);
            dataSource->emitVid(time);
            dataSource->emitImu(time);
        }
    }

    expectPipelineStop();
    EXPECT_EQ(error.count(), 0);
}

TEST_F(PipelineTest, FeatureExtractorWindowing)
{
    QVector<double> features = { 1, 2, 3 };
    elapse::CognitiveState state = { 42 };

    EXPECT_CALL(*dataSink, saveData(_,_)).Times(13);
    EXPECT_CALL(*dataSink, saveSample(_,_)).Times(13);
    EXPECT_CALL(*dataSink, saveFeatureVector(_)).Times(6);
    EXPECT_CALL(*dataSink, saveCognitiveState(_)).Times(2);

    QSignalSpy error(&pipeline, SIGNAL(error(QString)));
    pipeline.setElements(elements);
    pipeline.setWindowLength(1000);
    pipeline.setWindowStep(500);

    expectPipelineStart();

    // Simulate 5 samples. First is used to set start time, then discarded.
    // Subsequent ones form two (and a half) windows.
    //
    //  1  2  3  4  5
    //  X
    //    |----|
    //       |----|

    // 1: set start time, reset state, discard sample
    expectFirstSampleWithTimestamp(10);

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

        dataSource->emitEeg(1500);
        dataSource->emitVid(1500);
        dataSource->emitImu(1500);
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

        dataSource->emitEeg(2000);
        dataSource->emitVid(2000);
        dataSource->emitImu(2000);
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
            EXPECT_CALL(*eegFeatEx, removeDataBefore(1510e6));
            EXPECT_CALL(*eegFeatEx, analyseSample(_));
        }
        {
            InSequence video;
            EXPECT_CALL(*vidDecoder, onData(_));
            EXPECT_CALL(*vidFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*vidFeatEx, removeDataBefore(1510e6));
            EXPECT_CALL(*vidFeatEx, analyseSample(_));
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuDecoder, onData(_));
            EXPECT_CALL(*imuFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*imuFeatEx, removeDataBefore(1510e6));
            EXPECT_CALL(*imuFeatEx, analyseSample(_));
        }

        EXPECT_CALL(*classifier, classify(_)).WillOnce(Return(state));
        EXPECT_CALL(*action, onState(_));

        dataSource->emitEeg(2500);
        dataSource->emitVid(2500);
        dataSource->emitImu(2500);

        EXPECT_EQ(eegFeatExPriv->windowStart, 1510e6);
        EXPECT_EQ(vidFeatExPriv->windowStart, 1510e6);
        EXPECT_EQ(imuFeatExPriv->windowStart, 1510e6);
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
            EXPECT_CALL(*eegFeatEx, removeDataBefore(2010e6));
            EXPECT_CALL(*eegFeatEx, analyseSample(_));
        }
        {
            InSequence video;
            EXPECT_CALL(*vidDecoder, onData(_));
            EXPECT_CALL(*vidFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*vidFeatEx, removeDataBefore(2010e6));
            EXPECT_CALL(*vidFeatEx, analyseSample(_));
        }
        {
            InSequence imu;
            EXPECT_CALL(*imuDecoder, onData(_));
            EXPECT_CALL(*imuFeatEx, features()).WillOnce(Return(features));
            EXPECT_CALL(*imuFeatEx, removeDataBefore(2010e6));
            EXPECT_CALL(*imuFeatEx, analyseSample(_));
        }

        EXPECT_CALL(*classifier, classify(_)).WillOnce(Return(state));
        EXPECT_CALL(*action, onState(_));

        dataSource->emitEeg(3000);
        dataSource->emitVid(3000);
        dataSource->emitImu(3000);

        EXPECT_EQ(eegFeatExPriv->windowStart, 2010e6);
        EXPECT_EQ(vidFeatExPriv->windowStart, 2010e6);
        EXPECT_EQ(imuFeatExPriv->windowStart, 2010e6);
    }

    expectPipelineStop();
    EXPECT_EQ(error.count(), 0);
}

TEST_F(PipelineTest, FeatureExtractorWindowingWithDelay)
{
    QVector<double> features = { 1, 2, 3 };
    elapse::CognitiveState state = { 42 };

    dataSink->ignoreCalls();
    QSignalSpy error(&pipeline, SIGNAL(error(QString)));
    pipeline.setElements(elements);
    pipeline.setWindowLength(1000);
    pipeline.setWindowStep(500);

    expectPipelineStart();

    // 1: set start time, reset state, discard sample
    expectFirstSampleWithTimestamp(10);

    // Expected window bounds
    const uint w1start = 1010, w1end = 2010;
    const uint w2start = 1510, w2end = 2510;
    const uint w3start = 2010, w3end = 3010;
    const uint w4start = 2510, w4end = 3510;
    const uint w5start = 3010, w5end = 4010;
    const uint w6start = 3510;

    // 2: A bunch of EEG samples spanning five windows:
    //
    //   1   |----|
    //   2      |----|
    //   3         |----|
    //   4            |----|
    //   5               |----|
    //  EEG  xxxxxxxxxxxxxxxxxx
    //  VID
    //  IMU
    {
        EXPECT_CALL(*eegDecoder, onData(_)).Times(301);
        EXPECT_CALL(*eegFeatEx, analyseSample(_)).Times(301);
        EXPECT_CALL(*eegFeatEx, features()).Times(5).WillRepeatedly(Return(features));
        EXPECT_CALL(*eegFeatEx, removeDataBefore(_)).Times(5);

        for (uint time = w1start; time <= w5end; time += 10)
            dataSource->emitEeg(time);

        EXPECT_EQ(eegFeatExPriv->windowStart, w6start * 1e6);
        EXPECT_EQ(vidFeatExPriv->windowStart, w1start * 1e6);
        EXPECT_EQ(imuFeatExPriv->windowStart, w1start * 1e6);
    }

    // 3: IMU samples in first window
    //
    //   1   |----|
    //   2      |----|
    //   3         |----|
    //   4            |----|
    //   5               |----|
    //  EEG  xxxxxxxxxxxxxxxxxx
    //  VID
    //  IMU  xxxxxx
    {
        EXPECT_CALL(*imuDecoder, onData(_)).Times(11);
        EXPECT_CALL(*imuFeatEx, analyseSample(_)).Times(11);
        EXPECT_CALL(*imuFeatEx, features()).WillOnce(Return(features));
        EXPECT_CALL(*imuFeatEx, removeDataBefore(_));

        for (uint time = w1start; time <= w1end; time += 100)
            dataSource->emitImu(time);

        EXPECT_EQ(eegFeatExPriv->windowStart, w6start * 1e6);
        EXPECT_EQ(vidFeatExPriv->windowStart, w1start * 1e6);
        EXPECT_EQ(imuFeatExPriv->windowStart, w2start * 1e6);
    }

    // 4: Video samples in first three windows. This completes the FeatureSet
    //    for the first window, so it will be classified.
    //
    //   1   |----|
    //   2      |----|
    //   3         |----|
    //   4            |----|
    //   5               |----|
    //  EEG  xxxxxxxxxxxxxxxxxx
    //  VID  xxxxxxxxxxxx
    //  IMU  xxxxxx
    {
        EXPECT_CALL(*classifier, classify(_)).WillOnce(Return(state));
        EXPECT_CALL(*action, onState(_));

        EXPECT_CALL(*vidDecoder, onData(_)).Times(81);
        EXPECT_CALL(*vidFeatEx, analyseSample(_)).Times(81);
        EXPECT_CALL(*vidFeatEx, features()).Times(3).WillRepeatedly(Return(features));
        EXPECT_CALL(*vidFeatEx, removeDataBefore(_)).Times(3);

        for (uint time = w1start; time <= w3end; time += 25)
            dataSource->emitVid(time);

        EXPECT_EQ(eegFeatExPriv->windowStart, w6start * 1e6);
        EXPECT_EQ(vidFeatExPriv->windowStart, w4start * 1e6);
        EXPECT_EQ(imuFeatExPriv->windowStart, w2start * 1e6);
    }

    // 5: IMU sample after third window. Should finish second window
    //    and jump straight to start of fourth.
    //
    //   1   |----|
    //   2      |----|
    //   3         |----|
    //   4            |----|
    //   5               |----|
    //  EEG  xxxxxxxxxxxxxxxxxx
    //  VID  xxxxxxxxxxxx
    //  IMU  xxxxxx      x
    {
        EXPECT_CALL(*classifier, classify(_)).WillOnce(Return(state));
        EXPECT_CALL(*action, onState(_));

        EXPECT_CALL(*imuDecoder, onData(_));
        EXPECT_CALL(*imuFeatEx, analyseSample(_));
        EXPECT_CALL(*imuFeatEx, features()).WillOnce(Return(features));
        EXPECT_CALL(*imuFeatEx, removeDataBefore(_));

        dataSource->emitImu(w3end + 100);

        EXPECT_EQ(eegFeatExPriv->windowStart, w6start * 1e6);
        EXPECT_EQ(vidFeatExPriv->windowStart, w4start * 1e6);
        EXPECT_EQ(imuFeatExPriv->windowStart, w4start * 1e6);
    }

    expectPipelineStop();
    EXPECT_EQ(error.count(), 0);
}

#include "pipeline_test.moc"

