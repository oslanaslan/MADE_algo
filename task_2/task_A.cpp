#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

random_device rd;
mt19937 gen = mt19937(rd());

int find(int data_vec[], int start, int end, int target) {
    if (end - start <= 1)
        return data_vec[start];

    uniform_int_distribution<> uniform_dist(start, end - 1);
    int middle_element = data_vec[uniform_dist(gen)];
    int current_ind = start;
    int left_border = start;
    int right_border = start;
    int result;

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

    if (left_border > target && start <= target) {
        result = find(data_vec, start, left_border, target);
    }
    else if (left_border <= target && right_border > target) {
        result = middle_element;
    }
    else {
        result = find(data_vec, right_border, end, target);
    }

    return result;
}

int main() {
    int n, m;
    cin >> n;
    int input_data[n];

    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
    }

    cin >> m;
    
    int output_data[m];
    int left_vec[m];
    int right_vec[m];
    int target_vec[m];

    for (int i = 0; i < m; i++) {
        cin >> left_vec[i] >> right_vec[i] >> target_vec[i];
    }

    for (int i = 0; i < m; i++) {
        int current_data_vec[right_vec[i] - left_vec[i] + 1];

        copy_n(input_data + left_vec[i] - 1, right_vec[i] - left_vec[i] + 1, current_data_vec);
        output_data[i] = find(current_data_vec, 0, right_vec[i] - left_vec[i] + 1, target_vec[i] - 1);
    }

    for (int i = 0; i < m; i++) {
        cout << output_data[i] << endl;
    }

    return 0;
}