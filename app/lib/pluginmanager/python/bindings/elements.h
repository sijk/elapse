#ifndef PYTHON_ELEMENTS_H
#define PYTHON_ELEMENTS_H

#include <boost/python.hpp>
#include "elapse/elements/featurextractor.h"
#include "elapse/elements/classifier.h"
#include "elapse/elements/outputaction.h"
#include "elapse/elements/datasinkdelegate.h"

namespace py = boost::python;


struct FeatureExtractorWrap : elapse::FeatureExtractor,
                              py::wrapper<elapse::FeatureExtractor>
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
                                  py::wrapper<BaseFeatureExtractorPublic>
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
        if (py::override fn = this->get_override("reset"))
            fn();
        return BaseFeatureExtractorPublic::reset();
    }
    void default_reset() {
        return this->BaseFeatureExtractorPublic::reset();
    }
};

struct ClassifierWrap : elapse::Classifier,
                        py::wrapper<elapse::Classifier>
{
    void onFeatures(elapse::FeatureVector features) {
        this->get_override("onFeatures")(features);
    }
    void reset() {
        this->get_override("reset")();
    }
};

class BaseClassifierPublic : public elapse::BaseClassifier
{
public:
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
    virtual elapse::CognitiveState classify(QList<elapse::FeatureVector> featureVectors) = 0;
};

struct BaseClassifierWrap : BaseClassifierPublic,
                            py::wrapper<BaseClassifierPublic>
{
    elapse::CognitiveState classify(QList<elapse::FeatureVector> featureVectors) {
        return this->get_override("classify")(featureVectors);
    }
};

struct OutputActionWrap : elapse::OutputAction,
                          py::wrapper<elapse::OutputAction>
{
    void onState(elapse::CognitiveState state) {
        this->get_override("onState")(state);
    }
};

struct DataSinkDelegateWrap : elapse::DataSinkDelegate,
                              py::wrapper<elapse::DataSinkDelegate>
{
    bool start() {
        return this->get_override("start")();
    }
    void stop() {
        this->get_override("stop")();
    }
    bool needsNewCaptureInfo() {
        return this->get_override("needsNewCaptureInfo")();
    }
    bool getCaptureInfo() {
        return this->get_override("getCaptureInfo")();
    }
    void saveDeviceConfig(const QMap<QString, QVariantMap> &config) {
        this->get_override("saveDeviceConfig")(config);
    }
    void saveData(elapse::Signal::Type signalType, QByteArray data) {
        this->get_override("saveData")(signalType, data);
    }
    void saveSample(elapse::Signal::Type signalType, elapse::SamplePtr sample) {
        this->get_override("saveSample")(signalType, sample);
    }
    void saveFeatureVector(elapse::FeatureVector featureVector) {
        this->get_override("saveFeatureVector")(featureVector);
    }
    void saveCognitiveState(elapse::CognitiveState state) {
        this->get_override("saveCognitiveState")(state);
    }
};


void export_elements()
{
    using namespace boost::python;

    // Make this a sub-module of 'elapse'
    object elements(handle<>(borrowed(PyImport_AddModule("elapse.elements"))));
    scope().attr("elements") = elements;
    scope elements_scope = elements;

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

    class_<ClassifierWrap, boost::noncopyable>("Classifier")
        .def("onFeatures", pure_virtual(&elapse::Classifier::onFeatures))
        .def("reset", pure_virtual(&elapse::Classifier::reset))
        .def("newState", &elapse::Classifier::newState);

    class_<BaseClassifierWrap, bases<elapse::Classifier>,
            boost::noncopyable>("BaseClassifier")
        .def("classify", pure_virtual(&BaseClassifierPublic::classify));

    class_<OutputActionWrap, boost::noncopyable>("OutputAction")
        .def("onState", pure_virtual(&elapse::OutputAction::onState));

    class_<DataSinkDelegateWrap, boost::noncopyable>("DataSinkDelegate")
        .def("start", pure_virtual(&elapse::DataSinkDelegate::start))
        .def("stop", pure_virtual(&elapse::DataSinkDelegate::stop))
        .def("needsNewCaptureInfo", pure_virtual(&elapse::DataSinkDelegate::needsNewCaptureInfo))
        .def("getCaptureInfo", pure_virtual(&elapse::DataSinkDelegate::getCaptureInfo))
        .def("saveDeviceConfig", pure_virtual(&elapse::DataSinkDelegate::saveDeviceConfig))
        .def("saveData", pure_virtual(&elapse::DataSinkDelegate::saveData))
        .def("saveSample", pure_virtual(&elapse::DataSinkDelegate::saveSample))
        .def("saveFeatureVector", pure_virtual(&elapse::DataSinkDelegate::saveFeatureVector))
        .def("saveCognitiveState", pure_virtual(&elapse::DataSinkDelegate::saveCognitiveState));
}

#endif // PYTHON_ELEMENTS_H
