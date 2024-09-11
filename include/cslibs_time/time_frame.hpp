#pragma once

#include <cslibs_time/time.hpp>
#include <string>

namespace cslibs_time {
struct TimeFrame {
    const Time start;
    const Time end;

    explicit TimeFrame() :
        start{Time::now()},
        end{start}
    {
    }

    TimeFrame(const double start_seconds,
              const double end_seconds) :
        start{start_seconds},
        end{end_seconds}
    {
    }

    TimeFrame(const int64_t &start_nanoseconds,
              const int64_t &end_nanoseconds) :
        start{start_nanoseconds},
        end{end_nanoseconds}
    {
    }

    TimeFrame(const uint64_t &start_nanoseconds,
              const uint64_t &end_nanoseconds) :
        start{start_nanoseconds},
        end{end_nanoseconds}
    {
    }

    TimeFrame(const Time::time_t &start_time,
              const Time::time_t &end_time) :
        start{start_time},
        end{end_time}
    {
    }

    TimeFrame(const Time &start_time,
              const Time &end_time) :
        start{start_time},
        end{end_time}
    {
    }

    TimeFrame(const TimeFrame &) = default;
    TimeFrame(TimeFrame &&) = default;

    bool within(const Time &time) const
    {
        return time >= start && time <= end;
    }

    Duration duration() const
    {
        return Duration{end.time() - start.time()};
    }
} ;
}

inline std::ostream & operator << (std::ostream &out, const cslibs_time::TimeFrame &time)
{
    out << "[" << time.start << "," << time.end << "]";
    return out;
}
