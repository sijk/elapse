#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "elapse/elements/datasink.h"

using testing::_;
using testing::Return;
using testing::ReturnPointee;
using testing::Assign;
using testing::DoAll;


class MockDataSink : public elapse::DataSink
{
public:
    MOCK_METHOD0(startSaving, bool());
    MOCK_METHOD0(stopSaving, void());
    MOCK_METHOD0(needsNewCaptureInfo, bool());
    MOCK_METHOD0(getCaptureInfo, bool());
    MOCK_METHOD1(saveDeviceConfig, void(const QMap<QString,QVariantMap> &));
    MOCK_METHOD2(saveData, void(elapse::data::Signal::Type, QByteArray));
    MOCK_METHOD2(saveSample, void(elapse::data::Signal::Type, elapse::data::SamplePtr));
    MOCK_METHOD1(saveFeatureVector, void(elapse::data::FeatureVector));
    MOCK_METHOD1(saveCognitiveState, void(elapse::data::CognitiveState));
};


TEST(DataSinkTest, StartSucceedsIfCaptureInfoNotNeeded)
{
    MockDataSink sink;
    EXPECT_CALL(sink, needsNewCaptureInfo())
            .WillOnce(Return(false));
    EXPECT_CALL(sink, startSaving())
            .WillOnce(Return(true));

    EXPECT_TRUE(sink.start());
}

TEST(DataSinkTest, StartFailsIfGetCaptureInfoFailed)
{
    MockDataSink sink;
    EXPECT_CALL(sink, needsNewCaptureInfo())
            .WillOnce(Return(true));
    EXPECT_CALL(sink, getCaptureInfo())
            .WillOnce(Return(false));

    EXPECT_FALSE(sink.start());
}

TEST(DataSinkTest, StartFailsIfStartSavingFails)
{
    MockDataSink sink;
    EXPECT_CALL(sink, needsNewCaptureInfo())
            .WillOnce(Return(true));
    EXPECT_CALL(sink, getCaptureInfo())
            .WillOnce(Return(true));
    EXPECT_CALL(sink, startSaving())
            .WillOnce(Return(false));

    EXPECT_FALSE(sink.start());
}

TEST(DataSinkTest, StartSucceedsIfGetCaptureInfoAndStartSavingSucceed)
{
    MockDataSink sink;
    EXPECT_CALL(sink, needsNewCaptureInfo())
            .WillOnce(Return(true));
    EXPECT_CALL(sink, getCaptureInfo())
            .WillOnce(Return(true));
    EXPECT_CALL(sink, startSaving())
            .WillOnce(Return(true));

    EXPECT_TRUE(sink.start());
}

TEST(DataSinkTest, NewCaptureInfoEachTime)
{
    // Test the behaviour of a DataSink that requires
    // getCaptureInfo() to be called before every run.

    bool needsData = true;
    MockDataSink sink;
    EXPECT_CALL(sink, needsNewCaptureInfo())
            .Times(2)
            .WillRepeatedly(ReturnPointee(&needsData));
    EXPECT_CALL(sink, getCaptureInfo())
            .Times(2)
            .WillRepeatedly(DoAll(Assign(&needsData, false), Return(true)));
    EXPECT_CALL(sink, startSaving())
            .Times(2)
            .WillRepeatedly(Return(true));
    EXPECT_CALL(sink, stopSaving())
            .WillRepeatedly(Assign(&needsData, true));

    EXPECT_TRUE(sink.start());
    EXPECT_FALSE(needsData);
    sink.stop();
    EXPECT_TRUE(needsData);
    EXPECT_TRUE(sink.start());
}

