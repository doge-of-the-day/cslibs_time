#ifndef CSLIBS_TIME_DURATION_HPP
#define CSLIBS_TIME_DURATION_HPP

#include <chrono>
#include <thread>
#include <cmath>
#include <ostream>

namespace cslibs_time {
class Duration {
public:
    using clock_t    = std::chrono::high_resolution_clock;
    using time_t     = clock_t::time_point;
    using duration_t = clock_t::duration;

    inline Duration() :
        duration_(0l)
    {
    }

    inline Duration(const double seconds) :
        duration_(static_cast<int64_t>(std::floor(seconds * 1e9)))
    {
    }

    inline Duration(const int64_t nanoseconds) :
        duration_(nanoseconds)
    {
    }

    inline Duration(const duration_t duration) :
        duration_(duration)
    {
    }

    inline double seconds() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration_).count() * 1e-9;
    }

    inline double milliseconds() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration_).count() * 1e-6;
    }

    inline int64_t nanoseconds() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration_).count();
    }

    inline duration_t duration() const
    {
        return duration_;
    }


    inline bool sleep() const
    {
        if(duration_ <= duration_t(0))
            return false;
        std::this_thread::sleep_for(duration_);
        return true;
    }

    inline bool isZero() const
    {
        return duration_.count() == 0l;
    }

    inline Duration operator + (const Duration &other)
    {
        return Duration(other.duration_ + duration_);
    }

    inline Duration operator - (const Duration &other)
    {
        return Duration(other.duration_ - duration_);
    }

    inline Duration operator * (const double s)
    {
        return Duration(static_cast<int64_t>(std::floor(nanoseconds() * s)));
    }

    inline Duration operator / (const double s)
    {
        return Duration(static_cast<int64_t>(std::floor(nanoseconds() / s)));
    }

    inline bool operator == (const Duration &other)
    {
        return duration_ == other.duration_;
    }

    inline bool operator != (const Duration &other)
    {
        return duration_ != other.duration_;
    }

    inline bool operator <= (const Duration &other)
    {
        return duration_ <= other.duration_;
    }

    inline bool operator >= (const Duration &other)
    {
        return duration_ >= other.duration_;
    }

    inline bool operator > (const Duration &other)
    {
        return duration_ > other.duration_;
    }

    inline bool operator < (const Duration &other)
    {
        return duration_ < other.duration_;
    }

private:
    duration_t duration_;
} __attribute__ ((aligned (8)));;
}

inline std::ostream & operator << (std::ostream &out, const cslibs_time::Duration &duration)
{
    const int64_t ns = duration.nanoseconds();
    const int64_t s = ns / static_cast<int64_t>(1e9);
    const int64_t ms = (ns % static_cast<int64_t>(1e9));
    out << "[" << std::to_string(s) + "." + std::to_string(ms) << "]";
    return out;
}

#endif // CSLIBS_TIME_DURATION_HPP
