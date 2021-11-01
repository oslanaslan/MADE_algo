#include <iostream>
#include <cstring>

using namespace std;

const int COMMAND_LEN = 3;

int f_func(int value) {
    return value & (value + 1);
}

void add_func(int64_t* sum_array, int index, int64_t value, int n) {
    while (index < n) {
        sum_array[index] += value;
        index = index | (index + 1);
    }
}

int64_t get(int64_t* sum_array, int index) {
    int64_t res = 0;

    while (index >= 0) {
        res += sum_array[index];
        index = f_func(index) - 1;
    }

    return res;
}

int64_t rsq(int64_t* sum_array, int left, int right) {
    if (left == 0) {
        return get(sum_array, right);
    }

    return get(sum_array, right) - get(sum_array, left - 1);
}

int64_t* create_pref_sum_array(int64_t* input_data, int n) {
    int64_t* sum_array = new int64_t[n];

    for (int i = 0; i < n; i++) {
        sum_array[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        add_func(sum_array, i, input_data[i], n);
    }

    return sum_array;
}

int main() {
    int n;
    cin >> n;
    int64_t input_data[n];
    char cmd[COMMAND_LEN + 1];
    int64_t first_operand, second_operand;

    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
    }

    int64_t* sum_array = create_pref_sum_array(input_data, n);

    while (cin >> cmd >> first_operand >> second_operand) {
        if (strcmp(cmd, "sum")) {
            // SET
            int64_t delta = second_operand - input_data[first_operand - 1];

            input_data[first_operand - 1] = second_operand;
            add_func(sum_array, first_operand - 1, delta, n);
        }
        else {
            // SUM
            int64_t sum_on_subarray = rsq(sum_array, first_operand - 1, second_operand - 1);

            cout << sum_on_subarray << endl;
        }
    }

    return 0;
}
