#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QSharedPointer>
#include "elapse/sampletypes.h"
#include "elapse/elements/datasource.h"
#include "elapse/elements/decoder.h"
#include "elapse/elements/featurextractor.h"
#include "elapse/elements/classifier.h"
#include "elapse/elements/outputaction.h"
#include "elapse/elements/datasinkdelegate.h"

using elapse::Signal;


/*!
 * \brief The ElementSet struct holds pointers to a complete set of
 * \ref signal-pipeline "pipeline elements".
 *
 * The lifetimes of the elements in the set are tied to the set itself; that is,
 * when the ElementSet is destroyed all of the elements it contains will be
 * detroyed too.
 *
 * \ingroup signal-pipeline
 */

struct ElementSet
{
    QSharedPointer<elapse::DataSource> dataSource;
    QMap<Signal::Type, QSharedPointer<elapse::SampleDecoder>> sampleDecoders;
    QMap<Signal::Type, QSharedPointer<elapse::FeatureExtractor>> featureExtractors;
    QSharedPointer<elapse::Classifier> classifier;
    QSharedPointer<elapse::OutputAction> action;
    QSharedPointer<elapse::DataSinkDelegate> dataSink;

    QList<QSharedPointer<QObject>> allElements() const;
};


/*!
 * \return a list of all the elements in the set.
 */
inline QList<QSharedPointer<QObject>> ElementSet::allElements() const
{
    QList<QSharedPointer<QObject>> elements;

    elements.append(dataSource);
    for (auto &decoder : sampleDecoders)
        elements.append(decoder);
    for (auto &extractor : featureExtractors)
        elements.append(extractor);
    elements.append(classifier);
    elements.append(action);
    elements.append(dataSink);

    return elements;
}


/*!
 * A reference-counted pointer to an ElementSet. Automatically deletes the
 * ElementSet when nothing refers to it.
 * \ingroup signal-pipeline
 */
typedef QSharedPointer<ElementSet> ElementSetPtr;


#endif // ELEMENTS_H
