#include <iostream>
#include "vector.h"
using namespace std;

int main()
{
    vector<int> v(10);
    for (int i=0;i<20;i++){
        v.push_bask(i%7);
    }
    std::make_heap(v.begin(),v.end());
    return 0;
}