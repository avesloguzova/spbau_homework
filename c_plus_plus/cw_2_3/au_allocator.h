//
// Created by av on 5/20/15.
//

#ifndef CW_2_3_AU_ALLOCATOR_H
#define CW_2_3_AU_ALLOCATOR_H


#include <stddef.h>
#include <exception>
#include <vector>
#include <map>
using std::map;
using std::vector;


struct allocation{
    size_t size_;
    void* ptr_;
    allocation(size_t size, void* ptr_):
            size_(size),
            ptr_(ptr_)
    {

    }
};
struct au_allocator
{
    explicit au_allocator(size_t max_order=7);
    virtual ~au_allocator();

    void* allocate(size_t size);
    template<class T, class ...CONSTR_PARAMS>
    T* allocate(CONSTR_PARAMS... constr_params);

    void deallocate(void *ptr, size_t size);
    template<class T>
    void deallocate(T* const ptr);

private:
    const size_t DEFAULT_POOL_SIZE = 100;
    typedef vector<void*> pool;
   vector<pool> pools_free_;
    vector<allocation> free_;
    size_t max_order_;

    static size_t getExponent(size_t value)
    {
        size_t exponent = 0;
        while((value = value >> 1))
        {
            ++exponent;
        }
        return exponent;
    }
};

template<class T, class ...CONSTR_PARAMS>
T *au_allocator::allocate(CONSTR_PARAMS... constr_params) {
    void* mem = allocate(sizeof(T));
    if(mem!= nullptr){
        return new (mem) T (std::forward<CONSTR_PARAMS>(constr_params)...);
    }else{
        return nullptr;
    }
}

template<class T>
void au_allocator::deallocate(T *const ptr) {
    ptr-> T::~T();
    deallocate(ptr,sizeof(ptr));
}

#endif //CW_2_3_AU_ALLOCATOR_H
