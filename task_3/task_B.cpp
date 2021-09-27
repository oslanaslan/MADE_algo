#include <iostream>
#include <algorithm>

using namespace std;

int lower_bound(int input_data[], int n, int target) {
    int left = -1;
    int right = n;

    while (right - left > 1) {
        int middle_ind = left + (right - left) / 2;
        int middle_element = input_data[middle_ind];

        if (target <= middle_element) {
            right = middle_ind;
        }
        else {
            left = middle_ind;
        }
    }

    return right;
}

int main() {
    int n, k;
    cin >> n;
    int input_data[n];

    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
    }

    cin >> k;

    pair<int, int> queries[k];
    int results[k];

    for (int i = 0; i < k; i++) {

        cin >> queries[i].first >> queries[i].second;
    }

    sort(input_data, input_data + n);

    for (int i = 0; i < k; i++) {
        pair<int, int> query = queries[i];
        int left_bound = lower_bound(input_data, n, query.first);
        int right_bound = lower_bound(input_data, n, query.second +1);

        results[i] = right_bound - left_bound;
    }

    for (int i = 0; i < k; i++) {
        cout << results[i] << " ";
    }

    return 0;
}