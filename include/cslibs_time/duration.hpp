#pragma once

#include <chrono>
#include <cmath>
#include <ostream>
#include <thread>

namespace cslibs_time {
class Duration {
public:
  using clock_t = std::chrono::high_resolution_clock;
  using time_t = clock_t::time_point;
  using duration_t = clock_t::duration;

  explicit Duration() : duration_(0l) {}

  explicit inline Duration(const double seconds)
      : duration_(static_cast<int64_t>(std::floor(seconds * 1e9))) {}

  explicit inline Duration(const int64_t nanoseconds)
      : duration_(nanoseconds) {}

  explicit Duration(const duration_t duration) : duration_(duration) {}

  Duration(const Duration &) = default;
  Duration(Duration &&) = default;

  Duration &operator=(const Duration &) = default;
  Duration &operator=(Duration &&) = default;

  double seconds() const {
    return static_cast<double>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(duration_)
                   .count()) *
           1e-9;
  }

  double milliseconds() const {
    return static_cast<double>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(duration_)
                   .count()) *
           1e-6;
  }

  int64_t nanoseconds() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration_)
        .count();
  }

  duration_t duration() const { return duration_; }

  Duration &operator+=(const Duration &other) {
    duration_ += other.duration_;
    return *this;
  }

  Duration &operator-=(const Duration &other) {
    duration_ -= other.duration_;
    return *this;
  }

  bool sleep() const {
    if (duration_ <= duration_t(0))
      return false;
    std::this_thread::sleep_for(duration_);
    return true;
  }

  bool isZero() const { return duration_.count() == 0l; }

private:
  duration_t duration_;
};
} // namespace cslibs_time

inline cslibs_time::Duration operator+(const cslibs_time::Duration &a,
                                       const cslibs_time::Duration &b) {
  return cslibs_time::Duration(a.duration() + b.duration());
}

inline cslibs_time::Duration operator-(const cslibs_time::Duration &a,
                                       const cslibs_time::Duration &b) {
  return cslibs_time::Duration(a.duration() - b.duration());
}

inline cslibs_time::Duration operator*(const cslibs_time::Duration &a,
                                       const cslibs_time::Duration &b) {
  return cslibs_time::Duration(a.nanoseconds() * b.nanoseconds());
}

inline cslibs_time::Duration operator*(const cslibs_time::Duration &a,
                                       const double s) {
  return cslibs_time::Duration(static_cast<int64_t>(
      std::floor(static_cast<double>(a.nanoseconds()) * s)));
}

inline cslibs_time::Duration operator*(const double s,
                                       const cslibs_time::Duration &a) {
  return cslibs_time::Duration(static_cast<int64_t>(
      std::floor(static_cast<double>(a.nanoseconds()) * s)));
}

inline cslibs_time::Duration operator/(const cslibs_time::Duration &a,
                                       const double s) {
  return cslibs_time::Duration(static_cast<int64_t>(
      std::floor(static_cast<double>(a.nanoseconds()) / s)));
}

inline bool operator==(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() == b.duration();
}

inline bool operator!=(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() != b.duration();
}

inline bool operator<=(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() <= b.duration();
}

inline bool operator>=(const cslibs_time::Duration &a,
                       const cslibs_time::Duration &b) {
  return a.duration() >= b.duration();
}

inline bool operator>(const cslibs_time::Duration &a,
                      const cslibs_time::Duration &b) {
  return a.duration() > b.duration();
}

inline bool operator<(const cslibs_time::Duration &a,
                      const cslibs_time::Duration &b) {
  return a.duration() < b.duration();
}

inline std::ostream &operator<<(std::ostream &out,
                                const cslibs_time::Duration &duration) {
  out << "[" << std::to_string(duration.seconds()) << "]";
  return out;
}
