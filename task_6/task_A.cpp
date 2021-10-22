#include <iostream>

using namespace std;

const int INF = 1e6;

int main() {
    int n, k;
    cin >> n >> k;
    int coins[n];
    int values[n];
    int parent[n];
    int way[n];
    int way_length = 0;

    coins[0] = 0;
    coins[n - 1] = 0;
    values[0] = 0;

    for (int i = 1; i < n - 1; i++) {
        cin >> coins[i];
    }

    for (int i = 1; i < n; i++) {
        int cur_max = -INF;
        int cur_max_pos = 0;

        for (int j = 1; j < min(k + 1, i + 1); j++) {
            if (values[i - j] > cur_max) {
                cur_max = values[i - j];
                cur_max_pos = i - j;
            }
        }

        values[i] = cur_max + coins[i];
        parent[i] = cur_max_pos;
    }

    int i = n - 1;

    while (i > 0) {
        way[way_length++] = i + 1;
        i = parent[i];
    }

    way[way_length++] = 1;
    cout << values[n - 1] << endl;
    cout << way_length - 1 << endl;

    for (int i = way_length - 1; i >= 0; i--) {
        cout << way[i] << " ";
    }

    return 0;
}