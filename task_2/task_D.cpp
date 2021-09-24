#include <iostream>

using namespace std;

char END = '\0';
char A = 'a';
char Z = 'z';

int main() {
    int n, m;
    cin >> n >> m;
    char input_string[n + 1] = {END};
    char cards[m + 1] = {END};
    int cards_count[Z - A + 1] = {0};
    int string_count[Z - A + 1] = {0};

    cin >> input_string;
    cin >> cards;

    for (int i = 0; i < m; i++) {
        cards_count[cards[i] - A]++;
    }

    int start = 0;
    int end = 0;
    int count = 0;

    while (start < n) {
        if (end < n) {
            char current_symbol = input_string[end] - A;

            if (string_count[current_symbol] < cards_count[current_symbol]) {
                string_count[current_symbol]++;
                end++;
                count++;
            }
            else {
                char left_symbol = input_string[start] - A;

                string_count[left_symbol] = string_count[left_symbol] > 0 ? string_count[left_symbol] - 1 : 0;
                start++;
                if (start > end) {
                    end = start;
                }
                left_symbol = input_string[start] - A;
                if (string_count[left_symbol] > 0 && string_count[left_symbol] <= cards_count[left_symbol]) {
                    count += end - start;
                }
            }
        }
        else {
            char left_symbol = input_string[start] - A;

            string_count[left_symbol] = string_count[left_symbol] > 0 ? string_count[left_symbol] - 1 : 0;
            start++;
            if (start > end) {
                end = start;
            }
            left_symbol = input_string[start] - A;
            if (string_count[left_symbol] > 0 && string_count[left_symbol] <= cards_count[left_symbol]) {
                count += end - start;
            }
        }
    }
    
    cout << count << endl;

    return 0;
}