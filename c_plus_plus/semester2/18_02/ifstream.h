#include <iostream>

namespace ifs {
    class input_file_exception : public std::exception {

    public:
        virtual const char *what() const noexcept {
            return "File not open";
        }
    };

    class ifstream {
    public:
        ifstream(const std::string file_name);

        ifstream(ifstream &&);

        ifstream &operator=(ifstream);

        ifstream(const ifstream &);

        void swap(ifstream &);

        ifstream &operator>>(int &);

        ifstream &operator>>(double &);

        ifstream &operator>>(std::string &);

        bool good();

        bool fail();

        bool eof();

        ~ ifstream();

    private:
        FILE *file;
        std::string file_name;
    };
}