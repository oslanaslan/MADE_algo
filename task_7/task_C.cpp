#include <iostream>
#include <cstring>

using namespace std;

const int COMMAND_LEN = 3;

int64_t* create_pref_sum_array(int64_t* input_data, int n) {
    int64_t* sum_array = new int64_t[n];

    
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

    while (cin >> cmd >> first_operand >> second_operand) {
        if (strcmp(cmd, "sum")) {
            // SET

        }
        else {
            // SUM
        }
    }

    return 0;
}