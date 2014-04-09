#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "datasink.h"
#include "elapse/elements/datasinkdelegate.h"

using testing::_;
using testing::Return;
using testing::ReturnPointee;
using testing::Assign;
using testing::DoAll;


class MockDataSinkDelegate : public elapse::DataSinkDelegate
{
public:
    MOCK_METHOD0(start, bool());
    MOCK_METHOD0(stop, void());
    MOCK_METHOD0(needsNewSessionData, bool());
    MOCK_METHOD0(getSessionData, bool());
    MOCK_METHOD1(saveDeviceConfig, void(const QMap<QString,QVariantMap> &));
    MOCK_METHOD2(saveData, void(elapse::Signal::Type, QByteArray));
    MOCK_METHOD2(saveSample, void(elapse::Signal::Type, elapse::SamplePtr));
    MOCK_METHOD1(saveFeatureVector, void(elapse::FeatureVector));
    MOCK_METHOD1(saveCognitiveState, void(elapse::CognitiveState));
};


TEST(DataSinkTest, StartSucceedsIfSessionDataNotNeeded)
{
    MockDataSinkDelegate d;
    EXPECT_CALL(d, needsNewSessionData())
            .WillOnce(Return(false));
    EXPECT_CALL(d, start())
            .WillOnce(Return(true));

    DataSink sink;
    sink.setDelegate(&d);
    EXPECT_TRUE(sink.start());
}

TEST(DataSinkTest, StartFailsIfGetSessionDataFailed)
{
    MockDataSinkDelegate d;
    EXPECT_CALL(d, needsNewSessionData())
            .WillOnce(Return(true));
    EXPECT_CALL(d, getSessionData())
            .WillOnce(Return(false));

    DataSink sink;
    sink.setDelegate(&d);
    EXPECT_FALSE(sink.start());
}

TEST(DataSinkTest, StartFailsIfDelegateStartFails)
{
    MockDataSinkDelegate d;
    EXPECT_CALL(d, needsNewSessionData())
            .WillOnce(Return(true));
    EXPECT_CALL(d, getSessionData())
            .WillOnce(Return(true));
    EXPECT_CALL(d, start())
            .WillOnce(Return(false));

    DataSink sink;
    sink.setDelegate(&d);
    EXPECT_FALSE(sink.start());
}

TEST(DataSinkTest, StartSucceedsIfGetSessionDataAndDelegateStartSucceed)
{
    MockDataSinkDelegate d;
    EXPECT_CALL(d, needsNewSessionData())
            .WillOnce(Return(true));
    EXPECT_CALL(d, getSessionData())
            .WillOnce(Return(true));
    EXPECT_CALL(d, start())
            .WillOnce(Return(true));

    DataSink sink;
    sink.setDelegate(&d);
    EXPECT_TRUE(sink.start());
}

TEST(DataSinkTest, NewSessionDataEachTime)
{
    // Test the behaviour of the DataSink with a delegate that requires
    // getSessionData() to be called before every run.

    bool needsData = true;
    MockDataSinkDelegate d;
    EXPECT_CALL(d, needsNewSessionData())
            .Times(2)
            .WillRepeatedly(ReturnPointee(&needsData));
    EXPECT_CALL(d, getSessionData())
            .Times(2)
            .WillRepeatedly(DoAll(Assign(&needsData, false), Return(true)));
    EXPECT_CALL(d, start())
            .Times(2)
            .WillRepeatedly(Return(true));
    EXPECT_CALL(d, stop())
            .WillRepeatedly(Assign(&needsData, true));

    DataSink sink;
    sink.setDelegate(&d);

    EXPECT_TRUE(sink.start());
    EXPECT_FALSE(needsData);
    sink.stop();
    EXPECT_TRUE(needsData);
    EXPECT_TRUE(sink.start());
}

TEST(DataSinktest, DelegateSaveNotCalledWhenDisabled)
{
    MockDataSinkDelegate d;
    EXPECT_CALL(d, saveData(_,_)).Times(0);
    EXPECT_CALL(d, saveSample(_,_)).Times(0);
    EXPECT_CALL(d, saveFeatureVector(_)).Times(0);
    EXPECT_CALL(d, saveCognitiveState(_)).Times(0);

    DataSink sink;
    sink.setDelegate(&d);

    sink.setSaveData(false);
    sink.setSaveSamples(false);
    sink.setSaveFeatureVectors(false);
    sink.setSaveCognitiveState(false);

    sink.onData("");
    sink.onSample(elapse::SamplePtr(new elapse::EegSample()));
    sink.onFeatureVector(elapse::FeatureVector(elapse::Signal::EEG, 0));
    sink.onCognitiveState(elapse::CognitiveState(0));
}

TEST(DataSinktest, DelegateSaveCalledWhenEnabled)
{
    MockDataSinkDelegate d;
//    EXPECT_CALL(d, saveData(_,_)).Times(1);
    EXPECT_CALL(d, saveSample(_,_)).Times(1);
    EXPECT_CALL(d, saveFeatureVector(_)).Times(1);
    EXPECT_CALL(d, saveCognitiveState(_)).Times(1);

    DataSink sink;
    sink.setDelegate(&d);

    sink.setSaveData(true);
    sink.setSaveSamples(true);
    sink.setSaveFeatureVectors(true);
    sink.setSaveCognitiveState(true);

    // Can't test onData() since it must only be called by a DataSource signal
//    sink.onData("");
    sink.onSample(elapse::SamplePtr(new elapse::EegSample()));
    sink.onFeatureVector(elapse::FeatureVector(elapse::Signal::EEG, 0));
    sink.onCognitiveState(elapse::CognitiveState(0));
}

