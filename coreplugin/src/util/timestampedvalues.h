#ifndef TIMESTAMPEDVALUES_H
#define TIMESTAMPEDVALUES_H

#include <QMap>

/*!
 * \brief The TimestampedValues class maps timestamps to arbitrary values.
 *
 * This class exists primarily as a convenience for implementing
 * FeatureExtractor%s. It provides an easy way to remove all values
 * which have timestamps less than a given value.
 */

template<typename T>
class TimestampedValues : public QMap<quint64, T>
{
public:
    /*!
     * Remove all values which have timestamps less than the given \a time.
     */
    void removeValuesBefore(quint64 time)
    {
        for (auto i = this->begin(); i != this->lowerBound(time); )
            i = this->erase(i);
    }
};

#endif // TIMESTAMPEDVALUES_H
