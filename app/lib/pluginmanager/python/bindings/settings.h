#ifndef PYTHON_SETTINGS_H
#define PYTHON_SETTINGS_H

#ifndef DOXYGEN

#include <boost/python.hpp>
#include <QSettings>

namespace py = boost::python;


template<class T>
T value(const std::string &key)
{
    return QSettings().value(key.c_str()).value<T>();
}

template<class T>
void setValue(const std::string &key, const T &value)
{
    QSettings().setValue(key.c_str(), QVariant::fromValue(value));
}

template<>
std::string value(const std::string &key)
{
    return value<QString>(key).toStdString();
}

template<>
void setValue(const std::string &key, const std::string &value)
{
    setValue(key, QString::fromStdString(value));
}


void export_settings()
{
    using namespace boost::python;

    // Make this a sub-module of 'elapse'
    object settings(handle<>(borrowed(PyImport_AddModule("elapse.settings"))));
    scope().attr("settings") = settings;
    scope settings_scope = settings;

    def("getBool", value<bool>);
    def("setBool", setValue<bool>);
    def("getInt", value<int>);
    def("setInt", setValue<int>);
    def("getStr", value<std::string>);
    def("setStr", setValue<std::string>);
    def("getFloat", value<double>);
    def("setFloat", setValue<double>);
}

#endif // DOXYGEN
#endif // PYTHON_SETTINGS_H
