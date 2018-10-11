//
// Created by Greg on 2018-10-08.
//

#ifndef PAGERANK_CONNECTIVITY_MATRIX_HPP
#define PAGERANK_CONNECTIVITY_MATRIX_HPP

#include <ostream>
#include "matrix.hpp"

using namespace std;

class Connectivity_Matrix : public Matrix {

private:
    std::vector<std::vector<bool>> matrix; // a vector of bool vectors; functions as matrix

public:
    /*
     * Constructs a matrix using a list of bools.
     * @param v the list of bools
     */
    Connectivity_Matrix(vector<bool> v);
    /*
     * Destroys the matrix.
     */
    ~Connectivity_Matrix();
    /*
     * Determines the "importance" of values in this matrix by summing up values in the columns and dividing
     * them by said sum.
     * @return a matrix of probability values
     */
    const Matrix probability();
    /*
     * Creates a transition matrix for the markov process.
     * @param pr a probability matrix
     * @return transition matrix
     */
    const Matrix transition(const Matrix pr);
    /*
     * Creates a rank matrix and uses a transition matrix for the markov process.
     * @param tr a transition matrix
     * @return ranked matrix after markov process
     */
    const Matrix markov(const Matrix tr);
    /*
     * Calculates page rank and prints it to cout.
     */
    void page_rank();
    /*
     * Puts the connectivity matrix into an output stream in an easily readable format.
     * @param os the stream to put the matrix into
     * @param m the matrix to put into the stream
     * @return the output stream with the matrix
     */
    friend std::ostream& operator<<(std::ostream& os, const Connectivity_Matrix& m);
};


#endif //PAGERANK_CONNECTIVITY_MATRIX_HPP
