#ifndef PYTHON_EXCEPTION_H
#define PYTHON_EXCEPTION_H

#include <QString>

struct PythonException
{
    QString type;
    QString value;
    QStringList traceback;
};

PythonException getPythonException();

void logPythonException();

#endif // PYTHON_EXCEPTION_H
