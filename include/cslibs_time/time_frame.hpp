#ifndef CSLIBS_TIME_TIME_FRAME_HPP
#define CSLIBS_TIME_TIME_FRAME_HPP

#include <cslibs_time/time.hpp>
#include <string>

namespace cslibs_time {
struct TimeFrame {
    const Time start;
    const Time end;

    inline TimeFrame() :
        start(Time::now()),
        end(start)
    {
    }

    inline TimeFrame(const double start_seconds,
                     const double end_seconds) :
        start(start_seconds),
        end(end_seconds)
    {
    }

    inline TimeFrame(const int64_t &start_nanoseconds,
                     const int64_t &end_nanoseconds) :
        start(start_nanoseconds),
        end(end_nanoseconds)
    {
    }

    inline TimeFrame(const uint64_t &start_nanoseconds,
                     const uint64_t &end_nanoseconds) :
        start(start_nanoseconds),
        end(end_nanoseconds)
    {
    }

    inline TimeFrame(const Time::time_t &start_time,
                     const Time::time_t &end_time) :
        start{start_time},
        end{end_time}
    {
    }

    inline TimeFrame(const Time &start_time,
                     const Time &end_time) :
        start{start_time},
        end{end_time}
    {
    }

    inline TimeFrame(const TimeFrame &other) :
        start(other.start),
        end(other.end)
    {
    }

    inline bool within(const Time &time) const
    {
        return time >= start && time <= end;
    }

    inline Duration duration() const
    {
        return end.time() - start.time();
    }
} ;
}

inline std::ostream & operator << (std::ostream &out, const cslibs_time::TimeFrame &time)
{
    out << "[" << time.start << "," << time.end << "]";
    return out;
}

#endif // CSLIBS_TIME_TIME_FRAME_HPP
