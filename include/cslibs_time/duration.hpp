#pragma once

#include <cslibs_time/numeric_types.hpp>

#include <chrono>
#include <cmath>
#include <ostream>
#include <thread>

namespace cslibs_time {
/**
 * @brief Class representing a duration.
 */
class Duration {
public:
  /// @brief underlying clock type
  using clock_t = std::chrono::high_resolution_clock;
  /// @brief underlying time type
  using time_t = clock_t::time_point;
  /// @brief underlying duration type
  using duration_t = clock_t::duration;

  /// @brief Default constructor
  explicit Duration() = default;

  /**
   * @brief Constructor
   *
   * @param[in] seconds seconds given as a floating point value
   */
  explicit Duration(const float64_t seconds)
      : duration_(static_cast<int64_t>(std::floor(seconds * 1e9))) {}

  /**
   * @brief Constructor
   *
   * @param[in] nanoseconds given as a integer value
   */
  explicit Duration(const int64_t nanoseconds) : duration_{nanoseconds} {}

  /**
   * @brief Constructor
   *
   * @param[in] duration underlying duration type
   */
  explicit Duration(const duration_t duration) : duration_(duration) {}

  /// @brief Copy constructor
  Duration(const Duration &) = default;
  /// @brief Move constructor
  Duration(Duration &&) = default;

  /// @brief Copy assignment
  Duration &operator=(const Duration &) = default;
  /// @brief Move assignment
  Duration &operator=(Duration &&) = default;

  /**
   * @brief Returns duration value in seconds.
   *
   * @return float64_t seconds given as a floating point value
   */
  float64_t seconds() const {
    return static_cast<float64_t>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(duration_)
                   .count()) *
           1e-9;
  }

  /**
   * @brief Returns a duration in milliseconds.
   *
   * @return float64_t milliseconds given as a floating point value
   */
  float64_t milliseconds() const {
    return static_cast<float64_t>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(duration_)
                   .count()) *
           1e-6;
  }

  /**
   * @brief Returns a duration in nanoseconds.
   *
   * @return int64_t nanoseconds given as an integer value
   */
  int64_t nanoseconds() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration_)
        .count();
  }

  /**
   * @brief Returns the underlying duration.
   *
   * @return duration_t underlying duration
   */
  duration_t duration() const { return duration_; }

  /**
   * @brief Adds another duration to the duration stored.
   *
   * @param[in] other duration to be added
   * @return Duration& reference to the current object
   */
  Duration &operator+=(const Duration &other) {
    duration_ += other.duration_;
    return *this;
  }

  /**
   * @brief Subtracts another duration from the duration stored.
   *
   * @param[in] other duration to be subtracted
   * @return Duration& reference to the current object
   */
  Duration &operator-=(const Duration &other) {
    duration_ -= other.duration_;
    return *this;
  }

  /**
   * @brief Sleeps in current thread on basis of the currently stored duration.
   *
   * @return true if sleeping worked, false otherwise
   */
  bool sleep() const {
    if (duration_ <= duration_t{}) {
      return false;
    }
    std::this_thread::sleep_for(duration_);
    return true;
  }

  /**
   * @brief Returns if the currently store duration is 0.
   *
   * @return true if stored duration is zero, false otherwise
   */
  bool isZero() const { return duration_.count() == 0l; }

private:
  /// @brief duration that shall be stored.
  duration_t duration_{};
};
} // namespace cslibs_time

/**
 * @brief Addition of durations.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return cslibs_time::Duration resulting duration
 */
inline cslibs_time::Duration operator+(const cslibs_time::Duration &a,
                                       const cslibs_time::Duration &b) {
  return cslibs_time::Duration(a.duration() + b.duration());
}

/**
 * @brief Subtraction of durations.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return cslibs_time::Duration resulting duration
 */
inline cslibs_time::Duration operator-(const cslibs_time::Duration &a,
                                       const cslibs_time::Duration &b) {
  return cslibs_time::Duration(a.duration() - b.duration());
}

/**
 * @brief Scaling of durations.
 *
 * @param[in] a duration operand
 * @param[in] s scale
 * @return cslibs_time::Duration resulting duration
 */
inline cslibs_time::Duration operator*(const cslibs_time::Duration &a,
                                       const float64_t s) {
  return cslibs_time::Duration(static_cast<int64_t>(
      std::floor(static_cast<float64_t>(a.nanoseconds()) * s)));
}

/**
 * @brief Scaling of durations.
 *
 * @param[in] s scale
 * @param[in] a duration operand
 * @return cslibs_time::Duration resulting duration
 */
inline cslibs_time::Duration operator*(const float64_t s,
                                       const cslibs_time::Duration &a) {
  return cslibs_time::Duration(static_cast<int64_t>(
      std::floor(static_cast<float64_t>(a.nanoseconds()) * s)));
}

/**
 * @brief Division of durations by a factor.
 *
 * @param[in] a duration operand
 * @param[in] s divisor / inverse scale
 * @return cslibs_time::Duration resulting duration
 */
inline cslibs_time::Duration operator/(const cslibs_time::Duration &a,
                                       const float64_t s) {
  return cslibs_time::Duration(static_cast<int64_t>(
      std::floor(static_cast<float64_t>(a.nanoseconds()) / s)));
}

/**
 * @brief Equality of two durations.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return true if both operands are equal, false otherwise
 */
inline bool operator==(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() == b.duration();
}

/**
 * @brief Inequality of two durations.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return true if both operands are not equal, false otherwise
 */
inline bool operator!=(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() != b.duration();
}

/**
 * @brief Comparison for whether one duration is less equal than another.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return true if a <= b, false otherwise
 */
inline bool operator<=(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() <= b.duration();
}

/**
 * @brief Comparison for whether one duration is larger equal than another.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return true if a >= b, false otherwise
 */
inline bool operator>=(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() >= b.duration();
}

/**
 * @brief Comparison for whether one duration is larger than another.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return true if a > b, false otherwise
 */
inline bool operator>(const cslibs_time::Duration &a,
                      const cslibs_time::Duration &b) {
  return a.duration() > b.duration();
}

/**
 * @brief Comparison for whether one duration is less than another.
 *
 * @param[in] a first operand
 * @param[in] b second operand
 * @return true if a < b, false otherwise
 */
inline bool operator<(const cslibs_time::Duration &a,
                      const cslibs_time::Duration &b) {
  return a.duration() < b.duration();
}

/**
 * @brief Defintion for output streams making the ta duration printable.
 *
 * @param[in] out output stream
 * @param[in] duration value to be moved to output stream
 * @return std::ostream& the output stream
 */
inline std::ostream &operator<<(std::ostream &out,
                                const cslibs_time::Duration &duration) {
  out << "[" << std::to_string(duration.seconds()) << "]";
  return out;
}
