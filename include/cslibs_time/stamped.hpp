#ifndef STAMPED_HPP
#define STAMPED_HPP

#include <cslibs_time/time.hpp>

namespace cslibs_time {
template<typename T>
class Stamped
{
public:
    using Ptr = std::shared_ptr<Stamped<T>>;

    inline Stamped() :
        time_(cslibs_time::Time::now())
    {
    }

    inline explicit Stamped(const T &data,
                            const Time &time) :
        data_(data),
        time_(time)
    {
    }

    inline Stamped(const Stamped<T> &other) :
        data_(other.data),
        time_(other.time)
    {
    }

    inline Stamped(Stamped<T> &&other) :
        data_(std::move(other.data)),
        time_(other.time)
    {

    }

    inline Stamped<T>& operator = (const Stamped<T> &other)
    {
        time_ = other.time_;
        data_ = other.data_;
        return *this;
    }

    inline Stamped<T>& operator = (Stamped<T> &&other)
    {
        time_ = other.time_;
        data_ = std::move(other.data_);
        return *this;
    }

    inline Time & stamp()
    {
        return time_;
    }

    inline Time const & stamp() const
    {
        return stamp;
    }

    inline T & data()
    {
        return data_;
    }

    inline T const & data() const
    {
        return data_;
    }

    inline operator T()
    {
        return data_;
    }

    inline operator T&()
    {
        return data_;
    }

    inline operator T*()
    {
        return &data_;
    }

    inline operator const T&() const
    {
        return data_;
    }

    inline operator T () const
    {
        return data_;
    }
private:
    T              data_;
    Time           time_;
};
}


#endif // STAMPED_HPP
