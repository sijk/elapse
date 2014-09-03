#ifndef PYTHON_EXCEPTION_H
#define PYTHON_EXCEPTION_H

#include <QString>

namespace elapse { namespace plugin { namespace python {

struct Exception
{
    QString type;
    QString value;
    QStringList traceback;
};

Exception getException();

void logException();

}}} // namespace elapse::plugin::python

#endif // PYTHON_EXCEPTION_H
