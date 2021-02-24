#include <iostream>
#include <vector>
#include <omp.h>

#include "matr/Matr.h"

using namespace std;

void swap_size_t(size_t &a, size_t &b) {
    size_t tmp = a;
    a = b;
    b = tmp;
}

void hand_mod() {
    cout << "Hello, it's debug mode." << endl;

    cout << "Input n and m to first nxm matrix: " << endl;
    size_t n, m, k;

    cout << "n = ";
    cin >> n;

    cout << "m = ";
    cin >> m;

    cout << "Input k to second mxk matrix: " << endl;
    cout << "k = ";
    cin >> k;

    Matr matrFirst = Matr(n, m);
    Matr matrSecond = Matr(m, k);

    matrFirst.inputMatr();
    matrSecond.inputMatr();

    Matr matrResult = *(matrFirst * matrSecond);

    matrFirst.printMatr();
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
    matrSecond.printMatr();

    cout << "=========================" << endl;

    matrResult.printMatr();
}

void async_test() {
    cout << "Hello, it's test vector mode." << endl;

    size_t count_matrix;
    size_t n, m;
    vecMatr vector_matrix;

    cout << "Input count matrix (min 2): ";
    cin >> count_matrix;

    cout << "input n and m which will be swapped for each subsequent matrix." << endl;

    cout << "n = ";
    cin >> n;

    cout << "m = ";
    cin >> m;

    vector_matrix.reserve(count_matrix);
    for (size_t i = 0; i < count_matrix; ++i) {
        vector_matrix.push_back(new Matr(n, m));
        swap_size_t(n, m);
        vector_matrix[i]->inputMatr();
    }

    for (int i = 0; i < count_matrix; ++i) {
        vector_matrix[i]->printMatr();
        cout << "===" << endl;
    }
    multMatrixs(vector_matrix).printMatr();

    for (size_t i = 0; i < count_matrix; ++i)
        delete vector_matrix[i];

}

void async_mode() {
    cout << "Hello, it's test time mode." << endl;

    size_t count_matrix;
    size_t n, m;
    vecMatr vector_matrix;
    vector<int> count_threads = {1, 2, 4, 8, 16};

    cout << "Input count matrix (min 2): ";
    cin >> count_matrix;

    cout << "input n and m which will be swapped for each subsequent matrix." << endl;

    cout << "n = ";
    cin >> n;

    cout << "m = ";
    cin >> m;

    cout << "Generating matrix...." << endl;
    vector_matrix.reserve(count_matrix);
    for (size_t i = 0; i < count_matrix; ++i) {
        vector_matrix.push_back(new Matr(n, m));
        swap_size_t(n, m);
        vector_matrix[i]->random_generate();
    }

    for (int count_thread: count_threads) {
        omp_set_num_threads(count_thread);

        double time_start = omp_get_wtime();
        multMatrixs(vector_matrix);
        double time_end = omp_get_wtime();

        cout << "Count Thread = " << count_thread <<
             "; Time: " << (time_end - time_start) * 1000 << " ms\n";
    }

    for (size_t i = 0; i < count_matrix; ++i)
        delete vector_matrix[i];
}

int main(int argc, char *argv[]) {

    if ((argc > 1) && (string(argv[1]) == "-debug"))
        hand_mod();
    else if ((argc > 1) && (string(argv[1]) == "-debug_vec"))
        async_test();
    else
        async_mode();

    return 0;
}