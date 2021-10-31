#include <iostream>

using namespace std;

const int64_t CONST_FROM_TASK_FOR_A_1 = 23;
const int64_t CONST_FROM_TASK_FOR_A_2 = 21563;
const int64_t CONST_FROM_TASK_FOR_A_3 = 16714589;
const int64_t CONST_FROM_TASK_FOR_A_4 = 23;

const int64_t CONST_FROM_TASK_FOR_U_1 = 17;
const int64_t CONST_FROM_TASK_FOR_U_2 = 751;
const int64_t CONST_FROM_TASK_FOR_U_3 = 2;

const int64_t CONST_FROM_TASK_FOR_V_1 = 13;
const int64_t CONST_FROM_TASK_FOR_V_2 = 593;
const int64_t CONST_FROM_TASK_FOR_V_3 = 5;

int64_t get_next_u(int64_t u_prev, int64_t prev_request_res, int64_t i, int64_t n) {
    int64_t res = CONST_FROM_TASK_FOR_U_1 * u_prev;

    res += CONST_FROM_TASK_FOR_U_2;
    res += prev_request_res;
    res += CONST_FROM_TASK_FOR_U_3 * (i + 1);
    res %= n;
    res += 1;
    return res;
}

int64_t get_next_v(int64_t v_prev, int64_t prev_request_res, int64_t i, int64_t n) {
    int64_t res = CONST_FROM_TASK_FOR_V_1 * v_prev;

    res += CONST_FROM_TASK_FOR_V_2;
    res += prev_request_res;
    res += CONST_FROM_TASK_FOR_V_3 * (i + 1);
    res %= n;
    res += 1;
    return res;
}
int64_t get_next_a(int64_t prev_a) {
    return (CONST_FROM_TASK_FOR_A_1 * prev_a + 
            CONST_FROM_TASK_FOR_A_2) % CONST_FROM_TASK_FOR_A_3;
}

int main() {
    int64_t n, m, a0, u1, v1;

    cin >> n >> m >> a0;
    cin >> u1 >> v1;

    int64_t max_deg_array[n + 1];
    int64_t max_deg_values[n + 1];
    int64_t res_array[m];

    max_deg_array[0] = 0;
    max_deg_values[0] = 0;
    max_deg_array[1] = 0;
    max_deg_values[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (max_deg_values[i - 1] * 2 > i) {
            max_deg_array[i] = max_deg_array[i - 1];
            max_deg_values[i] = max_deg_values[i - 1];
        }
        else {
            max_deg_array[i] = max_deg_array[i - 1] + 1;
            max_deg_values[i] = max_deg_values[i - 1] * 2;
        }
    }

    int64_t deg_values_of_2[max_deg_array[n] + 1];
    int deg_count = 0;

    for (int i = 1; i <= max_deg_values[n]; i *= 2) {
        deg_values_of_2[deg_count++] = i;
    }

    int64_t subarray_len = max_deg_array[n] + 1;
    int64_t min_matrix[n][subarray_len];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < subarray_len; j++) {
            min_matrix[i][j] = j != 0 ? -1 : (
                i == 0 ? a0 : get_next_a(min_matrix[i - 1][j])
            );
        }
    }

    for (int64_t j = 1; j < subarray_len; j++) {
        for (int64_t i = 0; i < n; i++) {
            int64_t left_border = i;
            int64_t right_border = min(i + deg_values_of_2[j], n);
            int64_t min_ind = min(max_deg_array[right_border - left_border], j - 1);

            min_matrix[i][j] = min(
                min_matrix[i][min_ind],
                min_matrix[right_border - deg_values_of_2[min_ind]][min_ind]
            );
        }
    }

    int64_t current_u = u1;
    int64_t current_v = v1;
    int64_t old_u = u1;
    int64_t old_v = v1;
    int64_t prev_res = 0;

    for (int i = 0; i < m; i++) {
        int64_t current_left_border = min(
            min(current_u, current_v) - 1,
            n
        );
        int64_t current_right_border = min(
            max(current_u, current_v),
            n
        );

        int64_t max_deg_value = max_deg_values[current_right_border - current_left_border];
        int64_t max_deg = max_deg_array[current_right_border - current_left_border];
        int64_t ind = current_right_border - deg_values_of_2[max_deg];

        prev_res = min(
            min_matrix[current_left_border][max_deg],
            min_matrix[current_right_border - deg_values_of_2[max_deg]][max_deg]
        );
        old_u = current_u;
        old_v = current_v;
        current_u = get_next_u(old_u, prev_res, i, n);
        current_v = get_next_v(old_v, prev_res, i, n);
    }

    cout << old_u << " " << old_v << " " << prev_res << endl;

    return 0;
}