//
// Created by Greg on 2018-10-09.
//

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "helper.hpp"

using namespace std;

bool helper::is_perfect_square(const int n) {
    if (n < 0)
        return false;
    int root(round(sqrt(n)));
    return n == root * root;
}

vector<bool> helper::read_file() {
    ifstream file;
    file.open("connectivity.txt");
    string word;
    vector<bool> list(0);

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        bool curr;
        while(iss >> curr) {
            list.push_back(curr);
        }
    }
    return list;
}