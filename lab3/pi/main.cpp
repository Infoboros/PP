#include "mpi.h"
#include <cstdio>

double f_pi(double a);

int main(int argc, char *argv[]) {

    int n, rang_prog, count_procs;
    double pi;

    double start_time = 0.0;

    // Инициализируем MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &count_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang_prog);

    if (rang_prog == 0) {
        fprintf(stdout, "Input N: ");
        fflush(stdout);
        scanf("%d", &n);
        start_time = MPI_Wtime();
    }

    // Рассылаем количество интервалов всем процессам
    //(в том числе и себе самому)
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double h = 1.0 / (double) n;
    double sum = 0.0;
    // Обсчитывает точки, "закрепленные" за процессом
    for (int i = rang_prog + 1; i <= n; i += count_procs) {
        double x = h * ((double) i - 0.5);
        sum += f_pi(x);
    }
    double current_pi = h * sum;

    // Собираем результаты со всех процессов и складываем все
    MPI_Reduce(&current_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Если это головной процесс, выводим полученные результаты
    if (rang_prog == 0) {
        printf("PI = %.16f\n", pi);
        double end_time = MPI_Wtime();
        printf("Time = %f\n", end_time - start_time);
        fflush(stdout);
    }

    // Освобождаем MPI
    MPI_Finalize();
    return 0;
}

double f_pi(double a) {
    return (4.0 / (1.0 + a * a));
}