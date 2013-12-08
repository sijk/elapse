#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "sampletypes.h"
#include "elements/datasource.h"
#include "elements/decoder.h"
#include "elements/featurextractor.h"
#include "elements/classifier.h"


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
    DataSource *dataSource;
    SampleDecoder *sampleDecoders[N_SAMPLE_TYPES];
    FeatureExtractor *featureExtractors[N_SAMPLE_TYPES];
    Classifier *classifier;

    ~ElementSet();
};


/*!
 * Destroy this ElementSet and all of the elements it contains.
 */
inline ElementSet::~ElementSet() {
    delete dataSource;
    for (int i = 0; i < N_SAMPLE_TYPES; i++) {
        delete sampleDecoders[i];
        delete featureExtractors[i];
    }
    delete classifier;
}

#endif // ELEMENTS_H
