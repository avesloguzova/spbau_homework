#include <stddef.h>
#include <exception>
#include <stdexcept>

namespace utils {

    struct empty_t {


    };

    struct bad_maybe_value : std::runtime_error {
        bad_maybe_value() : runtime_error("so bad") {
        }

    };

    static const empty_t empty;

    template<typename T>
    class maybe {
        char data_[sizeof(T)];
        bool is_empty;

        template<typename V>
        friend void swap(maybe<V> &, maybe<V> &);

    public:
        maybe();

        maybe(empty_t);

        maybe(const T &value);

        maybe(const maybe &);

        ~maybe();

        explicit operator bool() const {
            return !is_empty;
        }

        explicit operator bool() {
            return !is_empty;
        }

        maybe &operator=(maybe);

        maybe &operator=(const empty_t &);

        maybe &operator=(const T &);


        T &get();

        const T &get() const;

        T *get_pointer();

        T const *get_pointer() const;


        T *operator->();

        T const *operator->() const;

        T &operator*();

        T &operator*() const;

        bool operator!();


        bool is_initialized();

        T &value();

        T const &value() const;

        void reset();
    };

    template<typename T>
    void swap(maybe<T> &first, maybe<T> &secound) {
        std::swap(first.data_, secound.data_);
        std::swap(first.is_empty, secound.is_empty);
    }

    template<typename T>
    maybe<T>::maybe() {

        is_empty = true;
    }

    template<typename T>
    maybe<T>::maybe(empty_t empty) {
        is_empty = true;
    }

    template<typename T>
    maybe<T>::maybe(const T &value) {
        new(data_) T(value);
        is_empty = false;
    }

    template<typename T>
    maybe<T>::maybe(maybe const &other) {
        is_empty = other.is_empty;
        if (!is_empty)
            new(data_) T(other.get());

    }

    template<typename T>
    maybe<T>::~maybe() {
        if (!is_empty) {
            reset();
        }
    }


    template<typename T>
    maybe<T> &maybe<T>::operator=(const empty_t &empty) {
        is_empty = true;
    }

    template<typename T>
    maybe<T> &maybe<T>::operator=(maybe other) {
        swap<T>(*this, other);
        return *this;

    }

    template<typename T>
    maybe<T> &maybe<T>::operator=(const T &value) {
        if (!is_empty) {
            reset();
        }
        is_empty = false;
        new(data_) T(value);
    }

    template<typename T>
    T &maybe<T>::get() {
        return *get_pointer();
    }

    template<typename T>
    const T &maybe<T>::get() const {
        return *(get_pointer());
    }

    template<typename T>
    T *maybe<T>::get_pointer() {
        return reinterpret_cast<T *>(data_);
    }

    template<typename T>
    T const *maybe<T>::get_pointer() const {
        return reinterpret_cast<T const *>(data_);
    }

    template<typename T>
    T *maybe<T>::operator->() {
        return get_pointer();
    }

    template<typename T>
    const T *maybe<T>::operator->() const {
        return get_pointer();
    }

    template<typename T>
    T &maybe<T>::operator*() {
        return get();
    }

    template<typename T>
    T &maybe<T>::operator*() const {
        return get();
    }

    template<typename T>
    bool maybe<T>::operator!() {
        return is_empty;
    }

    template<typename T>
    bool maybe<T>::is_initialized() {
        return !is_empty;
    }

    template<typename T>
    T &maybe<T>::value() {
        if (is_empty)
            throw bad_maybe_value();
        return get();
    }

    template<typename T>
    T const &maybe<T>::value() const {
        if (is_empty)
            throw bad_maybe_value();
        return get();
    }

    template<typename T>
    void maybe<T>::reset() {
        is_empty = true;
        T p = get();
        p.~T();
    }
}