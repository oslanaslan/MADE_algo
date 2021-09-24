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
        cards_count[input_string[i] - A]++;
    }

    int start = 0;
    int end = 0;

    while (end < n) {
        if (start < end) {
            if ()
        }
        else {
            end++;
        }
    }
    

    return 0;
}