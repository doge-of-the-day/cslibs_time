#pragma once

#include <cslibs_time/duration.hpp>
#include <cslibs_time/numeric_types.hpp>
#include <ctime>
#include <ostream>
#include <assert.h>

namespace cslibs_time {
class Time {
public:
  /// @brief underlying clock type
  using clock_t = std::chrono::high_resolution_clock;
  /// @brief underlying time type
  using time_t = clock_t::time_point;
  /// @brief underlying duration type
  using duration_t = clock_t::duration;

  /// @brief default constructor
  explicit Time() = default;

  /**
   * @brief Constructor
   *
   * @param[in] seconds timestamp represented by seconds
   */
  explicit Time(const float64_t seconds)
      : time_(std::chrono::nanoseconds(static_cast<int64_t>(seconds * 1e9))) {}

  /**
   * @brief Constructor
   *
   * @param[in] nanoseconds timestamp represented by nanoseconds
   */
  explicit Time(const int64_t &nanoseconds) : time_(duration_t(nanoseconds)) {}

  explicit Time(const uint64_t &nanoseconds)
      : time_(duration_t(static_cast<int64_t>(nanoseconds))) {
    assert(static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) >
           nanoseconds);
  }

  /**
   * @brief Constructor
   *
   * @param[in] time timestamp as underlying time type
   */
  explicit Time(const time_t &time) : time_{time} {}

  /// @brief Copy constructor
  Time(const Time &) = default;
  /// @brief Move constructor
  Time(Time &&) = default;

  /// @brief Copy assignment
  Time &operator=(const Time &) = default;
  /// @brief Move assignment
  Time &operator=(Time &&) = default;

  /**
   * @brief Returns the underlying time value.
   *
   * @return time_t const& underlying time
   */
  time_t const &time() const { return time_; }

  /**
   * @brief Returns underlying time in seconds.
   *
   * @return float64_t
   */
  float64_t seconds() const {
    return static_cast<float64_t>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(
                   time_.time_since_epoch())
                   .count()) *
           1e-9;
  }

  /**
   * @brief Returns the underlying time in nanoseconds.
   */
  int64_t nanoseconds() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               time_.time_since_epoch())
        .count();
  }

  /**
   * @brief Returns if time is zero
   *
   * @return true if time is zero, false otherwise
   */
  bool isZero() const { return time_ == time_t(duration_t{}); }

  /**
   * @brief Creates time using the current system time.
   *
   * @return Time constructed time object
   */
  static Time now() { return Time(clock_t::now()); }

private:
  /// @brief time value
  time_t time_{};
};
} // namespace cslibs_time

/**
 * @brief Checks two times for equality.
 *
 * @param[in] a first operand of comparison
 * @param[in] b sedond operato of comparison
 * @return true if two times are equal, false otherwise
 */
inline bool operator==(const cslibs_time::Time &a, const cslibs_time::Time &b) {
  return a.time() == b.time();
}

/**
 * @brief Checks two times for inequality.
 *
 * @param[in] a first operand of comparison
 * @param[in] b sedond operato of comparison
 * @return true if two times are inequal, false otherwise
 */
inline bool operator!=(const cslibs_time::Time &a, const cslibs_time::Time &b) {
  return a.time() != b.time();
}

/**
 * @brief Checks if a time is less equal compared to another.
 *
 * @param[in] a first operand of comparison
 * @param[in] b sedond operato of comparison
 * @return true if a <= b, false otherwise
 */
inline bool operator<=(const cslibs_time::Time &a, const cslibs_time::Time &b) {
  return a.time() <= b.time();
}

/**
 * @brief Checks if a time is greater equal compared to another.
 *
 * @param[in] a first operand of comparison
 * @param[in] b sedond operato of comparison
 * @return true if a >= b, false otherwise
 */
inline bool operator>=(const cslibs_time::Time &a, const cslibs_time::Time &b) {
  return a.time() >= b.time();
}

/**
 * @brief Checks if a time is greater than another.
 *
 * @param[in] a first operand of comparison
 * @param[in] b sedond operato of comparison
 * @return true if a > b, false otherwise
 */
inline bool operator>(const cslibs_time::Time &a, const cslibs_time::Time &b) {
  return a.time() > b.time();
}

/**
 * @brief Checks if a time is smaller than another.
 *
 * @param[in] a first operand of comparison
 * @param[in] b sedond operato of comparison
 * @return true if a < b, false otherwise
 */
inline bool operator<(const cslibs_time::Time &a, const cslibs_time::Time &b) {
  return a.time() < b.time();
}

/**
 * @brief Subtracts a time from another.
 *
 * @param[in] a first operand of subtraction
 * @param[in] b second operand of the subtraction
 * @return cslibs_time::Duration duration representing the delta
 */
inline cslibs_time::Duration operator-(const cslibs_time::Time &a,
                                       const cslibs_time::Time &b) {
  return cslibs_time::Duration{a.time() - b.time()};
}

/**
 * @brief Subtracts a duration from a time.
 *
 * @param[in] a first operand of subtraction
 * @param[in] b second operand of the subtraction, which is a duration
 * @return cslibs_time::Time resulting time after subtraction
 */
inline cslibs_time::Time operator-(const cslibs_time::Time &t,
                                   const cslibs_time::Duration &d) {
  return cslibs_time::Time{t.time() - d.duration()};
}

/**
 * @brief Subtracts a duration from a time.
 *
 * @param[in] a first operand of subtraction
 * @param[in] b second operand of the subtraction, which is a duration
 * @return cslibs_time::Time resulting time after subtraction
 */
inline cslibs_time::Time operator+(const cslibs_time::Time &t,
                                   const cslibs_time::Duration &d) {
  return cslibs_time::Time{t.time() + d.duration()};
}

/**
 * @brief Defintion for output streams making the time printable.
 *
 * @param[in] out output stream
 * @param[in] time value to be moved to output stream
 * @return std::ostream& the output stream
 */
inline std::ostream &operator<<(std::ostream &out,
                                const cslibs_time::Time &time) {
  const int64_t ns = time.nanoseconds();
  const int64_t s = ns / static_cast<int64_t>(1e9);
  const int64_t ms = (ns % static_cast<int64_t>(1e9));
  out << "<" << std::to_string(s) + "." + std::to_string(ms) << ">";
  return out;
}

namespace std {
/**
 * @brief Defintion of the less functor for times.
 *
 * @tparam template specialization
 */
template <> struct less<cslibs_time::Time> {
  /**
   * @brief The comparison operation.
   *
   * @param[in] lhs left hand side operand
   * @param[in] rhs right hands ide operand
   * @return true if lhs < rhs, false otherwise
   */
  bool operator()(const cslibs_time::Time &lhs,
                  const cslibs_time::Time &rhs) const {
    return lhs.time() < rhs.time();
  }
};
} // namespace std
