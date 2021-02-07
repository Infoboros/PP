//
// Created by ouroboros on 07.02.2021.
//

#include "calc_area_async.h"

figure generate_random_figure(int count_node) {
    figure f;

    point prev_point = {rand() % MAX_RADIUS_FIGURE, rand() % MAX_RADIUS_FIGURE};
    point next_point;

    //0.017 для перевода в радианы
    float rotate_angle = 360.f / (float)count_node * 0.017f;

    for (int i = 0; i < count_node; ++i) {
        f.push_back(prev_point);

        //Стандартный поворот вокруг точки
        //  X = x * cos(a) - y * sin(a);
        // Y = y * cos(a) + x * sin(a);
        next_point.first = prev_point.first * cos(rotate_angle) - prev_point.second * sin(rotate_angle);
        next_point.second = prev_point.second * cos(rotate_angle) + prev_point.first * sin(rotate_angle);
        prev_point = next_point;
    }

    return f;
}

float get_square(figure f) {
    //Формула площади Гаусса
    //S = 1/2 |E(yi*(xi+1 - xi-1))
    int n = f.size();
    float S = 0.0f;
    for (int i = 0; i < n; ++i) {
        int prev = i - 1;
        if (prev < 0)
            prev = n - 1;

        int next = i + 1;
        if (next == n)
            next = 0;

        S += f[i].second * (f[next].first - f[prev].first);
    }
    return S/2.f;
}