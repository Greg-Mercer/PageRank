//
// Created by Greg on 2018-10-04.
//

#include <vector>
#include <ostream>

#ifndef PAGERANK_MATRIX_HPP
#define PAGERANK_MATRIX_HPP

using namespace std;

/*
 * A data structure used to store doubles. Implements various operators for data manipulation.
 */
class Matrix {

private:
    std::vector<std::vector<double>> matrix; // a vector of double vectors; functions as matrix

public:

    /*
     * Constructs a matrix with a single row and a single column containing 0.
     */
    Matrix();
    /*
     * Constructs a matrix with n rows and columns, filling them with 0.
     * @param n the number of rows and columns for this Matrix
     */
    Matrix(const int n);
    /*
     * Constructs a matrix with r rows and c columns, filling them with 0.
     * @param r number of rows
     * @param c number of columns
     */
    Matrix(const int r, const int c);
    /*
     * Constructs a matrix using a list of doubles.
     * @param v the list of doubles
     */
    Matrix(const vector<double> v);
    /*
     * Sets a given value within the matrix.
     * @param r the row of the value to change
     * @param c the column of the value to change
     * @param newVal the new value to change to
     */
    void set_value(const int r, const int c, const double newVal);
    /*
     * Gets a given value from within the matrix.
     * @param r the row of the value to get
     * @param c the column of the value to get
     * @return the value
     */
    double get_value(const int r, const int c) const;
    /*
     * Sets all values within the matrix to 0.
     */
    void clear();
    /*
     * Destroys the matrix.
     */
    virtual ~Matrix();
    /*
     * Puts the matrix into an output stream in an easily readable format.
     * @param os the stream to put the matrix into
     * @param m the matrix to put into the stream
     * @return the output stream with the matrix
     */
    friend ostream& operator<<(ostream& os, const Matrix& m);
    /*
     * Checks if a given matrix is equal to another.
     * @param other the matrix this one is being compared to
     * @return true if the matrices are equal, otherwise false
     */
    bool operator==(const Matrix& other) const;
    /*
     * Checks if a given matrix is unequal to another.
     * @param other the matrix this one is being compared to
     * @return true if the matrices are unequal, otherwise false
     */
    bool operator!=(const Matrix& other) const;
    /*
     * Increments all values in the matrix by 1 (prefix).
     */
    void operator++();
    /*
     * Increments all values in the matrix by 1 (postfix).
     */
    void operator++(int);
    /*
     * Decrements all values in the matrix by 1 (prefix).
     */
    void operator--();
    /*
     * Decrements all values in the matrix by 1 (postfix).
     */
    void operator--(int);
    /*
     * Uses copy-and-swap for assignment.
     * @param other the matrix being copied and swapped
     * @return this matrix
     */
    Matrix& operator=(Matrix other);
    /*
     * Standard implementation of copy-and-swap.
     * @param first a matrix
     * @param second a matrix
     */
    friend void swap(Matrix& first, Matrix& second);
    /*
     * Adds elements of one matrix to another.
     * @param other the matrix to add to this one
     * @return this matrix
     */
    Matrix& operator+=(const Matrix& other);
    /*
     * Adds elements of one matrix to another.
     * @param other the matrix to add to this one
     * @return the resulting matrix
     */
    Matrix operator+(const Matrix& other) const;
    /*
     * Subtracts elements of one matrix from another.
     * @param other the matrix to subtract from this one
     * @return this matrix
     */
    Matrix& operator-=(const Matrix& other);
    /*
     * Subtracts elements of one matrix from another.
     * @param other the matrix to subtract from this one
     * @return the resulting matrix
     */
    Matrix operator-(const Matrix& other) const;
    /*
     * Multiplies 2 matrices together.
     * @param other the matrix to multiply with this one
     * @return this matrix
     */
    Matrix& operator*=(const Matrix& other);
    /*
     * Multiplies 2 matrices together.
     * @param other the matrix to multiply with this one
     * @return the resulting matrix
     */
    Matrix operator*(const Matrix& other) const;

};

#endif //PAGERANK_MATRIX_HPP