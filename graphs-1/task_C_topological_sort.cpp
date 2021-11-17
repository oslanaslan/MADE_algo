#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int DEFAULT_COLOR = 0;
const int NONE_PARENT = -1;

template<class Key>
class Graph {
    bool is_undirected;
    Key vertex_count;
    vector<vector<Key>> edges;

    void dfs(Key vertex, vector<int>& visited, vector<Key>& sort_result, Key parent_vertex, bool& success) {
        visited[vertex] = 1;

        for (Key second_vertex : this->edges[vertex]) {
            if (visited[second_vertex] == DEFAULT_COLOR) {
                this->dfs(second_vertex, visited, sort_result, vertex, success);
            }
            if (visited[second_vertex] == 1 && second_vertex != parent_vertex) {
                success = false;
            }
        }

        visited[vertex] = 2;
        sort_result.push_back(vertex);
    }

public:

    Graph(Key vertex_count = 0, bool is_undirected = true) {
        this->vertex_count = vertex_count;
        this->is_undirected = is_undirected;
        this->edges.resize(this->vertex_count);
    }

    void add_edge(Key first_vertex, Key second_vertex) {
        this->edges[first_vertex].push_back(second_vertex);
        if (this->is_undirected) {
            this->edges[second_vertex].push_back(first_vertex);
        }
    }

    void print_graph() {
        for (Key vertex = 0; vertex < this->vertex_count; vertex++) {
            for (Key pair_vertex : this->edges[vertex]) {
                if (this->is_undirected) {
                    cout << vertex << " <-> " << pair_vertex << endl;
                }
                else {
                    cout << vertex << " -> " << pair_vertex << endl;
                }
            }
        }
    }

    pair<vector<Key>, bool> topological_sort() {
        vector<int> visited;
        vector<Key> sort_result;
        bool success = true;

        visited.resize(this->vertex_count);

        for (Key start_vertex = 0; start_vertex < this->vertex_count; start_vertex++) {
            if (visited[start_vertex] == DEFAULT_COLOR) {
                this->dfs(start_vertex, visited, sort_result, NONE_PARENT, success);
            }
        }

        return make_pair(sort_result, success);
    }
};

int main() {
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    Graph<int> graph(vertex_count, false);
    int first_vertex, second_vertex;

    for (int i = 0; i < edge_count; i++) {
        cin >> first_vertex >> second_vertex;
        graph.add_edge(first_vertex - 1, second_vertex - 1);
    }

    pair<vector<int>, bool> result = graph.topological_sort();

    if (result.second) {
        for (int i = vertex_count - 1; i >= 0; i--) {
            cout << result.first[i] + 1 << " ";
        }
    }
    else {
        cout << -1 << endl;
    }
    
    return 0;
}