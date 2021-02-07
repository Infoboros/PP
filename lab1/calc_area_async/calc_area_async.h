//
// Created by ouroboros on 07.02.2021.
//

#ifndef LAB1_CALC_AREA_ASYNC_H
#define LAB1_CALC_AREA_ASYNC_H

#include <vector>
#include "math.h"

#define MAX_RADIUS_FIGURE 50

using namespace std;

typedef pair<float, float> point;

typedef  vector<point> figure;

figure generate_random_figure(int count_node);

float get_square(figure f);

#endif //LAB1_CALC_AREA_ASYNC_H
