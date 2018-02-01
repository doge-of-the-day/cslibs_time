#ifndef CSLIBS_TIME_MEAN_DURATION_HPP
#define CSLIBS_TIME_MEAN_DURATION_HPP

#include <cslibs_time/duration.hpp>

namespace cslibs_time {
class MeanDuration {
public:
    using duration_t = cslibs_time::Duration;

    inline MeanDuration() :
        n_(1),
        n_1(0)
    {
    }

    inline MeanDuration &operator += (const Duration &d)
    {
        duration_ = (duration_ * static_cast<double>(n_1) + d) / static_cast<double>(n_);
        ++n_;
        ++n_1;
        return *this;
    }

    inline void add(const Duration &d)
    {
        duration_ = (duration_ * static_cast<double>(n_1) + d) / static_cast<double>(n_);
        ++n_;
        ++n_1;
    }

    inline double seconds() const
    {
        return duration_.seconds();
    }

    inline double milliseconds() const
    {
        return duration_.milliseconds();
    }

    inline int64_t nanoseconds() const
    {
        return duration_.nanoseconds();
    }

    inline const duration_t & duration() const
    {
        return duration_;
    }

private:
    std::size_t n_;
    std::size_t n_1;

    duration_t duration_;

};
}

#endif // CSLIBS_TIME_MEAN_DURATION_HPP
