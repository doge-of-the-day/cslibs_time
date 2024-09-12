#pragma once

#include <cslibs_time/duration.hpp>
#include <cslibs_time/numeric_types.hpp>

namespace cslibs_time {
namespace statistics {
/**
 * @brief Class representing a rolling window for durations.
 */
class DurationWindow {
public:
  /// @brief underlying duration type
  using duration_t = cslibs_time::Duration;

  /// @brief Default constructor
  DurationWindow() = default;

  /**
   * @brief Constructor
   *
   * @param[in] size of the window in which values shall be collected
   */
  explicit DurationWindow(const std::size_t size) : size_{size} {}

  /// @brief Copy constructor
  DurationWindow(const DurationWindow &) = default;
  /// @brief Move constructor
  DurationWindow(DurationWindow &&) = default;

  /// @brief Copy assignment
  DurationWindow &operator=(const DurationWindow &) = default;
  /// @brief Move assignment
  DurationWindow &operator=(DurationWindow &&) = default;

  /**
   * @brief Adds duration to the current duration window.
   *
   * @param[in] d duration to add to the rolling window
   * @return DurationWindow& reference to the current object
   */
  DurationWindow &operator+=(const duration_t &d) {

    const float64_t n{static_cast<float64_t>(n_)};
    const float64_t n_1{static_cast<float64_t>(n_1_)};

    auto update_Window = [this, n, n_1](const duration_t &d) -> DurationWindow & {
      const duration_t mean_1{mean_ * n - oldest_};
      const duration_t variance_1{
          variance_ * n - (oldest_ - mean_1) * (oldest_ - mean_)};
      mean_ = (mean_1 + d) / n;
      variance_ = (variance_1 + (d - mean_1) * (d - mean_)) / n;
      return *this;
    };
    auto update = [this, n, n_1](const duration_t &d) -> DurationWindow & {
      const duration_t mean_1 = mean_;
      mean_ = (mean_ * n_1 + d) / n;
      variance_ = (variance_ * n_1 + (d - mean_1) * (d - mean_)) / n;
      ++n_;
      ++n_1_;
      return *this;
    };

    return n_ >= size_ ? update_Window(d) : update(d);
  }

  /**
   * @brief Returns the mean of the durations added in the rolling window.
   *
   * @return duration_t const& const reference to the mean
   */
  duration_t const &mean() const { return mean_; }

  /**
   * @brief Returns the variance of the durations added in the rolling window.
   *
   * @return duration_t const& const reference to the variance
   */
  duration_t const &variance() const { return variance_; }

private:
  std::size_t n_{1};
  std::size_t n_1_{0};
  std::size_t size_{std::numeric_limits<std::size_t>::max()};

  duration_t mean_{};
  duration_t variance_{};
  duration_t oldest_{};
};
} // namespace statistics
} // namespace cslibs_time
