//
// Created by Greg on 2018-10-08.
//

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "connectivity_matrix.hpp"
#include "helper.cpp"

#define RANDOM_WALK 0.85

using namespace std;

Connectivity_Matrix::Connectivity_Matrix(vector<bool> v) {
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

const Matrix Connectivity_Matrix::probability() {
    Matrix temp(matrix.size(), matrix[0].size());

    for(unsigned int c = 0; c < matrix.size(); c++) {
        int sum = 0;
        bool all_zeros = true;
        for(unsigned int r = 0; r < matrix[0].size(); r++) {
            if(matrix[r][c] != 0) {
                sum += (int)matrix[r][c];
                all_zeros = false;
            }
        }
        for(unsigned int r = 0; r < matrix[0].size(); r++) {
            double val = matrix[r][c];
            all_zeros ? (temp.set_value(r, c, ((double)1 / (double)matrix.size())))
            : (temp.set_value(r, c, val / sum));
        }
    }
    return temp;
}

const Matrix Connectivity_Matrix::transition(const Matrix pr) {
    Matrix m = pr;

    for (unsigned int r = 0; r < matrix.size(); r++) {
        for (unsigned int c = 0; c < matrix[0].size(); c++) {
            m.set_value(r, c, m.get_value(r, c) * RANDOM_WALK);
        }
    }

    Matrix q(matrix.size(), matrix[0].size());
    for (unsigned int r = 0; r < matrix.size(); r++) {
        for (unsigned int c = 0; c < matrix[0].size(); c++) {
            q.set_value(r, c, ((double)1 / (double)matrix.size()) * ((double)1 - RANDOM_WALK));
        }
    }

    m += q;
    return m;
}

const Matrix Connectivity_Matrix::markov(const Matrix tr) {
    Matrix rank(matrix.size(), 1);

    for (unsigned int r = 0; r < matrix.size(); r++) {
        rank.set_value(r, 0, 1.0);
    }

    Matrix m = tr;
    Matrix result;

    while(rank != m * rank) {
        rank = m * rank;
    }

    double sum = 0;
    for(unsigned int r = 0; r < matrix.size(); r++) {
        sum += rank.get_value(r, 0);
    }
    for(unsigned int r = 0; r < matrix.size(); r++) {
        rank.set_value(r, 0, rank.get_value(r, 0) / sum);
    }

    return rank;
}

void Connectivity_Matrix::page_rank() {
    Matrix probability = this->probability();
    Matrix transition = this->transition(probability);
    Matrix markov = this->markov(transition);

    char page = 'A';
    for(unsigned int r = 0; r < matrix.size(); r++) {
        cout << "Page " << page << ": " << fixed << setprecision(2)
             << markov.get_value(r, 0) * 100 << "%" << endl;
        page++;
    }
}

Connectivity_Matrix::~Connectivity_Matrix() {
    matrix.resize(0);
}

ostream& operator<<(ostream& os, const Connectivity_Matrix& m) {
    for(unsigned int r = 0; r < m.matrix.size(); r++) {
        for (unsigned int c = 0; c < m.matrix[0].size(); c++)
            os << m.matrix[r][c] << " ";
        os << endl;
    }
    return os;
}

