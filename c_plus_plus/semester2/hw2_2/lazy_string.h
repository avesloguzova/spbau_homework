//
// Created by Sasha on 4/21/15.
//

#ifndef HW2_2_LAZY_STRING_H
#define HW2_2_LAZY_STRING_H

#include <string>
#include <vector>


namespace std_utils
{
    template<class charT,
             class traits>
    class basic_lazy_string;

    template<class charT, class traits = std::char_traits<charT>>
    class proxy
    {
        size_t ind;
        basic_lazy_string<charT, traits> &str;
    public:

        proxy(size_t ind, basic_lazy_string<charT, traits> &string) : ind(ind), str(string)
        {
        }

        proxy &operator=(charT c)
        {
            str.replace(ind, c);
        }

        operator charT() const
        {

            return str.get(ind);
        }

        ~proxy()
        {
        }


    };

    template<class charT,
             class traits = std::char_traits<charT>>
    class basic_lazy_string
    {
    public:

        typedef traits traits_type;
        typedef charT value_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        basic_lazy_string();

        basic_lazy_string(const basic_lazy_string &str);

        basic_lazy_string(basic_lazy_string &&str) noexcept;

        basic_lazy_string(const charT *s);

        basic_lazy_string(const charT &c);

        basic_lazy_string(size_t n, charT c);

        ~basic_lazy_string();

        basic_lazy_string &operator=(const basic_lazy_string &str);

        basic_lazy_string &operator=(const charT *s);

        basic_lazy_string &operator=(charT c);

        basic_lazy_string &operator=(basic_lazy_string &&str);

        basic_lazy_string &operator+=(const basic_lazy_string &str);

        basic_lazy_string &operator+=(const charT *s);

        basic_lazy_string &operator+=(charT c);

        int compare(const basic_lazy_string &str) const noexcept;

        int compare(const charT *s) const noexcept;

        charT get(size_t pose)
        {
            return (*buffer)[pose];
        }

        void replace(size_type ind, charT value);

        proxy<charT, traits> operator[](size_t pos);

        const charT &operator[](size_t pos) const;

        void clear();

        bool empty() const noexcept;

        size_t size() const noexcept;

        const charT *c_str() const;

        void swap(basic_lazy_string<charT, traits> &other);

        bool operator==(const basic_lazy_string &str)
        {
            return compare(str) == 0;
        }

        bool operator!=(const basic_lazy_string &str)
        {
            return !operator==(str);
        }

        bool operator<(const basic_lazy_string &str)
        {
            return compare(str) < 0;
        }

        bool operator>(const basic_lazy_string &str)
        {
            return compare(str) > 0;
        }

        bool operator<=(const basic_lazy_string &str)
        {
            return !operator>(str);
        }

        bool operator>=(const basic_lazy_string &str)
        {
            return !operator<(str);
        }
        basic_lazy_string operator + (basic_lazy_string const& str){
            return basic_lazy_string(*this)+=str;
        }


    private:
        std::shared_ptr<std::basic_string<charT, traits> > buffer;

        void copy_not_unique();
    };

    class itraits : public std::char_traits<char>
    {
    public:
        static int compare(const char *s1, const char *s2, size_t n)
        {
            for (; n; --n, ++s1, ++s2)
            {
                if (std::tolower(*s1) != std::tolower(*s2))
                {
                    return std::tolower(*s1) < std::tolower(*s2) ? -1 : 1;
                }
            }
            return 0;
        }

    };


    typedef basic_lazy_string<char> lazy_string;
    typedef basic_lazy_string<wchar_t> lazy_wstring;
    typedef basic_lazy_string<char, itraits> lazy_istring;

    template<class charT, class traits>
    basic_lazy_string<charT, traits>::basic_lazy_string()
            : buffer(std::make_shared<std::basic_string<charT, traits>>(std::basic_string<charT, traits>()))
    {

    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits>::basic_lazy_string(const basic_lazy_string &str)
            : buffer(str.buffer)
    {
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits>::basic_lazy_string(basic_lazy_string &&str) noexcept
            : buffer(std::move(str.buffer))
    {

    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits>::basic_lazy_string(const charT *s)
            : buffer(std::make_shared<std::basic_string<charT, traits>>(std::basic_string<charT, traits>(s)))
    {
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits>::basic_lazy_string(size_t n, charT c)
            : buffer(std::make_shared<std::basic_string<charT, traits>>(std::basic_string<charT, traits>(n, c)))
    {

    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits>::~basic_lazy_string()
    {
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits> &basic_lazy_string<charT, traits>::operator=(const basic_lazy_string &str)
    {
        basic_lazy_string copy = str;
        swap(copy);
        return *this;
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits> &basic_lazy_string<charT, traits>::operator=(const charT *s)
    {
        buffer = std::make_shared<std::basic_string<charT, traits>>(std::basic_string<charT, traits>(s));
        return *this;
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits> &basic_lazy_string<charT, traits>::operator=(charT c)
    {
        buffer = std::make_shared<std::basic_string<charT, traits>>(std::basic_string<charT, traits>(c));
        return *this;
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits> &basic_lazy_string<charT, traits>::operator=(basic_lazy_string &&str)
    {
        swap(str);
        str.clear();
        return *this;
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits> &basic_lazy_string<charT, traits>::operator+=(const basic_lazy_string &str)
    {
        copy_not_unique();
        (*buffer) += (*str.buffer);
        return *this;
    }

    template<class charT, class traits>
    void basic_lazy_string<charT, traits>::copy_not_unique()
    {
        if (!buffer.unique())
        {
            buffer = std::make_shared<std::basic_string<charT, traits>>(std::basic_string<charT, traits>(*buffer));
        }
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits> &basic_lazy_string<charT, traits>::operator+=(const charT *s)
    {
        copy_not_unique();
        (*buffer) += s;
        return *this;
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits> &basic_lazy_string<charT, traits>::operator+=(charT c)
    {
        copy_not_unique();
        (*buffer) += c;
        return *this;
    }

    template<class charT, class traits>
    int basic_lazy_string<charT, traits>::compare(const basic_lazy_string &str) const noexcept
    {
        return buffer->compare(*(str.buffer));
    }

    template<class charT, class traits>
    int basic_lazy_string<charT, traits>::compare(const charT *s) const noexcept
    {
        return buffer->compare(s);
    }

    template<class charT, class traits>
    proxy<charT, traits> basic_lazy_string<charT, traits>::operator[](size_type pos)
    {
        return proxy<charT, traits>(pos, *this);
    }

    template<class charT, class traits>
    const charT &basic_lazy_string<charT, traits>::operator[](size_type pos) const
    {
        return (*buffer)[pos];
    }

    template<class charT, class traits>
    void basic_lazy_string<charT, traits>::clear()
    {
        if (!buffer.unique())
        {
            buffer = std::make_shared<std::basic_string<charT, traits>>(std::basic_string<charT, traits>());
        }
        buffer->clear();
    }

    template<class charT, class traits>
    bool basic_lazy_string<charT, traits>::empty() const noexcept
    {
        return buffer->empty();
    }

    template<class charT, class traits>
    size_t basic_lazy_string<charT, traits>::size() const noexcept
    {
        return buffer->size();
    }

    template<class charT, class traits>
    charT const *basic_lazy_string<charT, traits>::c_str() const
    {
        return buffer->c_str();
    }

    template<class charT, class traits>
    void basic_lazy_string<charT, traits>::swap(basic_lazy_string<charT, traits> &other)
    {
        buffer.swap(other.buffer);
    }

    template<class charT, class traits>
    void basic_lazy_string<charT, traits>::replace(size_t ind, charT value)
    {
        copy_not_unique();
        (*buffer)[ind] = value;
    }

    template<class charT, class traits>
    basic_lazy_string<charT, traits>::basic_lazy_string(charT const &c) : basic_lazy_string<charT, traits>(1, c)
    {

    }

    template<class charT, class traits>
    void swap(basic_lazy_string<charT, traits> &x,
              basic_lazy_string<charT, traits> &y)
    {
        x.swap(y);
    }

    template<class charT, class traits>
    bool operator==(const charT *str1, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 == str1;
    }

    template<class charT, class traits>
    bool operator==(const charT &c, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 == c;
    }

    template<class charT, class traits>
    bool operator!=(const charT *str1, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 == str1;
    }

    template<class charT, class traits>
    bool operator!=(const charT &c, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 == c;
    }

    template<class charT, class traits>
    bool operator<(const charT *str1, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 > str1;
    }
    template<class charT, class traits>
    bool operator<(const charT &c, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 > c;
    }
    template<class charT, class traits>
    bool operator>(const charT *str1, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 < str1;
    }
    template<class charT, class traits>
    bool operator>(const charT& c, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 < c;
    }
    template<class charT, class traits>
    bool operator>=(const charT *str1, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 <= str1;
    }
    template<class charT, class traits>
    bool operator>=(const charT &c, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 <= c;
    }
    template<class charT, class traits>
    bool operator<=(const charT *str1, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 >= str1;
    }
    template<class charT, class traits>
    bool operator<=(const charT &c, const basic_lazy_string<charT, traits> &str2)
    {
        return str2 >= c;
    }
    template<class charT, class traits>
    basic_lazy_string <charT, traits> operator+(const charT *str1, const basic_lazy_string<charT, traits> &str2)
    {
        return basic_lazy_string<charT,traits>(str1)+str2;
    }
    template<class charT, class traits>
    basic_lazy_string <charT, traits> operator+(const charT &str1, const basic_lazy_string<charT, traits> &str2)
    {
        return basic_lazy_string<charT,traits>(str1)+str2;
    }
}
#endif //HW2_2_LAZY_STRING_H
