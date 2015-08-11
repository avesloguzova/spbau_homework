template<typename T>
class linked_ptr{
    linked_ptr()noexcept;
    linked_ptr(T*)noexcept;
    linked_ptr(const linked_ptr<T> & )noexcept;
    template <typename U>
    linked_ptr(U*);
    template <typename U>
    linked_ptr(linked_ptr<U>   );
    void swap (linked_ptr<T>&)noexcept;
    T get() noexcept;
    T get() const noexcept;
    bool unique() const noexcept;
    T operator *();
    T operator ->();
    T operator *() const;
    T operator ->()const ;
    bool operator == (const linked_ptr<T> &);
    explicit operator bool() const;
    explicit operator bool() ;



};