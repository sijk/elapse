#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QxtLogger>


template<class T>
void qDebugPrintTo(const T &value, std::ostream *os)
{
    QString s;
    QDebug(&s) << value;
    *os << s.toStdString();
}

void PrintTo(const QString& str, std::ostream* os)
{
    *os << "QString(\"" << str.toStdString() << "\")";
}

void PrintTo(const QByteArray& bytes, std::ostream* os)
{
    *os << "QByteArray(\"" << bytes.constData() << "\")";
}

void PrintTo(const QVariant& var, std::ostream* os)
{
    qDebugPrintTo(var, os);
}


class SuppressLogging
{
public:
    SuppressLogging()
    {
        enabledEngines = qxtLog->allEnabledLoggerEngines();
        for (const QString &engine : enabledEngines)
            qxtLog->disableLoggerEngine(engine);
    }

    ~SuppressLogging()
    {
        for (const QString &engine : enabledEngines)
            qxtLog->enableLoggerEngine(engine);
    }

private:
    QStringList enabledEngines;
};


bool recursiveRmDir(const QString &dirname)
{
    bool result = true;
    QDir dir(dirname);
    auto flags = QDir::AllEntries|QDir::System|QDir::Hidden|QDir::NoDotAndDotDot;

    if (dir.exists()) {
        for (const QFileInfo &info : dir.entryInfoList(flags)) {
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


void clearSettings()
{
    QSettings settings;
    for (const auto &key : settings.allKeys())
        settings.remove(key);
}


#endif // TEST_UTILS_H
