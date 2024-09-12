#pragma once

#include <cslibs_time/duration.hpp>
#include <cslibs_time/numeric_types.hpp>

namespace cslibs_time {
namespace statistics {
/**
 * @brief Class calculating the mean of durations.
 */
class DurationMean {
public:
  /// @brief underlying duration type
  using duration_t = cslibs_time::Duration;

  /**
   * @brief Adds a duration into the mean calculation.
   *
   * @param[in] d duration to add
   * @return DurationMean& reference to the accumulator object
   */
  DurationMean &operator+=(const duration_t &d) {
    const duration_t mean_1{mean_};
    const float64_t n{static_cast<float64_t>(n_)};
    const float64_t n_1{static_cast<float64_t>(n_1_)};

    mean_ = (mean_ * n_1 + d) / n;
    variance_ = (variance_ * n_1 + (d - mean_1) * (d - mean_)) / n;
    ++n_;
    ++n_1_;
    return *this;
  }

  /**
   * @brief Returns a const reference to the mean duration.
   *
   * @return duration_t const& const reference to the mean duration
   */
  duration_t const &mean() const { return mean_; }

  /**
   * @brief Returns a const reference to the duration variance.
   *
   * @return duration_t const& const reference to the duration variance
   */
  duration_t const &variance() const { return variance_; }

private:
  /// @brief current iteration
  std::size_t n_{1};
  /// @brief last iteration
  std::size_t n_1_{0};

  /// @brief computed mean
  duration_t mean_{};
  /// @brief computed variance.
  duration_t variance_{};
};
} // namespace statistics
} // namespace cslibs_time
