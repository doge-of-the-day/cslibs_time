#pragma once

#include <cslibs_time/duration.hpp>

namespace cslibs_time {
namespace statistics {
class DurationWindow {
public:
    using duration_t = cslibs_time::Duration;

    DurationWindow() = default;

    explicit DurationWindow(const std::size_t size) :
        size_{size}
    {
    }

    DurationWindow(const DurationWindow&) = default;
    DurationWindow(DurationWindow&&) = default;

    DurationWindow& operator = (const DurationWindow&) = default;
    DurationWindow& operator = (DurationWindow&&) = default;

    DurationWindow& operator += (const duration_t &d)
    {

        const double n = static_cast<double>(n_);
        const double n_1 = static_cast<double>(n_1_);

        auto update_Window = [this, n, n_1] (const duration_t &d) ->DurationWindow&
        {
            const duration_t mean_1 = mean_ * n - oldest_;
            const duration_t deviation_1 = deviation_ * n - (oldest_ - mean_1) * (oldest_ - mean_);
            mean_      = (mean_1 + d) / n;
            deviation_ = (deviation_1 + (d - mean_1) * (d - mean_)) / n;
            return *this;
        };
        auto update = [this, n, n_1](const duration_t &d) ->DurationWindow&
        {
            const duration_t mean_1 = mean_;
            mean_      = (mean_ * n_1 + d) / n;
            deviation_ = (deviation_ * n_1 + (d - mean_1) * (d - mean_)) / n;
            ++n_;
            ++n_1_;
            return *this;
        };

        return n_ >= size_ ? update_Window(d) : update(d);
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
    std::size_t size_{std::numeric_limits<std::size_t>::max()};

    duration_t mean_;
    duration_t deviation_;
    duration_t oldest_;
};
}
}
