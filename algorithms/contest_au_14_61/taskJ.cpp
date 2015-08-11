//
// Created by av on 6/13/15.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <unordered_map>

using namespace std;

const int INF = 1000000000;

int main() {

    ifstream in("incrementator.in");
    ofstream out("incrementator.out");

    unordered_map<string, int> storage;
    string name;
    int value;
    while(in >> name >> value) {
        auto ptr = storage.find(name);
        if(ptr == storage.end()) {
            storage[name] = 0;
        }
        storage[name] += value;
        out << storage[name] << "\n";
    }

    return 0;
}