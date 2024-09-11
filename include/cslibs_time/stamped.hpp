#pragma once

#include <cslibs_time/time.hpp>

namespace cslibs_time {
template<typename T>
class Stamped
{
public:
    using Ptr = std::shared_ptr<Stamped<T>>;
    using ConstPtr = std::shared_ptr<const Stamped<T>>;

    explicit Stamped() = default;

    explicit Stamped(const Time &time) :
        time_{time}
    {
    }

    explicit Stamped(const T &data,
                     const Time &time) :
        data_{data},
        time_{time}
    {
    }

    Stamped(const Stamped &) = default;
    Stamped(Stamped &&) = default;

    Stamped& operator = (const Stamped &) = default;
    Stamped& operator = (Stamped &&) = default;

    Time & stamp()
    {
        return time_;
    }

    Time const & stamp() const
    {
        return time_;
    }

    T & data()
    {
        return data_;
    }

    T const & data() const
    {
        return data_;
    }

    operator T()
    {
        return data_;
    }

    operator T&()
    {
        return data_;
    }

    operator T*()
    {
        return &data_;
    }

    operator const T&() const
    {
        return data_;
    }

    operator T () const
    {
        return data_;
    }
private:
    T              data_{};
    Time           time_{};
};
}
