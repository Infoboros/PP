#include "mpi.h"
#include <cstdio>
#include <cmath>

#define N 14.0

double f(double x);

int main(int argc, char *argv[]) {

    int p, rang_prog, count_procs;
    double my_f;

    double start_time = 0.0;

    // Инициализируем MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &count_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang_prog);

    if (rang_prog == 0) {
        fprintf(stdout, "Input P: ");
        fflush(stdout);
        scanf("%d", &p);
        start_time = MPI_Wtime();
    }

    // Рассылаем количество интервалов всем процессам
    //(в том числе и себе самому)
    MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double h = N / (double) p;
    double sum = 0.0;
    // Обсчитывает точки, "закрепленные" за процессом
    for (int i = rang_prog + 1; i <= p; i += count_procs) {
        double x = h * ((double) i - 0.5) + 1.0;
        sum += f(x);
    }
    double current_my_f = h * sum;

    // Собираем результаты со всех процессов и складываем все
    MPI_Reduce(&current_my_f, &my_f, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Если это головной процесс, выводим полученные результаты
    if (rang_prog == 0) {
        printf("F = %.16f\n", my_f);
        double end_time = MPI_Wtime();
        printf("Time = %f\n", end_time - start_time);
        fflush(stdout);
    }

    // Освобождаем MPI
    MPI_Finalize();
    return 0;
}

double f(double x) {
    double x2 = x * x;
    double x3 = x2 * x;

    return fabs(x2 - x3) - (7.0 * x) / (x3 - 15.0 * x);
}