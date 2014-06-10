#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "elapse/elements/featurextractor.h"

using namespace boost::python;


struct FeatureExtractorWrap : elapse::FeatureExtractor,
                              wrapper<elapse::FeatureExtractor>
{
    void setStartTime(elapse::TimeStamp timestamp) {
        this->get_override("setStartTime")(timestamp);
    }
    void setWindowLength(uint ms) {
        this->get_override("setWindowLength")(ms);
    }
    void setWindowStep(uint ms) {
        this->get_override("setWindowStep")(ms);
    }
    void onSample(elapse::SamplePtr sample) {
        this->get_override("onSample")(sample);
    }
};

class BaseFeatureExtractorPublic : public elapse::BaseFeatureExtractor
{
public:
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
    virtual void analyseSample(elapse::SamplePtr sample) = 0;
    virtual std::vector<double> features() = 0;
    virtual void removeDataBefore(elapse::TimeStamp time) = 0;
    virtual void reset() { elapse::BaseFeatureExtractor::reset(); }
};

struct BaseFeatureExtractorWrap : BaseFeatureExtractorPublic,
                                  wrapper<BaseFeatureExtractorPublic>
{
    void analyseSample(elapse::SamplePtr sample) {
        this->get_override("analyseSample")(sample);
    }
    std::vector<double> features() {
        return this->get_override("features")();
    }
    void removeDataBefore(elapse::TimeStamp time) {
        this->get_override("removeDataBefore")(time);
    }
    void reset() {
        if (override fn = this->get_override("reset"))
            fn();
        return BaseFeatureExtractorPublic::reset();
    }
    void default_reset() {
        return this->BaseFeatureExtractorPublic::reset();
    }
};


BOOST_PYTHON_MODULE(elements)
{
    class_<FeatureExtractorWrap, boost::noncopyable>("FeatureExtractor")
        .def("setStartTime", pure_virtual(&elapse::FeatureExtractor::setStartTime))
        .def("setWindowLength", pure_virtual(&elapse::FeatureExtractor::setWindowLength))
        .def("setWindowStep", pure_virtual(&elapse::FeatureExtractor::setWindowStep))
        .def("onSample", pure_virtual(&elapse::FeatureExtractor::onSample))
        .def("newFeatures", &elapse::FeatureExtractor::newFeatures);

    class_<BaseFeatureExtractorWrap, bases<elapse::FeatureExtractor>,
           boost::noncopyable>("BaseFeatureExtractor")
        .def("analyseSample", pure_virtual(&BaseFeatureExtractorPublic::analyseSample))
        .def("features", pure_virtual(&BaseFeatureExtractorPublic::features))
        .def("removeDataBefore", pure_virtual(&BaseFeatureExtractorPublic::removeDataBefore))
        .def("reset", &BaseFeatureExtractorPublic::reset,
                      &BaseFeatureExtractorWrap::default_reset);
}
