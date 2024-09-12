#pragma once

#include <ros/rate.h>
#include <ros/time.h>

#include <cslibs_time/duration.hpp>
#include <cslibs_time/rate.hpp>
#include <cslibs_time/time.hpp>
#include <cslibs_time/time_frame.hpp>

namespace cslibs_time {
/// @brief Time frame consisting of two ros::Time objects.
using ros_time_frame_t = std::pair<ros::Time, ros::Time>;

// FROM ROS
/**
 * @brief Creates cslibs_time::Time from a ros::Time.
 *
 * @param[in] t ros::Time object
 * @return Time cslibs_time::Time object
 */
inline Time from(const ros::Time &t) { return Time(t.toNSec()); }

/**
 * @brief Create cslibs_time::Duration from a ros::Duration.
 *
 * @param[in] d ros::Duration object
 * @return Duration cslibs_time::Duration object
 */
inline Duration from(const ros::Duration &d) { return Duration(d.toNSec()); }

/**
 * @brief Creates cslibs_time::TimeFrame from ros::Time objects.
 *
 * @param[in] t_start start timestamp as ros::Time
 * @param[in] t_end end timestamp as ros::Time
 * @return TimeFrame cslibs_time::TimeFrame object
 */
inline TimeFrame from(const ros::Time &t_start, const ros::Time &t_end) {
  return TimeFrame{from(t_start), from(t_end)};
}

/**
 * @brief Creates cslibs_time::TimeFrame from ros::Time frame.
 *
 * @param[in] f time frame on basis of ros::Time objects
 * @return TimeFrame cslibs_time::TimeFrame object
 */
inline TimeFrame from(const ros_time_frame_t &f) {
  return TimeFrame{from(f.first), from(f.second)};
}

/**
 * @brief Create cslibs_time::Rate object from a ros::Rate.
 *
 * @param[in] r rate given as ros::Rate
 * @return Rate cslibs_time::Rate object
 */
inline Rate from(const ros::Rate &r) {
  return Rate{from(r.expectedCycleTime())};
}

/**
 * @brief Sets cslibs_time::Time object from ros::Time.
 *
 * @param[in] t_src ros::Time source object
 * @param[in,out] t_dst cslibs_time::Time destination object
 */
inline void from(const ros::Time &t_src, Time &t_dst) {
  t_dst = Time{t_src.toNSec()};
}

/**
 * @brief Sets cslibs_time::Duration object from ros::Duration.
 *
 * @param[in] d_src ros::Duration source object
 * @param[in,out] d_dst cslibs_time::Duration destination object
 */
inline void from(const ros::Duration &d_src, Duration &d_dst) {
  d_dst = Duration{d_src.toNSec()};
}

/**
 * @brief Sets cslibs_time::Rate object from ros::Rate.
 *
 * @param[in] r_src ros::Rate source object
 * @param[in,out] r_dst cslibs_time::Rate destination object
 */
inline void from(const ros::Rate &r_src, Rate r_dst) {
  r_dst = Rate{from(r_src.expectedCycleTime())};
}

// TO ROS
/**
 * @brief Create ros::Time from cslibs_time::Time
 *
 * @param[in] t cslibs_time::Time object
 * @return ros::Time object
 */
inline ros::Time from(const Time &t) {
  const int64_t ns = t.nanoseconds();
  const uint32_t s = ns / static_cast<uint32_t>(1e9);
  const uint32_t n = ns - s * 1e9;
  return ros::Time(s, n);
}

/**
 * @brief Create ros::Duration from cslibs_time::Time
 *
 * @param[in] d cslibs_time::Duration object
 * @return ros::Duration object
 */
inline ros::Duration from(const Duration &d) {
  const int64_t ns = d.nanoseconds();
  const uint32_t s = ns / static_cast<uint32_t>(1e9);
  const uint32_t n = ns - s * 1e9;
  return ros::Duration(s, n);
}

/**
 * @brief Create ros time frame from cslibs_time::TimeFrame
 *
 * @param[in] t cslibs_time::TimeFrame object
 * @return ros::Duration object
 */
inline ros_time_frame_t from(const TimeFrame &t) {
  return {from(t.start), from(t.end)};
}

/**
 * @brief Create ros time frame from cslibs_time::Rate
 *
 * @param[in] r cslibs_time::Rate object
 * @return ros::Rate object
 */
inline ros::Rate from(const Rate &r) { return ros::Rate(r.frequency()); }

/**
 * @brief Sets ros::Time from cslibs_time::Time object.
 *
 * @param[in] t_src cslibs_time::Time object
 * @param[in,out] t_dst ros::Time object
 */
inline void from(const Time &t_src, ros::Time &t_dst) {
  t_dst.fromNSec(t_src.nanoseconds());
}

/**
 * @brief Sets ros::Duration from cslibs_time::Duration object.
 *
 * @param[in] d_src cslibs_time::Duration object
 * @param[in,out] d_dst ros::Duration object
 */
inline void from(const Duration &d_src, ros::Duration &d_dst) {
  d_dst.fromNSec(d_src.nanoseconds());
}

/**
 * @brief Extracts start and end time from a cslibs::TimeFrame object to
 * ros::Time objects.
 *
 * @param[in] f cslibs::TimeFrame source object
 * @param[in,out] t_start ros::Time destination object
 * @param[in,out] t_end ros::Time destination object
 */
inline void from(const TimeFrame &f, ros::Time &t_start, ros::Time &t_end) {
  t_start.fromNSec(f.start.nanoseconds());
  t_end.fromNSec(f.end.nanoseconds());
}

/**
 * @brief Sets ros::Rate object from cslibs_time::Rate.
 *
 * @param[in] r_src cslibs_time::Rate source object
 * @param[in,out] r_dst ros::Rate destination object
 */
inline void from(const Rate &r_src, ros::Rate r_dst) {
  r_dst = ros::Rate(from(r_src.desiredCycleTime()));
}
} // namespace cslibs_time
