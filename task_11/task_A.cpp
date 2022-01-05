#include <iostream>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;

const int INF = 100;
const int NO_PARENT = -1;
const int X_DIRECTIONS[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int Y_DIRECTIONS[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int POSSIBLE_DIRECTIONS_COUNT = 8;

bool is_correct_position(int x, int y, int N) {
    if (x < 0 || y < 0 || x >= N || y >= N) {
        return false;
    }

    return true;
}

vector<pair<int, int>> find_shortest_way(int N, int start_x, int start_y, int end_x, int end_y) {
    pair<int, int>** parent_mat = new pair<int, int>*[N];
    bool** used = new bool*[N];
    queue<pair<int, int>> queue;

    for (int i = 0; i < N; i++) {
        parent_mat[i] = new pair<int, int>[N];
        used[i] = new bool[N];

        for (int j = 0; j < N; j++) {
            parent_mat[i][j] = make_pair(NO_PARENT, NO_PARENT);
            used[i][j] = false;
        }
    }

    // BFS

    used[start_x][start_y] = true;
    queue.push(make_pair(start_x, start_y));

    while (!queue.empty()) {
        pair<int, int> current_node = queue.front();
        int current_x = current_node.first;
        int current_y = current_node.second;

        queue.pop();

        for (int i = 0; i < POSSIBLE_DIRECTIONS_COUNT; i++) {
            int next_pos_x = current_x + X_DIRECTIONS[i];
            int next_pos_y = current_y + Y_DIRECTIONS[i];

            if (is_correct_position(next_pos_x, next_pos_y, N) && !used[next_pos_x][next_pos_y]) {
                used[next_pos_x][next_pos_y] = true;
                queue.push(make_pair(next_pos_x, next_pos_y));
                parent_mat[next_pos_x][next_pos_y] = make_pair(current_x, current_y);
            }
        }
    }

    // Shortest path

    vector<pair<int, int>> result;
    int current_x = end_x;
    int current_y = end_y;

    while (parent_mat[current_x][current_y].first != NO_PARENT) {
        result.push_back(make_pair(current_x, current_y));
        pair<int, int> parent_node = parent_mat[current_x][current_y];
        current_x = parent_node.first;
        current_y = parent_node.second;
    }

    result.push_back(make_pair(current_x, current_y));

    return result;
}

int main() {
    int N, start_x, start_y, end_x, end_y;
    cin >> N;
    cin >> start_x >> start_y;
    cin >> end_x >> end_y;

    vector<pair<int, int>> result = find_shortest_way(N, start_x - 1, start_y - 1, end_x - 1, end_y - 1);
    cout << result.size() << endl;

    for (int i = result.size() - 1; i >= 0; i--) {
        cout << (result[i].first + 1) << " " << (result[i].second + 1) << endl;
    }

    return 0;
}