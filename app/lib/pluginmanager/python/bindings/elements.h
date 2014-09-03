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

using namespace elapse::elements;

namespace py = boost::python;


/*!
 * Execute the given \a expr. If a Python runtime error occurs, print the
 * traceback.
 */
#define PYCATCH(expr) \
    try { expr; } \
    catch (const py::error_already_set&) { \
        qxtLog->trace(QString("Error in '%1'").arg(#expr)); \
        elapse::plugin::python::logException(); \
    }

/*!
 * Execute the given \a expr and return the result, unless a Python runtime
 * error occurs, in which case print the traceback and return \a def.
 */
#define PYCATCH_RETURN(expr, def) \
    try { return expr; } \
    catch (const py::error_already_set&) { \
        qxtLog->trace(QString("Error in '%1'").arg(#expr)); \
        elapse::plugin::python::logException(); \
    } \
    return def


struct FeatureExtractorWrap : FeatureExtractor,
                              py::wrapper<FeatureExtractor>
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
    void onSample(elapse::data::SamplePtr sample) {
        PYCATCH(this->get_override("onSample")(sample));
    }
};

class BaseFeatureExtractorPublic : public BaseFeatureExtractor
{
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
public:
    using BaseFeatureExtractor::analyseSample;
    using BaseFeatureExtractor::removeDataBefore;
    using BaseFeatureExtractor::reset;
    virtual py::list pyfeatures() = 0;
};

struct BaseFeatureExtractorWrap : BaseFeatureExtractorPublic,
                                  py::wrapper<BaseFeatureExtractorPublic>
{
    void analyseSample(elapse::data::SamplePtr sample) {
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

struct ClassifierWrap : Classifier,
                        py::wrapper<Classifier>
{
    void onFeatures(elapse::data::FeatureVector features) {
        PYCATCH(this->get_override("onFeatures")(features));
    }
    void reset() {
        PYCATCH(this->get_override("reset")());
    }
};

class BaseClassifierPublic : public BaseClassifier
{
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
public:
    using BaseClassifier::classify;
};

struct BaseClassifierWrap : BaseClassifierPublic,
                            py::wrapper<BaseClassifierPublic>
{
    elapse::data::CognitiveState classify(QList<elapse::data::FeatureVector> featureVectors) {
        PYCATCH_RETURN(this->get_override("classify")(featureVectors),
                       elapse::data::CognitiveState(0));
    }
};

struct OutputActionWrap : OutputAction,
                          py::wrapper<OutputAction>
{
    void onState(elapse::data::CognitiveState state) {
        PYCATCH(this->get_override("onState")(state));
    }
};

class DataSinkPublic : public DataSink
{
    // Make the protected virtual methods public so they can be overriden
    // by python classes.
public:
    using DataSink::getCaptureInfo;
    using DataSink::needsNewCaptureInfo;
    using DataSink::startSaving;
    using DataSink::stopSaving;
    using DataSink::saveData;
    using DataSink::saveSample;
    using DataSink::saveFeatureVector;
    using DataSink::saveCognitiveState;
    using DataSink::saveDeviceConfig;
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
    void saveData(elapse::data::Signal::Type signalType, QByteArray data) {
        if (py::override fn = this->get_override("saveData"))
            PYCATCH(fn(signalType, data));
        DataSinkPublic::saveData(signalType, data);
    }
    void default_saveData(elapse::data::Signal::Type signalType, QByteArray data) {
        PYCATCH(this->DataSinkPublic::saveData(signalType, data));
    }
    void saveSample(elapse::data::Signal::Type signalType, elapse::data::SamplePtr sample) {
        if (py::override fn = this->get_override("saveSample"))
            PYCATCH(fn(signalType, sample));
        DataSinkPublic::saveSample(signalType, sample);
    }
    void default_saveSample(elapse::data::Signal::Type signalType, elapse::data::SamplePtr sample) {
        PYCATCH(this->DataSinkPublic::saveSample(signalType, sample));
    }
    void saveFeatureVector(elapse::data::FeatureVector featureVector) {
        if (py::override fn = this->get_override("saveFeatureVector"))
            PYCATCH(fn(featureVector));
        DataSinkPublic::saveFeatureVector(featureVector);
    }
    void default_saveFeatureVector(elapse::data::FeatureVector featureVector) {
        PYCATCH(this->DataSinkPublic::saveFeatureVector(featureVector));
    }
    void saveCognitiveState(elapse::data::CognitiveState state) {
        if (py::override fn = this->get_override("saveCognitiveState"))
            PYCATCH(fn(state));
        DataSinkPublic::saveCognitiveState(state);
    }
    void default_saveCognitiveState(elapse::data::CognitiveState state) {
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
        .def("setStartTime", pure_virtual(&FeatureExtractor::setStartTime))
        .def("setWindowLength", pure_virtual(&FeatureExtractor::setWindowLength))
        .def("setWindowStep", pure_virtual(&FeatureExtractor::setWindowStep))
        .def("onSample", pure_virtual(&FeatureExtractor::onSample))
        .def("newFeatures", &FeatureExtractor::newFeatures);

    class_<BaseFeatureExtractorWrap, bases<FeatureExtractor>,
           boost::noncopyable>("BaseFeatureExtractor")
        .def("analyseSample", pure_virtual(&BaseFeatureExtractorPublic::analyseSample))
        .def("features", pure_virtual(&BaseFeatureExtractorPublic::pyfeatures))
        .def("removeDataBefore", pure_virtual(&BaseFeatureExtractorPublic::removeDataBefore))
        .def("reset", &BaseFeatureExtractorPublic::reset,
                      &BaseFeatureExtractorWrap::default_reset);

    class_<ClassifierWrap, boost::noncopyable>("Classifier")
        .def("onFeatures", pure_virtual(&Classifier::onFeatures))
        .def("reset", pure_virtual(&Classifier::reset))
        .def("newState", &Classifier::newState);

    class_<BaseClassifierWrap, bases<Classifier>,
            boost::noncopyable>("BaseClassifier")
        .def("classify", pure_virtual(&BaseClassifierPublic::classify));

    class_<OutputActionWrap, boost::noncopyable>("OutputAction")
        .def("onState", pure_virtual(&OutputAction::onState));

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
