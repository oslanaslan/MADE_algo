#include <iostream>

using namespace std;

int printing_time_function(int n, int x, int y, int count) {
    // f(k) = max(x * k, y * (n - 1 - k)) + min(x, y) -> min_{k}

    int on_first = x * count;
    int on_second = y * (n - 1 - count);
    int first_page_time = x < y ? x : y;
    int last_pages_time = on_first > on_second ? on_first : on_second;

    return first_page_time + last_pages_time;
}

int main() {
    int n;
    int x, y;

    cin >> n >> x >> y;

    if (n * x < y) {
        cout << n * x << endl;
    }
    else if (n * y < x) {
        cout << n * y << endl;
    }
    else {
        int left = 0;
        int right = n;

        while (right - left > 1) {
            int left_mid = left + (right - left) / 3;
            int right_mid = left + 2 * (right - left) / 3;
            int left_mid_element = printing_time_function(n, x, y, left_mid);
            int right_mid_element = printing_time_function(n, x, y, right_mid);

            if (left_mid_element == right_mid_element) {
                left = left_mid;
                right = right_mid;
            }
            else if (left_mid_element < right_mid_element) {
                right = right_mid;
            }
            else {
                left = left_mid + 1;
            }
        }

        cout << printing_time_function(n, x, y, left) << endl;
    }

    return 0;
}