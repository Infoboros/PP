#include "calc_area_async/calc_area_async.h"
#include <iostream>

void test_get_square() {
    figure f = {{-2.0, 2.0},
                {2.0,  2.0},
                {2.0,  -2.0},
                {-2.0, -2.0},};
    float square = get_square(f);
    cout << "Площадь тестового объекта: " << square << endl;
}

float async_test(int count_figures, int count_nodes){
    vector<figure> figures;
    vector<float> results;

    figures.reserve(count_figures);
    for (int i = 0; i < count_figures; ++i)
        figures.push_back(generate_random_figure(count_nodes));

    results.reserve(count_figures);
    for (int i = 0; i < count_figures; ++i)
        results.push_back(get_square(figures[i]));
    return 0.f;
}

int main() {
//    test_get_square();
    int count_figures, count_nodes;
    cout << "Введите\n"
            "Колличество фигур: ";
    cin >> count_figures;

    cout << "Колличество вершин у фигур: ";
    cin >> count_nodes;

    float squares = async_test(count_figures, count_nodes);

    return 0;
}