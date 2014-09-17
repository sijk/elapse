#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "elapse/elements/simple/eegfeaturextractor.h"

using testing::_;
using testing::Eq;
using testing::Return;
using namespace elapse;


class MockSimpleEegFeatEx : public elapse::elements::SimpleEegFeatureExtractor
{
public:
    MOCK_METHOD2(extractFeatures, std::vector<double>(const Eigen::MatrixXd &eeg, uint sampleRate));
    using SimpleEegFeatureExtractor::signalType;
};


TEST(SimpleEegFeatExTest, ConstructsCorrectEegMatrix)
{
    MockSimpleEegFeatEx fx;

    const uint nChan = 3;
    const uint nSamp = 5;
    const uint freq  = 250;
    Eigen::Matrix<double, nSamp, nChan> eeg;
    eeg << 00, 01, 02,
           10, 11, 12,
           20, 21, 22,
           30, 31, 32,
           40, 41, 42;

    EXPECT_CALL(fx, extractFeatures(Eq(eeg),freq))
            .WillOnce(Return(std::vector<double>{42}));

    const auto start = time::from_ms(1000);
    fx.setWindowLength(1000);
    fx.setWindowStep(500);
    fx.setStartTime(start);
    fx.configure({{"eeg", {{"sampleRate", freq}}}});

    for (uint i = 0; i < nSamp + 1; i++) {
        auto sample = data::EegSample::create();
        sample->timestamp = start + i * time::from_ms(1000 / nSamp);
        sample->seqnum = i;
        sample->values.reserve(nChan);
        for (uint j = 0; j < nChan; j++)
            sample->values.push_back(10 * i + j);

        fx.onSample(sample);
    }
}

TEST(SimpleEegFeatExTest, HasCorrectSignalType)
{
    MockSimpleEegFeatEx fx;
    EXPECT_EQ(fx.signalType(), data::Signal::EEG);
}
