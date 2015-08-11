//
// Created by Sasha on 4/29/15.
//

#ifndef DATA_MONITIR_H
#define DATA_MONITIR_H

#include <mutex>
namespace thread_ops
{
    typedef std::recursive_mutex mutex_t;
    template<class T>
    class data_monitor
    {
    public:
        data_monitor(const data_monitor &) = delete;

        data_monitor &operator=(const data_monitor &) = delete;

        data_monitor(T &, mutex_t& mutex);

        T &operator*() const;

        T *operator->() const;

    private:
        std::unique_lock<mutex_t> mutex_;
        std::unique_ptr<T> obj_;
    };

    template<class T>
    class tread_safe_obj
    {
    public:
        tread_safe_obj(T& object);
        data_monitor<T> monitor();

        data_monitor<T> const_monitor() const;

    private:
        T obj_;
         mutex_;

    };

    template<class T>
    data_monitor::data_monitor(T &t, mutex_t& mutex)
            : obj_(&t),
            mutex_(mutex)
    {
    }

    template<class T>
    data_monitor::data_monitor(data_monitor const &aConst)
    {

    }
    template<class T>
    data_monitor &data_monitor::operator=(data_monitor const &aConst)
    {
        return <#initializer#>;
    }
    template<class T>
    T &data_monitor::operator*() const
    {
        return <#initializer#>;
    }
    template<class T>
    T *data_monitor::operator->() const
    {
        return nullptr;
    }
    template<class T>
    data_monitor<T> tread_safe_obj::monitor()
    {
        return data_monitor<T>(obj_,mutex_);
    }
    template<class T>
    const data_monitor<T> tread_safe_obj::const_monitor() const
    {
        return  data_monitor<T>(obj_,mutex_);
    }
    template<class T>
    tread_safe_obj::tread_safe_obj(T & object):obj_(object),mutex_()
    {

    }
}
#endif //DATA_MONITIR_H
