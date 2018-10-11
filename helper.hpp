//
// Created by Greg on 2018-10-10.
//

#ifndef PAGERANK_HELPER_HPP
#define PAGERANK_HELPER_HPP

#include <vector>

using namespace std;

class helper {

public:
    /*
     * Determines if a given number is a perfect square.
     * @param n the number to test
     * @return true if n is a perfect square, else false
     */
    static bool is_perfect_square(const int n);
    /*
     * Reads a file and converts the contents into a vector of bools.
     * @return resulting bool vector
     */
    static vector<bool> read_file();
};

#endif //PAGERANK_HELPER_HPP
