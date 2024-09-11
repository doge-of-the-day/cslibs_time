#pragma once

#include <cslibs_time/duration.hpp>

namespace cslibs_time {
namespace statistics {
class DurationMean {
public:
    using duration_t = cslibs_time::Duration;

    DurationMean& operator += (const duration_t &d)
    {
        const duration_t mean_1 = mean_;
        const double n = static_cast<double>(n_);
        const double n_1 = static_cast<double>(n_1_);

        mean_      = (mean_ * n_1 + d) / n;
        deviation_ = (deviation_ * n_1 + (d - mean_1) * (d - mean_)) / n;
        ++n_;
        ++n_1_;
        return *this;
    }

    duration_t const & mean() const
    {
        return mean_;
    }

    duration_t const &variance() const
    {
        return deviation_;
    }

private:
    std::size_t n_{1};
    std::size_t n_1_{0};

    duration_t mean_{};
    duration_t deviation_{};
};
}
}
