//
// Created by Greg on 2018-10-04.
//

#include <iostream>
#include <math.h>

#include "matrix.hpp"
#include "helper.hpp"

#define TOLERANCE 0.00000001 // tolerance for the difference between doubles

using namespace std;

Matrix::Matrix() {
    unsigned long length = 1;

    matrix.resize(length);
    matrix[0].resize(length);

    matrix[0][0] = 0.0;
}

Matrix::Matrix(const int n) {
    if(n <= 0) {
        throw "Cannot create matrix with < 1 rows/columns.";
    }

    matrix.resize((unsigned)n);
    for(int i = 0; i < n; i++)
        matrix[i].resize((unsigned)n);

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            matrix[r][c] = 0.0;
        }
    }
}

Matrix::Matrix(const int r, const int c) {
    if(r <= 0 || c <= 0) {
        throw "Cannot create matrix with < 1 rows/columns.";
    }

    matrix.resize((unsigned)r);
    for(int i = 0; i < r; i++)
        matrix[i].resize((unsigned)c);

    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            matrix[row][col] = 0.0;
        }
    }
}

Matrix::Matrix(const std::vector<double> v) {
    if(!helper::is_perfect_square(v.size()))
        throw "Must be a perfect square.";

    int length = sqrt(v.size());
    int index = 0;

    matrix.resize((unsigned)length);
    for(int i = 0; i < length; i++)
        matrix[i].resize((unsigned)length);

    for (int row = 0; row < length; row++) {
        for (int col = 0; col < length; col++) {
            matrix[row][col] = v[index];
            index++;
        }
    }
}

void Matrix::set_value(const int r, const int c, const double newVal) {
    if(r < 0 || c < 0 || (unsigned)r >= matrix.size() || (unsigned)c >= matrix[0].size()) {
        throw "Row and column must be within matrix.";
    }
    matrix[r][c] = newVal;
}

double Matrix::get_value(const int r, const int c) const {
    if(r < 0 || c < 0 || (unsigned)r >= matrix.size() || (unsigned)c >= matrix[0].size()) {
        throw "Row and column must be within matrix.";
    }
    return matrix[r][c];
}

void Matrix::clear() {
    for(unsigned int r = 0; r < matrix.size(); r++)
        for(unsigned int c = 0; c < matrix[0].size(); c++)
            matrix[r][c] = 0.0;
}

Matrix::~Matrix() {
    matrix.resize(0);
}

ostream& operator<<(ostream& os, const Matrix& m) {
    for(unsigned int r = 0; r < m.matrix.size(); r++) {
        for (unsigned int c = 0; c < m.matrix[0].size(); c++)
            os << m.matrix[r][c] << " ";
        os << endl;
    }
    return os;
}

bool Matrix::operator==(const Matrix& other) const {
    if(matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size())
        return false;

    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            if(fabs(matrix[r][c] - other.matrix[r][c]) > TOLERANCE)
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

void Matrix::operator++() {
    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            ++matrix[r][c];
}

void Matrix::operator++(int) {
    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            matrix[r][c]++;
}

void Matrix::operator--() {
    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            --matrix[r][c];
}

void Matrix::operator--(int) {
    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            matrix[r][c]--;
}

Matrix& Matrix::operator=(Matrix other) {
    swap(*this, other);
    return *this;
}

void swap(Matrix& first, Matrix& second) {
    using std::swap;
    swap(first.matrix, second.matrix);
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if(matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size())
        throw "Matrices must be the same size";

    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            matrix[r][c] += other.matrix[r][c];
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if(matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size())
        throw "Matrices must be the same size";

    Matrix temp = *this;
    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            temp.matrix[r][c] += other.matrix[r][c];
    return temp;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if(matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size())
        throw "Matrices must be the same size";

    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            matrix[r][c] -= other.matrix[r][c];
    return *this;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if(matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size())
        throw "Matrices must be the same size";

    Matrix temp = *this;
    for(unsigned int r = 0; r < matrix.size(); r++)
        for (unsigned int c = 0; c < matrix[0].size(); c++)
            temp.matrix[r][c] -= other.matrix[r][c];
    return temp;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    if(matrix[0].size() != other.matrix.size()) {
        throw "Number of columns of the first operand must be equal to number of rows of the second operand";
    }

    // Initialize product matrix temp with rows of first operand and columns of second operand
    Matrix temp;
    temp.matrix.resize(matrix.size());
    for(unsigned int i = 0; i < matrix.size(); i++)
        temp.matrix[i].resize(other.matrix[0].size());

    // Places products of matrix elements into temp
    for(unsigned int i = 0; i < matrix.size(); i++) {
        for(unsigned int j = 0; j < other.matrix[0].size(); j++) {
            for(unsigned int k = 0; k < matrix[0].size(); k++) {
                temp.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    *this = temp;
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if(matrix[0].size() != other.matrix.size()) {
        throw "Number of columns of the first operand must be equal to number of rows of the second operand";
    }

    // Initialize product matrix temp with rows of first operand and columns of second operand
    Matrix temp;
    temp.matrix.resize((unsigned)matrix.size());
    for(unsigned int i = 0; i < matrix.size(); i++)
        temp.matrix[i].resize((unsigned)other.matrix[0].size());

    // Places products of matrix elements into temp
    for(unsigned int i = 0; i < matrix.size(); i++) {
        for(unsigned int j = 0; j < other.matrix[0].size(); j++) {
            for(unsigned int k = 0; k < matrix[0].size(); k++) {
                temp.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return temp;
}