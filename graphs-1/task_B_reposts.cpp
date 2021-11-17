#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

const int DEFAULT_COLOR = 0;

class Graph {
    bool is_undirected;
    int vertex_count;
    vector<vector<int>> edges;

    void dfs(int vertex, vector<bool>& visited, int& current_max_depth, int current_depth) {
        visited[vertex] = true;

        for (int second_vertex : this->edges[vertex]) {
            if (!visited[second_vertex]) {
                this->dfs(second_vertex, visited, current_max_depth, current_depth + 1);
            }
        }

        if (current_depth > current_max_depth) {
            current_max_depth = current_depth;
        }
    }

public:

    Graph(int vertex_count = 0, bool is_undirected = true) {
        this->vertex_count = vertex_count;
        this->is_undirected = is_undirected;
        this->edges.resize(this->vertex_count);
    }

    void add_edge(int first_vertex, int second_vertex) {
        this->edges[first_vertex].push_back(second_vertex);
        if (this->is_undirected) {
            this->edges[second_vertex].push_back(first_vertex);
        }
    }

    int get_max_depth() {
        vector<bool> visited;
        int current_max_depth = 0;
        int current_depth = 1;

        visited.resize(this->vertex_count);

        for (int start_vertex = 0; start_vertex < this->vertex_count; start_vertex++) {
            if (!visited[start_vertex]) {
                this->dfs(start_vertex, visited, current_max_depth, current_depth);
            }
        }

        return current_max_depth;
    }
};

int main() {
    int vertex_index = 0;
    unordered_map<string, int> name_to_index_map;
    int vertex_count, edge_count;
    string name_to, repost, name_from;
    int index_to, index_from;
    cin >> edge_count;
    vertex_count = edge_count + 1;
    Graph graph(vertex_count);

    for (int i = 0; i < edge_count; i++) {
        cin >> name_to >> repost >> name_from;

        std::for_each(name_to.begin(), name_to.end(), [](char & c) {
            c = ::tolower(c);
        });
        std::for_each(name_from.begin(), name_from.end(), [](char & c) {
            c = ::tolower(c);
        });
        
        if (name_to_index_map.count(name_from)) {
            index_from = name_to_index_map[name_from];
        }
        else {
            index_from = vertex_index++;
            name_to_index_map[name_from] = index_from;
        }
        if (name_to_index_map.count(name_to)) {
            index_to = name_to_index_map[name_to];
        }
        else {
            index_to = vertex_index++;
            name_to_index_map[name_to] = index_to;
        }
        graph.add_edge(index_from, index_to);
    }

    int result = graph.get_max_depth();

    cout << result << endl;
    
    return 0;
}
