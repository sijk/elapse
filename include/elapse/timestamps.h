#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <cstdint>
#include <ctime>
#include <map>
#include <vector>
#include <QString>

namespace elapse {

/*!
 * TimeStamp%s are expressed in nanoseconds since the Unix epoch.
 *
 * This won't overflow until December 2554.
 */
typedef std::uint64_t TimeStamp;

/*!
 * Utilities for working with elapse::TimeStamp%s.
 */
namespace time {

/*!
 * User-defined literals for expressing elapse::TimeStamp%s.
 *
 *     1_us == 1000_ns == 1000
 */
namespace literals {

constexpr TimeStamp operator"" _ns(unsigned long long n) { return n; }
constexpr TimeStamp operator"" _us(unsigned long long n) { return n * 1000_ns; }
constexpr TimeStamp operator"" _ms(unsigned long long n) { return n * 1000_us; }
constexpr TimeStamp operator"" _s (unsigned long long n) { return n * 1000_ms; }

} // namespace literals


template<typename T>
constexpr TimeStamp from_us(T t)
{
    using namespace literals;
    return t * 1_us;
}

template<typename T>
constexpr TimeStamp from_ms(T t)
{
    using namespace literals;
    return t * 1_ms;
}

template<typename T>
constexpr TimeStamp from_s(T t)
{
    using namespace literals;
    return t * 1_s;
}

inline TimeStamp from_timespec(const struct timespec *ts)
{
    return from_s(ts->tv_sec) + ts->tv_nsec;
}

/*!
 * \return the \a time in ISO 8601 format (yyyy-mm-ddThh:mm:ss.fffffffff).
 */
inline QString format(TimeStamp time)
{
    using namespace literals;

    const std::time_t seconds = time / 1_s;
    char date[20];
    std::strftime(date, 20, "%FT%T", std::gmtime(&seconds));

    return QString().sprintf("%s.%09lu", date, time % 1_s);
}

/*!
 * \brief The time::Series class maps TimeStamp%s to arbitrary values.
 *
 * This class exists primarily as a convenience for implementing
 * FeatureExtractor%s. It provides an easy way to remove all values
 * which have TimeStamp%s less than a given value.
 *
 * \headerfile elapse/timestamps.h
 */
template<typename T>
class Series : public std::map<TimeStamp, T>
{
public:
    /*!
     * Remove all values which have TimeStamp%s less than the given \a time.
     *
     * Relies on the fact that std::maps are sorted by their keys.
     */
    void removeValuesBefore(TimeStamp time)
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

} // namespace time

} // namespace elapse


inline QDataStream &operator>>(QDataStream &stream, elapse::TimeStamp &value)
{
    return stream >> reinterpret_cast<quint64&>(value);
}

#endif // TIMESTAMPS_H
