#ifndef TIMESTAMPEDVALUES_H
#define TIMESTAMPEDVALUES_H

#include <map>
#include <vector>

/*!
 * \brief The TimestampedValues class maps timestamps to arbitrary values.
 *
 * This class exists primarily as a convenience for implementing
 * FeatureExtractor%s. It provides an easy way to remove all values
 * which have timestamps less than a given value.
 *
 * \headerfile elapse/util/timestampedvalues.h
 */

template<typename T>
class TimestampedValues : public std::map<uint64_t, T>
{
public:
    /*!
     * Remove all values which have timestamps less than the given \a time.
     *
     * Relies on the fact that std::maps are sorted by their keys.
     */
    void removeValuesBefore(uint64_t time)
    {
        auto i = this->begin();
        auto end = this->lower_bound(time);

        while (i != end)
            i = this->erase(i);
    }

    /*!
     * \return the values as a std::vector.
     */
    std::vector<T> values() const
    {
        std::vector<T> vals;
        vals.reserve(this->size());
        for (auto value : *this)
            vals.push_back(value.second);
        return vals;
    }
};

#endif // TIMESTAMPEDVALUES_H
