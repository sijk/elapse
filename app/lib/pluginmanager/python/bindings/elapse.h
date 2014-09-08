#ifndef PYTHON_ELAPSE_H
#define PYTHON_ELAPSE_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "elapse/sampletypes.h"
#include "elements.h"
#include "log.h"
#include "settings.h"
#include "gui.h"


std::vector<uchar> getVideoSampleData(elapse::VideoSample::const_ptr s)
{
    return std::vector<uchar>(s->data.cbegin(), s->data.cend());
}

struct QVector3DConverter
{
    static PyObject *convert(const QVector3D &vec)
    {
        using namespace boost::python;
        return incref(make_tuple(vec.x(), vec.y(), vec.z()).ptr());
    }
};


BOOST_PYTHON_MODULE(elapse)
{
    using namespace boost::python;
    using boost::noncopyable;

    // Turn this module into a package
    scope().attr("__path__") = "elapse";

    // Export sub-modules
    export_elements();
    export_log();
    export_settings();
    export_gui();

    {
        scope Signal = class_<elapse::Signal>("Signal", no_init)
            .def("toString", &elapse::Signal::toString)
            .staticmethod("toString")
            .def("fromString", &elapse::Signal::fromString)
            .staticmethod("fromString")
            .def("count", &elapse::Signal::count)
            .staticmethod("count");

        enum_<elapse::Signal::Type>("Type")
            .value("EEG", elapse::Signal::EEG)
            .value("VIDEO", elapse::Signal::VIDEO)
            .value("IMU", elapse::Signal::IMU)
            .value("INVALID", elapse::Signal::INVALID)
            .export_values();
    }

    class_<elapse::Sample, noncopyable>("Sample", no_init)
        .def_readwrite("timestamp", &elapse::Sample::timestamp);

    class_<elapse::EegSample, bases<elapse::Sample>, elapse::EegSample::ptr, noncopyable>("EegSample", no_init)
        .def("__init__", make_constructor(&elapse::EegSample::create))
        .def_readonly("seqnum", &elapse::EegSample::seqnum)
        .def_readonly("leadOff", &elapse::EegSample::seqnum)
        .def_readonly("values", &elapse::EegSample::values);

    class_<elapse::VideoSample, bases<elapse::Sample>, elapse::VideoSample::ptr, noncopyable>("VideoSample", no_init)
        .def("__init__", make_constructor(&elapse::VideoSample::create))
        .def_readonly("w", &elapse::VideoSample::w)
        .def_readonly("h", &elapse::VideoSample::h)
        .add_property("data", &getVideoSampleData);

    class_<elapse::ImuSample, bases<elapse::Sample>, elapse::ImuSample::ptr, noncopyable>("ImuSample", no_init)
        .def("__init__", make_constructor(&elapse::ImuSample::create))
        .add_property("acc", make_getter(&elapse::ImuSample::acc,
                                         return_value_policy<return_by_value>()))
        .add_property("gyr", make_getter(&elapse::ImuSample::gyr,
                                         return_value_policy<return_by_value>()));

    register_ptr_to_python<elapse::SamplePtr>();

    implicitly_convertible<elapse::EegSample::ptr, elapse::EegSample::const_ptr>();
    implicitly_convertible<elapse::VideoSample::ptr, elapse::VideoSample::const_ptr>();
    implicitly_convertible<elapse::ImuSample::ptr, elapse::ImuSample::const_ptr>();

    implicitly_convertible<elapse::EegSample::const_ptr, elapse::SamplePtr>();
    implicitly_convertible<elapse::VideoSample::const_ptr, elapse::SamplePtr>();
    implicitly_convertible<elapse::ImuSample::const_ptr, elapse::SamplePtr>();

    class_<elapse::FeatureVector>("FeatureVector",
                                  init<elapse::Signal::Type, elapse::TimeStamp>())
        .def_readonly("signalType", &elapse::FeatureVector::signalType)
        .def_readonly("startTime", &elapse::FeatureVector::startTime)
        .def_readonly("features", &elapse::FeatureVector::features);

    class_<elapse::CognitiveState>("CognitiveState", init<elapse::TimeStamp>())
        .def_readonly("startTime", &elapse::CognitiveState::startTime)
        .def_readonly("state", &elapse::CognitiveState::state);

    // ---

    class_<std::vector<double>>("_DoubleVector")
        .def(vector_indexing_suite<std::vector<double>>());

    class_<std::vector<uchar>>("_ByteArray")
        .def(vector_indexing_suite<std::vector<uchar>>());

    to_python_converter<QVector3D, QVector3DConverter>();
}

#endif // DOXYGEN
#endif // PYTHON_ELAPSE_H
