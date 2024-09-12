#pragma once

#include <cslibs_time/duration.hpp>
#include <cslibs_time/numeric_types.hpp>

namespace cslibs_time {
namespace statistics {
/**
 * @brief Class implementing a duration low pass filter.
 */
class DurationLowpass {
public:
  /// @brief underlying duration type
  using duration_t = cslibs_time::Duration;

  /**
   * @brief Constructor
   *
   * @param[in] alpha momentum of the low pass filter
   */
  explicit DurationLowpass(const float64_t alpha = 0.01) : alpha_{alpha} {}

  /// @brief Copy constructor
  DurationLowpass(const DurationLowpass &) = default;
  /// @brief Move constructor
  DurationLowpass(DurationLowpass &&) = default;

  /// @brief Copy assignment
  DurationLowpass &operator=(const DurationLowpass &) = default;
  /// @brief Move assignment
  DurationLowpass &operator=(DurationLowpass &&) = default;

  /**
   * @brief Adds a duration to the low pass filter
   *
   * @param[in] d duration
   * @return DurationLowpass& reference to the current object
   */
  DurationLowpass &operator+=(const duration_t &d) {
    duration_ = d * alpha_ + duration_ * (1.0 - alpha_);
    return *this;
  }

  /**
   * @brief Estimated low pass filtered duration.
   *
   * @return duration_t const& const reference to the estimated duration
   */
  duration_t const &duration() const { return duration_; }

private:
  float64_t alpha_;
  duration_t duration_{};
};
} // namespace statistics
} // namespace cslibs_time
