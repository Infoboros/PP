#include "calc_area_async/calc_area_async.h"
#include <iostream>
#include <string>
#include <omp.h>

void hand_mod() {
    cout << "Input count node in figure: ";

    int count_node;
    cin >> count_node;

    figure f;
    for (int i = 0; i < count_node; ++i) {
        cout << "Input coordinate " << i << " node: ";

        float x, y;
        cin >> x;
        cin >> y;

        f.push_back({x, y});
    }

    float square = get_square(f);
    cout << "Square test figure: " << square << endl;
}

void async_test() {
    vector<figure> figures;
    vector<float> results;
    vector<int> count_threads = {1, 2, 4, 8, 16};

    int count_figures, count_nodes;
    cout << "Input\n"
            "Count figures: ";
    cin >> count_figures;

    cout << "Count nodes in figure: ";
    cin >> count_nodes;


    figures.reserve(count_figures);
    for (int i = 0; i < count_figures; ++i)
        figures.push_back(generate_random_figure(count_nodes));
    for (int count_thread: count_threads) {
        omp_set_num_threads(count_thread);

        results.clear();
        results.reserve(count_figures);

        double time_start = omp_get_wtime();
        #pragma omp parallel for default(shared)
        for (int i = 0; i < count_figures; ++i)
             get_square(figures[i]);

        double time_end = omp_get_wtime();

        cout << "Count Thread = " << count_thread <<
             "; Time: " << (time_end - time_start) * 1000 << " ms\n";
    }

}

int main(int argc, char* argv[]) {

    int input_flag = 0;

    if ((argc > 1) && (string(argv[1]) == "-debug"))
        input_flag = 1;

    if (input_flag == 1)
        hand_mod();
    else
        async_test();

    return 0;
}