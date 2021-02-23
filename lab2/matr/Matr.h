//
// Created by ouroboros on 23.02.2021.
//

#ifndef LAB2_MATR_H
#define LAB2_MATR_H

#define MAX_RANDOM_EL 100

#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

class Matr {
private:
    size_t n, m;
    int** data;

public:
    Matr(): n(0), m(0){};
    Matr(size_t _n, size_t _m);
    ~Matr();

    void inputMatr();
    void printMatr();

    friend Matr* operator*(Matr &m1, Matr &m2);
    int * operator[](size_t index);

    void random_generate();

};

typedef vector<Matr *> vecMatr;
Matr multMatrixs(vecMatr);

#endif //LAB2_MATR_H
