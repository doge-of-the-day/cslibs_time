#pragma once

#include <cslibs_time/duration.hpp>
#include <cslibs_time/numeric_types.hpp>
#include <cslibs_time/time.hpp>

namespace cslibs_time {
/**
 * @brief Class representing a rate in Hz. It is featured by functionality to
 *        sleep in a thread to achieve the desired rate.
 */
class Rate {
public:
  /// @brief underlying clock type
  using clock_t = std::chrono::high_resolution_clock;
  /// @brief underlying time type
  using time_t = clock_t::time_point;
  /// @brief underlying duration type
  using duration_t = clock_t::duration;

  /**
   * @brief Default constructor
   *        Initialization with current system time
   */
  explicit Rate() : start_{Time::now()} {}

  /**
   * @brief Constructor
   *
   * @param[in] rate rate given in Hz
   */
  explicit Rate(const float64_t rate)
      : start_{Time::now()}, desired_cycle_time_{1.0 / rate} {}

  /**
   * @brief Constructor
   *
   * @param[in] d duration representing the inverse rate
   */
  explicit Rate(const Duration &d)
      : start_{Time::now()}, desired_cycle_time_{d} {}

  /**
   * @brief Resets the rate
   */
  void reset() { start_ = Time::now(); }

  /**
   * @brief Returns the cycle time
   *
   * @return Duration, the current cycle time
   */
  Duration cycleTime() const { return actual_cycle_time_; }

  /**
   * @brief Returns the expected or desired cycle time.
   *
   * @return Duration the desired cycle time
   */
  Duration desiredCycleTime() const { return desired_cycle_time_; }

  /**
   * @brief The frequency in Hz.
   *
   * @return float64_t the frequency of the rate
   */
  float64_t frequency() const { return 1.0 / desiredCycleTime().seconds(); }

  /**
   * @brief Sleep function to achieve rate stored in the object.
   *
   * @return true if sleeping functionality was executed validly, false if the
   * methods slept long enough already
   */
  bool sleep() {
    const Time actual_end{Time::now()};
    Time expected_end{start_ + desired_cycle_time_};

    if (actual_end < start_) {
      expected_end = actual_end + desired_cycle_time_;
    }

    const Duration sleep_duration{expected_end - actual_end};
    actual_cycle_time_ = actual_end - start_;
    start_ = expected_end;

    if (sleep_duration <= Duration{}) {
      if (actual_end > expected_end + desired_cycle_time_) {
        start_ = actual_end;
      }
      return false;
    }

    return sleep_duration.sleep();
  }

private:
  /// @brief time at which rate cycle was started
  Time start_;
  /// @brief current state of the cycle time
  Duration actual_cycle_time_{};
  /// @brief desired cycle time
  Duration desired_cycle_time_{std::numeric_limits<float64_t>::infinity()};
};
} // namespace cslibs_time
