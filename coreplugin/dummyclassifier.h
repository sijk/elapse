#ifndef DUMMYCLASSIFIER_H
#define DUMMYCLASSIFIER_H

#include <elapse/elements/classifier.h>

namespace elapse { namespace coreplugin {

/*!
 * \brief The DummyClassifier class is a black hole for data::FeatureVector%s.
 *
 * \ingroup core-plugin
 */

class DummyClassifier : public elements::BaseClassifier
{
    Q_OBJECT
public:
    Q_INVOKABLE DummyClassifier();

protected:
    std::vector<double> classify(const FeatureSet &featureVectors) override;
};

}} // namespace elapse::coreplugin

#endif // DUMMYCLASSIFIER_H
