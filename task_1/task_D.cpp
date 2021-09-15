#include <iostream>
#include <random>

using namespace std;

void inplace_quick_sort(long *data_vec, int start, int end) {
    if (end - start <= 1)
        return;

    std::random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<> uniform_dist(start, end - 1);
    long middle_element = data_vec[uniform_dist(gen)];
    int current_ind = start;
    int left_border = start;
    int right_border = start;

    while (data_vec[current_ind] < middle_element) {
        current_ind++;
    }

    left_border = current_ind;

    while (data_vec[current_ind] == middle_element) {
        current_ind++;
    }

    right_border = current_ind;

    for (; current_ind < end; current_ind++) {
        if (data_vec[current_ind] < middle_element) {
            swap(data_vec[right_border], data_vec[current_ind]);
            swap(data_vec[left_border], data_vec[right_border]);
            left_border++;
            right_border++;
        }
        else {
            if (data_vec[current_ind] == middle_element) {
                swap(data_vec[right_border], data_vec[current_ind]);
                right_border++;
            }
        }
    }

    inplace_quick_sort(data_vec, start, left_border);
    inplace_quick_sort(data_vec, right_border, end);
}

int main() {
    int N;
    long *data_vec;

    cin >> N;
    data_vec = new long[N];

    for (int i = 0; i < N; i++) {
        cin >> data_vec[i];
    }

    inplace_quick_sort(data_vec, 0, N);

    for (int i = 0; i < N; i++) {
        cout << data_vec[i] << " ";
    }

    return 0;
}