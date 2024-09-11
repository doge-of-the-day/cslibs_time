#pragma once

#include <cslibs_time/duration.hpp>

namespace cslibs_time {
namespace statistics {
class DurationLowpass {
public:
    using duration_t = cslibs_time::Duration;

    explicit DurationLowpass(const double alpha = 0.01) :
        alpha_{alpha}
    {
    }

    DurationLowpass(const DurationLowpass&) = default;
    DurationLowpass(DurationLowpass&&) = default;

    DurationLowpass& operator = (const DurationLowpass&) = default;
    DurationLowpass& operator = (DurationLowpass&&) = default;

    DurationLowpass& operator += (const duration_t &d)
    {
        duration_ = d * alpha_ + duration_ * (1.0 - alpha_);
        return *this;
    }

    duration_t const & duration() const
    {
        return duration_;
    }

private:
    double     alpha_;
    duration_t duration_{};
};
}
}
