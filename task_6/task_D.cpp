#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_INPUT_LEN = 1e3;

int main() {
    char str_1[MAX_INPUT_LEN + 1];
    char str_2[MAX_INPUT_LEN + 1];

    scanf("%s", str_1);
    scanf("%s", str_2);

    int str_1_len = strlen(str_1);
    int str_2_len = strlen(str_2);
    int values[str_1_len + 1][str_2_len + 1];

    for (int i = 0; i < str_1_len + 1; i++) {
        for (int j = 0; j < str_2_len + 1; j++) {
            if (i == 0 && j == 0) {
                values[i][j] = 0;
            }
            else if (i > 0 && j == 0) {
                values[i][j] = i;
            }
            else if (i == 0 && j > 0) {
                values[i][j] = j;
            }
            else {
                values[i][j] = min(min(values[i - 1][j], values[i][j - 1]) + 1, values[i - 1][j - 1] + 
                    (str_1[i - 1] == str_2[j - 1] ? 0 : 1));
            }
        }
    }

    cout << values[str_1_len][str_2_len] << endl;

    return 0;
}