#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <cstdint>
#include <ctime>
#include <QString>

/*!
 * TimeStamp%s are expressed in nanoseconds since the Unix epoch.
 *
 * This won't overflow until December 2554.
 */
typedef std::uint64_t TimeStamp;


/*!
 * Utilities for working with timestamps.
 */
namespace timestamp {

/*!
 * User-defined literals for expressing timestamps.
 *
 * e.g. 1_us == 1000_ns == 1000
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

inline QString format(TimeStamp time)
{
    using namespace literals;

    const std::time_t seconds = time / 1_s;
    char date[20];
    std::strftime(date, 20, "%Y-%m-%dT%H:%M:%S", std::gmtime(&seconds));

    return QString().sprintf("%s.%09lu", date, time % 1_s);
}

} // namespace timestamp

#endif // TIMESTAMPS_H
