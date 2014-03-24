#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <QString>
#include <QDir>


void PrintTo(const QString& str, std::ostream* os)
{
    *os << "QString(\"" << str.toStdString() << "\")";
}


bool recursiveRmDir(const QString &dirname)
{
    bool result = true;
    QDir dir(dirname);
    auto flags = QDir::AllEntries|QDir::System|QDir::Hidden|QDir::NoDotAndDotDot;

    if (dir.exists()) {
        foreach (QFileInfo info, dir.entryInfoList(flags))
        {
            result = info.isDir()
                   ? recursiveRmDir(info.absoluteFilePath())
                   : QFile::remove(info.absoluteFilePath());

            if (!result)
                return result;
        }
        result = dir.rmdir(dirname);
    }

    return result;
}


#endif // TEST_UTILS_H
