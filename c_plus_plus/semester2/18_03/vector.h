//
// Created by Sasha on 3/18/15.
//



#ifndef _18_03_VECTOR_H_
#define _18_03_VECTOR_H_


#include <memory>

template<class T>
T *new_copy(const T *src, int src_size, int dst_size)
{
    T *dst = new T[dst_size];
    try
    {
        std::copy(src, src + src_size, dst);
    }
    catch (...)
    {
        delete[] dst;
        throw;
    }
    return dst;
}

template<class T>
class vector
{
public:
    vector(int capasity);

    vector(const vector &);

    vector& operator=(vector);

    vector(vector &&) = default;

    vector& operator=(vector &&) = default;

    void push_bask(const T& elem);

    T &operator[](int index);

    const T &operator[](int index) const;

    void swap(vector<T> vec);

    T* begin (){ return buffer;}
    T* end(){return buffer+current_size;}

    ~vector();

private:
    T *buffer;
    int capacity;
    int current_size;


};

template<class T>
void vector<T>::push_bask(const T &elem)
{
    if (current_size == capacity)
    {
        T *copy = new_copy<T>(buffer, current_size, current_size * 2);
        delete[] buffer;
        buffer = copy;
        capacity *= 2;
    }
    buffer[current_size] = elem;
    ++current_size;
}

template<class T>
T &vector<T>::operator[](int index)
{
    return buffer[index];
}

template<class T>
T const &vector<T>::operator[](int index) const
{
    return buffer[index];
}

template<class T>
vector<T>::vector(int capacity)
        : capacity(capacity),
          current_size(0)
{

    buffer = new T[capacity];
}

template<class T>
vector<T>::vector(vector const &object)
:buffer(new_copy<T>(object.buffer, object.current_size,object.capacity)),
capacity(object.capacity),
current_size(object.current_size)
{

}

template<class T>
vector<T>& vector<T>::operator=(vector other)
{
    swap(other);
    return *this;
}

template<class T>
vector<T>::~vector()
{
    delete [] buffer;
}

template<class T>
void vector<T>::swap(vector<T> vec)
{
    T* buf = buffer;
    buffer = vec.buffer;
    std::swap(capacity,vec.capacity);
    std::swap(current_size,vec.current_size);

}

#endif //_18_03_VECTOR_H_
