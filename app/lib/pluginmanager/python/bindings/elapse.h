#ifndef PYTHON_ELAPSE_H
#define PYTHON_ELAPSE_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "elapse/sampletypes.h"
#include "elements.h"


struct VideoSample_wrap : elapse::VideoSample
{
    std::vector<uchar> getData() const
    {
        return std::vector<uchar>(data.cbegin(), data.cend());
    }
};

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

    // Turn this module into a package
    scope().attr("__path__") = "elapse";

    // Export the 'elapse.elements' module
    export_elements();

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

    class_<elapse::Sample>("Sample")
        .def_readonly("timestamp", &elapse::Sample::timestamp);

    class_<elapse::EegSample, bases<elapse::Sample>>("EegSample")
        .def_readonly("seqnum", &elapse::EegSample::seqnum)
        .def_readonly("leadOff", &elapse::EegSample::seqnum)
        .def_readonly("values", &elapse::EegSample::values);

    class_<VideoSample_wrap, bases<elapse::Sample>>("VideoSample")
        .def_readonly("w", &elapse::VideoSample::w)
        .def_readonly("h", &elapse::VideoSample::h)
        .add_property("data", &VideoSample_wrap::getData);

    class_<elapse::ImuSample, bases<elapse::Sample>>("ImuSample")
        .add_property("acc", make_getter(&elapse::ImuSample::acc,
                                         return_value_policy<return_by_value>()))
        .add_property("gyr", make_getter(&elapse::ImuSample::gyr,
                                         return_value_policy<return_by_value>()));

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
