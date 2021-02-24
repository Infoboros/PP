//
// Created by ouroboros on 23.02.2021.
//

#include "Matr.h"

Matr::Matr(size_t _n, size_t _m) : n(_n), m(_m) {
    data = new int *[n];
    for (size_t i = 0; i < n; ++i)
        data[i] = new int[m];
}

Matr::~Matr() {

        for (size_t i = 0; i < n; ++i)
            delete data[i];
        delete data;

}

void Matr::inputMatr() {
    cout << "Input Matrix: " << endl;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            cin >> data[i][j];
}

void Matr::printMatr() {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

Matr* operator*(Matr &m1, Matr &m2) {
    size_t n = m1.n,
            m = m1.m,
            k = m2.m;

    Matr *result = new Matr(n, k);

    #pragma omp parallel for default(shared)
    for (size_t i = 0; i < n; ++i) {
        #pragma omp parallel for default(shared)
        for (size_t j = 0; j < k; ++j) {
            int c_i_j = 0;
            #pragma omp parallel for reduction(+:c_i_j)
            for (size_t index_for_mult = 0; index_for_mult < m; ++index_for_mult) {
                c_i_j += m1[i][index_for_mult] * m2[index_for_mult][j];
            }
            (*result)[i][j] = c_i_j;
        }
    }
    return result;
}

int *Matr::operator[](size_t index) {
    return data[index];
}

void Matr::random_generate() {
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            data[i][j] = rand() % MAX_RANDOM_EL;
}

Matr multMatrixs(vecMatr inVector) {
    while (inVector.size() != 1){
        size_t len = inVector.size();
        size_t tmp_len = len/2 + len%2;
        size_t len_to_for = len - len%2;
        vecMatr tmpVec;
        tmpVec.resize(tmp_len);

        #pragma omp parallel for default(shared)
        for (size_t i = 0; i < len_to_for; i+=2) {
            Matr *tmpMatr = (*inVector[i]) * (*inVector[i+1]);
            tmpVec[i/2] = tmpMatr;
        }

        if(len%2)
            tmpVec[tmp_len-1] = inVector[len-1];

        inVector = tmpVec;
    }
    return *inVector.front();
}