#include <iostream>
#include "singleton.h"


int main()
{
    std::shared_ptr<util::singleton> s = util::singleton::get_instance();
    s->field = 100;
    std::shared_ptr<util::singleton> s1 = util::singleton::get_instance();
    std::cout<< s->field;
    s.reset();
    s1.reset();
    s = util::singleton::get_instance();
    std::cout<< s->field;
    return 0;
}