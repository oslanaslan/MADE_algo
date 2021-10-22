#include <iostream>

using namespace std;

const int INF = 1e9;

int main() {
    int n, m;
    cin >> n >> m;
    short coin;
    int values[n][m];
    char way[n + m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int first_value = i > 0 ? values[i - 1][j] : -INF;
            int second_value = j > 0 ? values[i][j - 1] : -INF;

            cin >> coin;
            values[i][j] = ((i > 0 || j > 0) ? max(first_value, second_value) : 0) + coin;
        }
    }

    int cur_pos_x = m - 1;
    int cur_pos_y = n - 1;
    int way_length = 0;

    while (cur_pos_x > 0 || cur_pos_y > 0) {
        int first_value = cur_pos_y > 0 ? values[cur_pos_y - 1][cur_pos_x] : -INF;
        int second_value = cur_pos_x > 0 ? values[cur_pos_y][cur_pos_x - 1] : -INF;

        if (first_value >= second_value) {
            cur_pos_y--;
            way[way_length++] = 'D';
        }
        else {
            cur_pos_x--;
            way[way_length++] = 'R';
        }
    }

    cout << values[n - 1][m - 1] << endl;

    for (int i = way_length - 1; i >= 0; i--) {
        cout << way[i];
    }

    return 0;
}