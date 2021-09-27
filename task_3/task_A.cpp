#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int64_t input_data[n];
    int64_t target_data[k];
    int64_t results[k];

    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
    }

    for (int i = 0; i < k; i++) {
        cin >> target_data[i];
    }

    for (int i = 0; i < k; i++) {
        int64_t target = target_data[i];
        int left = 0;
        int right = n - 1;

        while (right - left > 1) {
            int middle_ind = left + (right - left) / 2;
            int64_t middle_element_1 = input_data[middle_ind];
            int64_t middle_element_2 = input_data[middle_ind + 1];

            if (middle_element_1 <=  target && target <= middle_element_2) {
                left = middle_ind;
                right = middle_ind + 1;
            }
            else if (target < middle_element_1) {
                right = middle_ind;
            }
            else {
                left = middle_ind + 1;
            }
        }

        if (abs(input_data[left] - target) <= abs(input_data[left + 1] - target)) {
            results[i] = input_data[left];
        }
        else {
            results[i] = input_data[right];
        }
    }

    for (int i = 0; i < k; i++) {
        cout << results[i] << endl;
    }

    return 0;
}