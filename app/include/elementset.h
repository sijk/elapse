/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <memory>
#include <map>
#include "elapse/datatypes.h"
#include "elapse/elements/datasource.h"
#include "elapse/elements/decoder.h"
#include "elapse/elements/featurextractor.h"
#include "elapse/elements/classifier.h"
#include "elapse/elements/outputaction.h"
#include "elapse/elements/datasink.h"

namespace elapse { namespace elements {

/*!
 * Custom deleter function type for element classes.
 */
using ElementDeleter = std::function<void(QObject*)>;

/*!
 * Unique pointer to an element (with a custom [deleter](\ref ElementDeleter)).
 */
template<class T> using ElementPtr = std::unique_ptr<T, ElementDeleter>;


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
    DataSource* dataSource() const { return _dataSource.get(); }
    SampleDecoder* sampleDecoder(data::Signal::Type type) const;
    QList<SampleDecoder*> sampleDecoders() const;
    FeatureExtractor* featureExtractor(data::Signal::Type type) const;
    QList<FeatureExtractor*> featureExtractors() const;
    Classifier* classifier() const { return _classifier.get(); }
    OutputAction* action() const { return _action.get(); }
    DataSink* dataSink() const { return _dataSink.get(); }

    QList<QObject*> allElements() const;

protected:
    ElementPtr<DataSource> _dataSource;
    std::map<data::Signal::Type, ElementPtr<SampleDecoder>> _sampleDecoders;
    std::map<data::Signal::Type, ElementPtr<FeatureExtractor>> _featureExtractors;
    ElementPtr<Classifier> _classifier;
    ElementPtr<OutputAction> _action;
    ElementPtr<DataSink> _dataSink;
};


inline SampleDecoder *ElementSet::sampleDecoder(data::Signal::Type type) const
{
    return _sampleDecoders.at(type).get();
}

inline QList<SampleDecoder *> ElementSet::sampleDecoders() const
{
    QList<SampleDecoder*> list;
    for (const auto &i : _sampleDecoders)
        list.append(i.second.get());
    return list;
}

inline FeatureExtractor *ElementSet::featureExtractor(data::Signal::Type type) const
{
    return _featureExtractors.at(type).get();
}

inline QList<FeatureExtractor *> ElementSet::featureExtractors() const
{
    QList<FeatureExtractor*> list;
    for (const auto &i : _featureExtractors)
        list.append(i.second.get());
    return list;
}

/*!
 * \return a list of all the elements in the set.
 */
inline QList<QObject*> ElementSet::allElements() const
{
    QList<QObject*> elements;

    elements.append(dataSource());
    for (auto sampleDecoder : sampleDecoders())
        elements.append(sampleDecoder);
    for (auto featureExtractor : featureExtractors())
        elements.append(featureExtractor);
    elements.append(classifier());
    elements.append(action());
    elements.append(dataSink());

    return elements;
}


/*!
 * A reference-counted pointer to an ElementSet. Automatically deletes the
 * ElementSet when nothing refers to it.
 * \ingroup signal-pipeline
 */
typedef std::shared_ptr<ElementSet> ElementSetPtr;

}} // namespace elapse::elements

#endif // ELEMENTS_H
