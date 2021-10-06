#include <iostream>

using namespace std;

int64_t get_rope_count_by_length(int64_t input_data[], int64_t n, int64_t length) {
    int64_t count = 0;

    for (int64_t i = 0; i < n; i++) {
        count += input_data[i] / length;
    }

    return count;
}

int main() {
    int64_t n, k;
    cin >> n >> k;
    int64_t input_data[n];
    int64_t left = 1;
    int64_t right = 0;

    for (int64_t i = 0; i < n; i++) {
        cin >> input_data[i];
        right += input_data[i];
    }

    while (right - left > 1) {
        int64_t middle_ind = (right + left) / 2;
        int64_t middle_element = get_rope_count_by_length(input_data, n, middle_ind);

        if (k > middle_element) {
            right = middle_ind;
        }
        else {
            left = middle_ind;
        }
    }

    if (get_rope_count_by_length(input_data, n, left) == k ||
        get_rope_count_by_length(input_data, n, left) != k && left != 1) {
        cout << left << endl;
    }
    else {
        cout << 0 << endl;
    }

    return 0;
}