#include <iostream>
#include <random>

using namespace std;

void inplace_quick_sort(int *data_vec, int start, int end) {
    if (end - start <= 1)
        return;

    std::random_device rd;
    std::mt19937 gen(rd());
    uniform_int_distribution<> uniform_dist(start, end - 1);
    int middle_element = data_vec[uniform_dist(gen)];
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

    while (current_ind < end) {
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
        current_ind++;
    }

    inplace_quick_sort(data_vec, start, left_border);
    inplace_quick_sort(data_vec, right_border, end);
}

int main() {
    int n;
    int *data_vec;

    cin >> n;
    data_vec = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> data_vec[i];
    }

    inplace_quick_sort(data_vec, 0, n);

    for (int i = 0; i < n; i++) {
        cout << data_vec[i] << " ";
    }

    return 0;
}