#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <QSharedPointer>
#include "elapse/sampletypes.h"
#include "elapse/elements/datasource.h"
#include "elapse/elements/decoder.h"
#include "elapse/elements/featurextractor.h"
#include "elapse/elements/classifier.h"
#include "elapse/elements/outputaction.h"
#include "elapse/elements/datasink.h"

using elapse::data::Signal;


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
    template<class T> using Ptr = QSharedPointer<T>; // for readability

    Ptr<elapse::DataSource> dataSource;
    QMap<Signal::Type, Ptr<elapse::SampleDecoder>> sampleDecoders;
    QMap<Signal::Type, Ptr<elapse::FeatureExtractor>> featureExtractors;
    Ptr<elapse::Classifier> classifier;
    Ptr<elapse::OutputAction> action;
    Ptr<elapse::DataSink> dataSink;

    QList<Ptr<QObject>> allElements() const;
};


/*!
 * \return a list of all the elements in the set.
 */
inline QList<ElementSet::Ptr<QObject>> ElementSet::allElements() const
{
    QList<Ptr<QObject>> elements;

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
