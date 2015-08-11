//
// Created by Sasha on 4/1/15.
//
#ifndef _01_04_SERIALIZE_H_
#define _01_04_SERIALIZE_H_

#include <iostream>
#include <type_traits>

namespace serialization
{

    template<class T>
    class is_container
    {
        typedef char yes;
        typedef struct
        {
            yes dm[2];
        } no;

        template<class U,
                 typename U::iterator (U::*)(),
                 typename U::iterator (U::*)()>
        struct checker
        {};

        template<class U>
        static yes check(checker<U,&U::cbegin,&U::cend>*);
        template <class U>
        static no check(...);

    public:
        enum {value = sizeof(check<T>(nullptr))== sizeof(yes)};
    };

    template<class stream, class T>
    void serialize(stream s, T elem, typename std::enable_if<std::is_pod<T>::value>::type* = nullptr )
    {
        s.write(elem);
    }

    template<class stream, class T>
    void serialize(stream s, T elem, typename std::enable_if<is_container::value>::type* = nullptr)
    {
        s.write(elem);
    }

}

#endif //_01_04_SERIALIZE_H_
