#ifndef PYTHON_ELAPSE_H
#define PYTHON_ELAPSE_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "elapse/datatypes.h"
#include "python/host.h"
#include "elements.h"
#include "log.h"
#include "settings.h"
#include "gui.h"


std::vector<uchar> getVideoSampleData(elapse::data::VideoSample::const_ptr s)
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

template<class T>
typename T::const_ptr fromSample(elapse::data::SamplePtr sample)
{
    return T::dynamicCastFrom(sample);
}


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

    def("export", &elapse::plugin::python::registerClass);

    {
        object data(handle<>(borrowed(PyImport_AddModule("elapse.data"))));
        scope().attr("data") = data;
        scope data_scope = data;

        using namespace elapse::data;

        {
            scope signal = class_<Signal>("Signal", no_init)
                .def("toString", &Signal::toString)
                .staticmethod("toString")
                .def("fromString", &Signal::fromString)
                .staticmethod("fromString")
                .def("count", &Signal::count)
                .staticmethod("count");

            enum_<Signal::Type>("Type")
                .value("EEG", Signal::EEG)
                .value("VIDEO", Signal::VIDEO)
                .value("IMU", Signal::IMU)
                .value("INVALID", Signal::INVALID)
                .export_values();
        }

        class_<Sample, noncopyable>("Sample", no_init)
            .def_readwrite("timestamp", &Sample::timestamp);

        class_<EegSample, bases<Sample>, EegSample::ptr, noncopyable>("EegSample", no_init)
            .def("__init__", make_constructor(&EegSample::create))
            .def("fromSample", &fromSample<EegSample>)
            .staticmethod("fromSample")
            .def_readonly("seqnum", &EegSample::seqnum)
            .def_readonly("leadOff", &EegSample::seqnum)
            .def_readonly("values", &EegSample::values);

        class_<VideoSample, bases<Sample>, VideoSample::ptr, noncopyable>("VideoSample", no_init)
            .def("__init__", make_constructor(&VideoSample::create))
            .def("fromSample", &fromSample<VideoSample>)
            .staticmethod("fromSample")
            .def_readonly("w", &VideoSample::w)
            .def_readonly("h", &VideoSample::h)
            .add_property("data", &getVideoSampleData);

        class_<ImuSample, bases<Sample>, ImuSample::ptr, noncopyable>("ImuSample", no_init)
            .def("__init__", make_constructor(&ImuSample::create))
            .def("fromSample", &fromSample<ImuSample>)
            .staticmethod("fromSample")
            .add_property("acc", make_getter(&ImuSample::acc,
                                             return_value_policy<return_by_value>()))
            .add_property("gyr", make_getter(&ImuSample::gyr,
                                             return_value_policy<return_by_value>()));

        register_ptr_to_python<SamplePtr>();
        register_ptr_to_python<EegSample::const_ptr>();
        register_ptr_to_python<VideoSample::const_ptr>();
        register_ptr_to_python<ImuSample::const_ptr>();

        implicitly_convertible<EegSample::ptr, EegSample::const_ptr>();
        implicitly_convertible<VideoSample::ptr, VideoSample::const_ptr>();
        implicitly_convertible<ImuSample::ptr, ImuSample::const_ptr>();

        implicitly_convertible<EegSample::const_ptr, SamplePtr>();
        implicitly_convertible<VideoSample::const_ptr, SamplePtr>();
        implicitly_convertible<ImuSample::const_ptr, SamplePtr>();

        class_<FeatureVector, FeatureVector::ptr>("FeatureVector",
            init<Signal::Type, elapse::time::Point>())
            .def_readonly("signalType", &FeatureVector::signalType)
            .def_readonly("startTime", &FeatureVector::startTime)
            .def_readonly("features", &FeatureVector::features);

        register_ptr_to_python<FeatureVector::const_ptr>();
        implicitly_convertible<FeatureVector::ptr, FeatureVector::const_ptr>();

        class_<CognitiveState, CognitiveState::ptr>("CognitiveState",
            init<elapse::time::Point>())
            .def_readonly("startTime", &CognitiveState::startTime)
            .def_readonly("state", &CognitiveState::state);

        register_ptr_to_python<CognitiveState::const_ptr>();
        implicitly_convertible<CognitiveState::ptr, CognitiveState::const_ptr>();
    }

    // ---

    class_<std::vector<double>>("_DoubleVector")
        .def(vector_indexing_suite<std::vector<double>>());

    class_<std::vector<uchar>>("_ByteArray")
        .def(vector_indexing_suite<std::vector<uchar>>());

    to_python_converter<QVector3D, QVector3DConverter>();
}

#endif // DOXYGEN
#endif // PYTHON_ELAPSE_H
