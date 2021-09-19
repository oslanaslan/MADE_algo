#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

int find(int *data_vec, int start, int end, int target, vector<pair<int, int>> &swapped_pairs) {
    if (end - start <= 1)
        return data_vec[start];

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
            swapped_pairs.push_back(make_pair(right_border, current_ind));
            swapped_pairs.push_back(make_pair(left_border, right_border));
            left_border++;
            right_border++;
        }
        else {
            if (data_vec[current_ind] == middle_element) {
                swap(data_vec[right_border], data_vec[current_ind]);
                swapped_pairs.push_back(make_pair(right_border, current_ind));
                right_border++;
            }
        }
        current_ind++;
    }

    if (left_border > target && start <= target) {
        return find(data_vec, start, left_border, target, swapped_pairs);
    }
    else if (left_border <= target && right_border > target) {
        return middle_element;
    }
    else {
        return find(data_vec, right_border, end, target, swapped_pairs);
    }
}

int main() {
    int n, m;
    cin >> n;
    int input_data[n];
    vector<pair<int, int>> swapped_pairs;

    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
    }

    cin >> m;

    for (int i = 0; i < m; i++) {
        int left, right, target, result;

        cin >> left >> right >> target;
        // int current_data_vec[right - left + 1];
        // copy_n(input_data + left - 1, right - left + 1, current_data_vec);
        // result = find(current_data_vec, 0, right - left + 1, target - 1, swapped_pairs);
        result = find(input_data, 0, right - left + 1, target - 1, swapped_pairs);
        cout << result << endl;

        while (!swapped_pairs.empty()) {
            pair<int, int> last_pair = swapped_pairs.back();
            swapped_pairs.pop_back();
            swap(input_data[last_pair.first], input_data[last_pair.second]);
        }
        
        for (int i = 0; i < n; i++)
            cout << input_data[i] << " ";
        cout << endl;
    }

    return 0;
}