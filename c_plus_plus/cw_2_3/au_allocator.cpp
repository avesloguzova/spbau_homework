//
// Created by av on 5/20/15.
//

#include "au_allocator.h"


void * au_allocator::allocate(size_t size) {
    for (int i = 0; i < max_order_ + 1; ++i) {
        if(size<=1<<i){
            pool &current_pool = pools_free_[i];
            if(current_pool.size()>0){
                void* ptr = current_pool.back();
                current_pool.pop_back();
                return ptr;
            }else{
                return malloc( (1u<<getExponent(size)));
            }
        }
    }
    for( auto it = free_.begin();it!=free_.end();++it){
        if(it->size_ >= size){
            void *ptr = it->ptr_;
            free_.erase(it);
            return  ptr;
        }
    }
    return malloc( (1u<<getExponent(size)));//TODO allocate 2^n memory
}
au_allocator::au_allocator(size_t max_order)
        :max_order_(max_order),
         pools_free_(max_order+1)
{
    for (int i = 0; i < max_order + 1; ++i) {
        pool current;
        for (int j = 0; j < DEFAULT_POOL_SIZE; ++j) {
            void* ptr = malloc((size_t) (1<<i));
            if(ptr == 0){
                throw std::runtime_error("Can't create pool");
            }
            current.push_back(ptr);
        }
        pools_free_[i] = current;
    }

}

void au_allocator::deallocate(void *ptr, size_t size) {
    size_t exp = getExponent(size);
    if(exp<= max_order_){
        pools_free_[exp].push_back(ptr);
    }else{
        free_.push_back(allocation(1u<<getExponent(size),ptr));
    }

}

au_allocator::~au_allocator() {
    for (int i = 0; i < max_order_ + 1; ++i){
        pool current = pools_free_[i];
        for (auto pool_it = current.begin();pool_it!=current.end();++pool_it){
            free((*pool_it));
        }
    }
    for(auto it = free_.begin();it!=free_.end();++it){
        free(it->ptr_);
    }
}
