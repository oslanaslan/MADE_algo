#include <iostream>
#include <algorithm>

using namespace std;

char A = 'a';
char Z = 'z';
char END = '\0';

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    char input_data[n][m + 1] = {END};
    int permutations[n];

    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
        permutations[i] = i;
    }

    for (int i = 0; i < k; i++) {
        int current_latter = m - i - 1;
        int counts[Z - A + 1] = {0};

        for (int word_index = 0; word_index < n; word_index++) {
            counts[input_data[permutations[word_index]][current_latter] - A]++;
        }

        int new_permutations[n];
        int positions[Z - A + 1] = {0};

        for (int j = 1; j < n; j++) {
            positions[j] = positions[j - 1] + counts[j - 1];
        }

        for (int j = 0; j < n; j++) {
            int word_index = input_data[permutations[j]][current_latter] - A;
            new_permutations[positions[word_index]] = permutations[j];
            positions[word_index]++;
        }
        copy_n(new_permutations, n, permutations);
    }

    for (int i = 0; i < n; i++) {
        cout << input_data[permutations[i]] << endl;
    }

    return 0;
}