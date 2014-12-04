#include "singleton.h"

std::weak_ptr<util::singleton> util::singleton::p_instance;

std::shared_ptr<util::singleton> util::singleton::get_instance()
{
    if(!p_instance.expired()){
        return p_instance.lock();
    }else{
        p_instance.reset();
        std::shared_ptr<util::singleton> p_tmp (new singleton());
        p_instance = std::weak_ptr<util::singleton>(p_tmp);
        return p_tmp;
    }
}