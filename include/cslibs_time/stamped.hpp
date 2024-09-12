#pragma once

#include <cslibs_time/time.hpp>

namespace cslibs_time {
/**
 * @brief Wrapper class to add a timestamp to data.
 *
 * @tparam T Data type to wrap
 */
template <typename T> class Stamped {
public:
  ///  @brief Shared pointer type
  using Ptr = std::shared_ptr<Stamped<T>>;
  /// @brief Const shared pointer type
  using ConstPtr = std::shared_ptr<const Stamped<T>>;

  /// @brief Default constructor
  explicit Stamped() = default;

  /**
   * @brief Constructor
   *
   * @param data data to wrap with a timestamp
   * @param time time to bind onto the data
   */
  explicit Stamped(const T &data, const Time &time)
      : data_{data}, time_{time} {}

  /**
   * @brief Constructor moving data
   *
   * @param data data to wrap with a timestamp
   * @param time time to bind onto the data
   */
  explicit Stamped(T &&data, Time &&time) : data_{data}, time_{time} {}

  /// @brief Copy constructor
  Stamped(const Stamped &) = default;
  /// @brief Move constructor
  Stamped(Stamped &&) = default;

  /// @brief Copy assignment
  Stamped &operator=(const Stamped &) = default;
  /// @brief Move assignment
  Stamped &operator=(Stamped &&) = default;

  /**
   * @brief Returns a reference to the timestamp.
   *
   * @return Time& writeable reference to the timestamp
   */
  Time &stamp() { return time_; }

  /**
   * @brief Returns a const reference to the timestamp.
   *
   * @return Time const& const reference to the timestamp
   */
  Time const &stamp() const { return time_; }

  /**
   * @brief Returns reference to the data.
   *
   * @return T& writable reference to the data
   */
  T &data() { return data_; }

  /**
   * @brief Returns const reference to the data.
   *
   * @return T const& const reference to the data
   */
  T const &data() const { return data_; }

  /// @brief Casting operator
  operator T() { return data_; }
  /// @brief Casting operator
  operator T &() { return data_; }
  /// @brief Casting operator
  operator const T &() const { return data_; }
  /// @brief Casting operator
  operator T() const { return data_; }

  /// @brief De-referencing operator
  operator T *() { return &data_; }

private:
  /// @brief data to wrap
  T data_{};
  /// @brief timestamp bound onto the data
  Time time_{};
};
} // namespace cslibs_time
