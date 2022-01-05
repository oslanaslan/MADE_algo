#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <cstring>

using namespace std;

const uint32_t INF = 1e9;

struct couple {
    uint32_t first;
    uint32_t second;

    couple(uint32_t a, uint32_t b) {
        this->first = a;
        this->second = b;
    }

    bool operator<(const couple& other) const {
        return this->first == other.first ? this->second < other.second : this->first < other.first;
    }
};

uint32_t* get_shortest_paths(uint32_t n, uint32_t m, vector<vector<couple>>& weights) {
    uint32_t* shortest_paths = new uint32_t[n];
    bool used[n];
    set<couple> queue;
 
    memset(shortest_paths, -1, sizeof(uint32_t) * n);
    memset(used, 0, sizeof(bool) * n);

    queue.insert(couple(0, 0));
    shortest_paths[0] = 0;
 
    for (uint32_t i = 0; i < n; i++) {
        if (queue.empty()) {
            break;
        }
 
        couple next_pair = queue.extract(queue.begin()).value();
        uint32_t next = next_pair.second;
        used[next] = true;
 
        for (couple current_couple : weights[next]) {
            uint32_t neighbour_node = current_couple.first;
            uint32_t current_weight = current_couple.second;
            uint32_t old_short_path = shortest_paths[neighbour_node];
            shortest_paths[neighbour_node] = min(shortest_paths[neighbour_node], shortest_paths[next] + current_weight);
            couple current_pair = couple(old_short_path, neighbour_node);
            if ((used[neighbour_node] || old_short_path != shortest_paths[neighbour_node]) && queue.count(current_pair) > 0) {
                queue.extract(queue.find(current_pair));
            }
            if (!used[neighbour_node]) {
                queue.insert(couple(shortest_paths[neighbour_node], neighbour_node));
            }
        }
    }
 
    return shortest_paths;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
 
    uint32_t n, m;
    vector<vector<couple>> weights;
    cin >> n >> m;

    weights.resize(n);
 
    for (uint32_t i = 0; i < m; i++) {
        uint32_t node_1, node_2, weight;
 
        cin >> node_1 >> node_2 >> weight;
        node_1--;
        node_2--;
        weights[node_1].push_back(couple(node_2, weight));
        weights[node_2].push_back(couple(node_1, weight));
    }
 
    uint32_t* results = get_shortest_paths(n, m, weights);
 
    for (uint32_t i = 0; i < n; i++) {
        cout << results[i] << " ";
    }
    
    delete[] results;
 
    return 0;
}