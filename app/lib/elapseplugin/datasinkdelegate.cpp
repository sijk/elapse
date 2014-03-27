#include <QxtLogger>
#include "elapse/elements/datasinkdelegate.h"


/*!
 * Create a new DataSinkDelegate as a child of the given \a parent.
 */
elapse::DataSinkDelegate::DataSinkDelegate(QObject *parent) :
    QObject(parent)
{
}

void elapse::DataSinkDelegate::saveData(Signal::Type signalType, QByteArray data)
{
    Q_UNUSED(signalType)
    Q_UNUSED(data)
    qxtLog->warning("DataSink: Raw data saving is enabled but",
                    metaObject()->className(),
                    "doesn't support saving raw data.");
}

void elapse::DataSinkDelegate::saveSample(Signal::Type signalType,
                                          elapse::SamplePtr sample)
{
    Q_UNUSED(signalType)
    Q_UNUSED(sample)
    qxtLog->warning("DataSink: Sample saving is enabled but",
                    metaObject()->className(),
                    "doesn't support saving samples.");
}

void elapse::DataSinkDelegate::saveFeatureVector(elapse::FeatureVector featureVector)
{
    Q_UNUSED(featureVector)
    qxtLog->warning("DataSink: Feature vector saving is enabled but",
                    metaObject()->className(),
                    "doesn't support saving feature vectors.");
}

void elapse::DataSinkDelegate::saveCognitiveState(elapse::CognitiveState state)
{
    Q_UNUSED(state)
    qxtLog->warning("DataSink: Cognitive state saving is enabled but",
                    metaObject()->className(),
                    "doesn't support saving cognitive state.");
}

