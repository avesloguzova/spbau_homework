//
// Created by Sasha on 4/8/15.
//

#ifndef CW2_2_SERIALIZATION_H
#define CW2_2_SERIALIZATION_H

#include <type_traits>
#include <sstream>
#include "io_streams.h"
#include "dict.h"
namespace serialization
{

    template <class T>
    void write( output_stream & os, const T& elem, typename std::enable_if<std::is_pod<T>::value>::type* = nullptr){
        os.write(&elem, sizeof(T));
    }

    template <class T>
    void read(input_stream& is, T& elem,typename std::enable_if<std::is_pod<T>::value>::type* = nullptr){
        is.read(&elem, sizeof(T));
    }

    template <class T>
    void write( dict& d, const T& elem,typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr){
        std::stringstream s;
        s<<elem;
        d.value = s.str();
    }
    template <class T>
    void write( dict& d, const T& elem,typename std::enable_if<!std::is_arithmetic<T>::value>::type* = nullptr){
        serialize(d, const_cast<T&>(elem));
    }

    template <class T>
    void read(const dict& d, T& elem,typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr ){
        std::stringstream s(d.value);
        s>>elem;
    }
    template <class T>
    void read(const dict& d, T& elem,typename std::enable_if<!std::is_arithmetic<T>::value>::type* = nullptr ){
        serialize(d,elem);
    }

    template <class T>
    void write(output_stream& os, const T& elem, typename std::enable_if<!std::is_pod<T>::value>::type* = nullptr){
        serialize(os, const_cast<T&>(elem));
    }

    template <class T>
    void read(input_stream& is, T& elem,typename std::enable_if<!std::is_pod<T>::value>::type* = nullptr){
        serialize(is,elem);
    }

    template <class T>
    void serialize(input_stream& is, T& elem,typename std::enable_if<std::is_pod<T>::value>::type* = nullptr){
        read(is,elem);
    }

    template <class T>
    void serialize(output_stream& os, T& elem,typename std::enable_if<std::is_pod<T>::value>::type* = nullptr){
        write(os,elem);
    }

    template <class T>
    void serialize(dict& d, T& elem, const std::string& key ,typename std::enable_if<!std::is_arithmetic<T>::value>::type* = nullptr){
        serialize(d.children[key],elem);
    }
    template <class T>
    void serialize(const dict& d, T& elem, const std::string& key ,typename std::enable_if<!std::is_arithmetic<T>::value>::type* = nullptr){
        serialize(d.children.at(key),elem);
    }

    template <class T>
    void serialize(dict& d, T& elem,const std::string& key, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr){
        write(d.children[key],elem);
    }
    template <class T>
    void serialize(const dict& d, T& elem,const std::string& key, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr){
        read(d.children.at(key),elem);
    }




}
#endif //CW2_2_SERIALIZATION_H
