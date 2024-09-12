#pragma once

#include <cslibs_time/time.hpp>
#include <cslibs_time/numeric_types.hpp>
#include <string>

namespace cslibs_time {
/// @brief Class to represent a temporal interval
struct TimeFrame {
  /// @brief Start of the temporal interval
  const Time start;
  /// @brief End of the temporal interval
  const Time end;

  /**
   * @brief Constructor
   *        using the current point in time with interval length of 0s.
   */
  explicit TimeFrame() : start{Time::now()}, end{start} {}

  /**
   * @brief Constructor
   * @param[in] start_seconds start timestamp of the interval represented as seconds
   * @param[in] end_seconds end timestamp of the interval represented as seconds
   */
  TimeFrame(const float64_t start_seconds, const float64_t end_seconds)
      : start{start_seconds}, end{end_seconds} {}

  /**
   * @brief Constructor
   * @param[in] start_nanoseconds start timestamp of the interval represented as nanoseconds
   * @param[in] end_nanoseconds end timestamp of the interval represented as nanoseconds
   */
  TimeFrame(const int64_t &start_nanoseconds, const int64_t &end_nanoseconds)
      : start{start_nanoseconds}, end{end_nanoseconds} {}

  /**
   * @brief Constructor
   * @param[in] start_nanoseconds start timestamp of the interval represented as nanoseconds
   * @param[in] end_nanoseconds end timestamp of the interval represented as nanoseconds
   */
  TimeFrame(const uint64_t &start_nanoseconds, const uint64_t &end_nanoseconds)
      : start{start_nanoseconds}, end{end_nanoseconds} {}

  /**
   * @brief Constructor
   * @param[in] start_time start timestamp of the interval represented as the underlying time type
   * @param[in] end_time end timestamp of the interval represented as the underlying time type
   */
  TimeFrame(const Time::time_t &start_time, const Time::time_t &end_time)
      : start{start_time}, end{end_time} {}

  /**
   * @brief Constructor
   * @param[in] start_time start timestamp of the interval represented as Time
   * @param[in] end_time end timestamp of the interval represented as Time
   */
  TimeFrame(const Time &start_time, const Time &end_time)
      : start{start_time}, end{end_time} {}

  /// @brief Copy constructor
  TimeFrame(const TimeFrame &) = default;
  /// @brief Move constructor
  TimeFrame(TimeFrame &&) = default;

  /**
   * @brief Conducts an inclusive check whether a time is defined within the temporal interval.
   * @param[in] time operand to be checked
   * @return true if time >= start && time <= end, false otherwise
   */
  bool within(const Time &time) const { return time >= start && time <= end; }

  /**
   * @brief Returns the duration of the interval.
   * @return Duration duration representing the delta of start and end
   */
  Duration duration() const { return Duration{end.time() - start.time()}; }
};
} // namespace cslibs_time

/**
 * @brief Defintion for output streams making the time frame printable.
 *
 * @param[in] out output stream
 * @param[in] time_span value to be moved to output stream
 * @return std::ostream& the output stream
 */
inline std::ostream &operator<<(std::ostream &out,
                                const cslibs_time::TimeFrame &time_span) {
  out << "[" << time_span.start << "," << time_span.end << "]";
  return out;
}
