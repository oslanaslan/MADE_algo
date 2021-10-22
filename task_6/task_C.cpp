#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int input_data[n];
    int values[n];
    int global_max_len = 1;
    int global_max_len_ind = 0;
    int parents[n];
    int result[n];
    int result_len = 0;

    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
    }

    values[0] = 1;
    parents[0] = -1;

    for (int i = 1; i < n; i++) {
        int max_len_in_prefix = 0;
        int max_len_in_prefix_ind = -1;

        for (int j = 0; j < i; j++) {
            if (values[j] > max_len_in_prefix && input_data[j] < input_data[i]) {
                max_len_in_prefix = values[j];
                max_len_in_prefix_ind = j;
            }
        }

        values[i] = max_len_in_prefix + 1;
        parents[i] = max_len_in_prefix_ind;
        
        if (values[i] > global_max_len) {
            global_max_len = values[i];
            global_max_len_ind = i;
        }
    }

    int i = global_max_len_ind;

    while (i >= 0) {
        result[result_len++] = input_data[i];
        i = parents[i];
    }

    cout << values[global_max_len_ind] << endl;

    for (int i = result_len - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }

    return 0;
}