#ifndef PYTHON_ELEMENTS_H
#define PYTHON_ELEMENTS_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include "python/exception.h"
#include "elapse/elements/featurextractor.h"
#include "elapse/elements/classifier.h"
#include "elapse/elements/outputaction.h"
#include "elapse/elements/datasink.h"

namespace py = boost::python;


/*!
 * Execute the given \a expr. If a Python runtime error occurs, print the
 * traceback.
 */
#define PYCATCH(expr) \
    try { expr; } \
    catch (const py::error_already_set&) { \
        qxtLog->trace(QString("Error in '%1'").arg(#expr)); \
        logPythonException(); \
    }

/*!
 * Execute the given \a expr and return the result, unless a Python runtime
 * error occurs, in which case print the traceback and return \a def.
 */
#define PYCATCH_RETURN(expr, def) \
    try { return expr; } \
    catch (const py::error_already_set&) { \
        qxtLog->trace(QString("Error in '%1'").arg(#expr)); \
        logPythonException(); \
    } \
    return def


struct FeatureExtractorWrap : elapse::FeatureExtractor,
                              py::wrapper<elapse::FeatureExtractor>
{
    void setStartTime(elapse::time::Point timestamp) {
        PYCATCH(this->get_override("setStartTime")(timestamp));
    }
    void setWindowLength(uint ms) {
        PYCATCH(this->get_override("setWindowLength")(ms));
    }
    void setWindowStep(uint ms) {
        PYCATCH(this->get_override("setWindowStep")(ms));
    }
    void onSample(elapse::SamplePtr sample) {
        PYCATCH(this->get_override("onSample")(sample));
    }
};

class BaseFeatureExtractorPublic : public elapse::BaseFeatureExtractor
{
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
public:
    using elapse::BaseFeatureExtractor::analyseSample;
    using elapse::BaseFeatureExtractor::removeDataBefore;
    using elapse::BaseFeatureExtractor::reset;
    virtual py::list pyfeatures() = 0;
};

struct BaseFeatureExtractorWrap : BaseFeatureExtractorPublic,
                                  py::wrapper<BaseFeatureExtractorPublic>
{
    void analyseSample(elapse::SamplePtr sample) {
        PYCATCH(this->get_override("analyseSample")(sample));
    }
    std::vector<double> features() {
        // py::list  ->  vector<double>
        py::list feat;
        PYCATCH(feat = this->pyfeatures());
        py::stl_input_iterator<double> begin(feat), end;
        return std::vector<double>(begin, end);
    }
    py::list pyfeatures() {
        PYCATCH_RETURN(this->get_override("features")(), {});
    }
    void removeDataBefore(elapse::time::Point time) {
        PYCATCH(this->get_override("removeDataBefore")(time));
    }
    void reset() {
        if (py::override fn = this->get_override("reset"))
            PYCATCH(fn());
        BaseFeatureExtractorPublic::reset();
    }
    void default_reset() {
        PYCATCH(this->BaseFeatureExtractorPublic::reset());
    }
};

struct ClassifierWrap : elapse::Classifier,
                        py::wrapper<elapse::Classifier>
{
    void onFeatures(elapse::FeatureVector features) {
        PYCATCH(this->get_override("onFeatures")(features));
    }
    void reset() {
        PYCATCH(this->get_override("reset")());
    }
};

class BaseClassifierPublic : public elapse::BaseClassifier
{
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
public:
    using elapse::BaseClassifier::classify;
};

struct BaseClassifierWrap : BaseClassifierPublic,
                            py::wrapper<BaseClassifierPublic>
{
    elapse::CognitiveState classify(QList<elapse::FeatureVector> featureVectors) {
        PYCATCH_RETURN(this->get_override("classify")(featureVectors),
                       elapse::CognitiveState(0));
    }
};

struct OutputActionWrap : elapse::OutputAction,
                          py::wrapper<elapse::OutputAction>
{
    void onState(elapse::CognitiveState state) {
        PYCATCH(this->get_override("onState")(state));
    }
};

class DataSinkPublic : public elapse::DataSink
{
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
public:
    using elapse::DataSink::getCaptureInfo;
    using elapse::DataSink::needsNewCaptureInfo;
    using elapse::DataSink::startSaving;
    using elapse::DataSink::stopSaving;
    using elapse::DataSink::saveData;
    using elapse::DataSink::saveSample;
    using elapse::DataSink::saveFeatureVector;
    using elapse::DataSink::saveCognitiveState;
    using elapse::DataSink::saveDeviceConfig;
};

struct DataSinkWrap : DataSinkPublic,
                      py::wrapper<DataSinkPublic>
{
    bool startSaving() {
        PYCATCH_RETURN(this->get_override("startSaving")(), false);
    }
    void stopSaving() {
        PYCATCH(this->get_override("stopSaving")());
    }
    bool needsNewCaptureInfo() {
        PYCATCH_RETURN(this->get_override("needsNewCaptureInfo")(), false);
    }
    bool getCaptureInfo() {
        PYCATCH_RETURN(this->get_override("getCaptureInfo")(), false);
    }
    void saveDeviceConfig(const QMap<QString, QVariantMap> &config) {
        PYCATCH(this->get_override("saveDeviceConfig")(config));
    }
    void saveData(elapse::Signal::Type signalType, QByteArray data) {
        if (py::override fn = this->get_override("saveData"))
            PYCATCH(fn(signalType, data));
        DataSinkPublic::saveData(signalType, data);
    }
    void default_saveData(elapse::Signal::Type signalType, QByteArray data) {
        PYCATCH(this->DataSinkPublic::saveData(signalType, data));
    }
    void saveSample(elapse::Signal::Type signalType, elapse::SamplePtr sample) {
        if (py::override fn = this->get_override("saveSample"))
            PYCATCH(fn(signalType, sample));
        DataSinkPublic::saveSample(signalType, sample);
    }
    void default_saveSample(elapse::Signal::Type signalType, elapse::SamplePtr sample) {
        PYCATCH(this->DataSinkPublic::saveSample(signalType, sample));
    }
    void saveFeatureVector(elapse::FeatureVector featureVector) {
        if (py::override fn = this->get_override("saveFeatureVector"))
            PYCATCH(fn(featureVector));
        DataSinkPublic::saveFeatureVector(featureVector);
    }
    void default_saveFeatureVector(elapse::FeatureVector featureVector) {
        PYCATCH(this->DataSinkPublic::saveFeatureVector(featureVector));
    }
    void saveCognitiveState(elapse::CognitiveState state) {
        if (py::override fn = this->get_override("saveCognitiveState"))
            PYCATCH(fn(state));
        DataSinkPublic::saveCognitiveState(state);
    }
    void default_saveCognitiveState(elapse::CognitiveState state) {
        PYCATCH(this->DataSinkPublic::saveCognitiveState(state));
    }
};

struct DeviceConfigConverter
{
    static PyObject *convert(const QMap<QString, QVariantMap> &config)
    {
        using namespace boost::python;
        dict pyconfig;

        for (auto i = config.cbegin(); i != config.cend(); i++) {
            dict subconfig;
            for (auto j = i.value().cbegin(); j != i.value().cend(); j++) {
                subconfig[j.key().toStdString()] = j.value().toString().toStdString();
            }
            pyconfig[i.key().toStdString()] = subconfig;
        }

        return incref(pyconfig.ptr());
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
        .def("features", pure_virtual(&BaseFeatureExtractorPublic::pyfeatures))
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

    class_<DataSinkWrap, boost::noncopyable>("DataSink")
        .def("startSaving", pure_virtual(&DataSinkPublic::startSaving))
        .def("stopSaving", pure_virtual(&DataSinkPublic::stopSaving))
        .def("needsNewCaptureInfo", pure_virtual(&DataSinkPublic::needsNewCaptureInfo))
        .def("getCaptureInfo", pure_virtual(&DataSinkPublic::getCaptureInfo))
        .def("saveDeviceConfig", pure_virtual(&DataSinkPublic::saveDeviceConfig))
        .def("saveData",
             &DataSinkPublic::saveData,
             &DataSinkWrap::default_saveData)
        .def("saveSample",
             &DataSinkPublic::saveSample,
             &DataSinkWrap::default_saveSample)
        .def("saveFeatureVector",
             &DataSinkPublic::saveFeatureVector,
             &DataSinkWrap::default_saveFeatureVector)
        .def("saveCognitiveState",
             &DataSinkPublic::saveCognitiveState,
             &DataSinkWrap::default_saveCognitiveState);

    to_python_converter<QMap<QString, QVariantMap>, DeviceConfigConverter>();
}

#endif // DOXYGEN
#endif // PYTHON_ELEMENTS_H
