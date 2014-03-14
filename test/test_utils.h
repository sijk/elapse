#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>


void PrintTo(const QString& str, std::ostream* os)
{
    *os << "QString(\"" << str.toStdString() << "\")";
}

#endif // TEST_UTILS_H
