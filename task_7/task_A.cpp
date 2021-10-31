#include <iostream>

using namespace std;

const uint64_t CONST_FROM_TASK_FOR_A_ARRAY = 1 << 16;
const uint64_t CONST_FROM_TASK_FOR_B_ARRAY = 1 << 30;

int64_t get_sum(uint64_t* array, uint64_t left, uint64_t right) {
    if (left == 0) {
        return array[right];
    }

    return array[right] - array[left - 1];
}

int main() {
    uint64_t n, m;
    int64_t x, y, a0, z, t, b0;
    cin >> n >> x >> y >> a0;
    cin >> m >> z >> t >> b0;
    uint64_t a_array[n];
    uint64_t last_counted_b = b0;
    uint64_t last_counted_a = a0;
    uint64_t all_sum = 0;

    a_array[0] = a0;

    for (int i = 1; i < n; i++) {
        last_counted_a = ((x * last_counted_a + y) % CONST_FROM_TASK_FOR_A_ARRAY);
        a_array[i] = last_counted_a + a_array[i - 1];
    }

    for (int i = 0; i < m; i++) {
        uint64_t c1, c2;

        c1 = i == 0 ? b0 : (z * last_counted_b + t) % CONST_FROM_TASK_FOR_B_ARRAY;
        c2 = (z * c1 + t) % CONST_FROM_TASK_FOR_B_ARRAY;
        last_counted_b = c2;
        c1 %= n;
        c2 %= n;

        all_sum += get_sum(a_array, min(c1, c2), max(c1, c2));
    }

    cout << all_sum << endl;

    return 0;
}