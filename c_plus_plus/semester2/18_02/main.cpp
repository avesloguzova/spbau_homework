#include "ifstream.h"
#include <ostream>

using namespace std;

int main() {
    ifs::ifstream ifile("test.txt");
    ifs::ifstream ifile2 = std::move(ifile);
    int n = 0;
    ifile2 >> n;
    std::cout << n << endl;
}