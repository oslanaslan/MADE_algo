#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int DEFAULT_COLOR = 0;

template<class Key>
class Graph {
    bool is_undirected;
    Key vertex_count;
    vector<vector<Key>> edges;

    void dfs(Key vertex, vector<Key>& color, Key current_color) {
        color[vertex] = current_color;

        for (Key second_vertex : this->edges[vertex]) {
            if (color[second_vertex] == DEFAULT_COLOR) {
                this->dfs(second_vertex, color, current_color);
            }
        }
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

    pair<vector<Key>, Key> get_connected_components() {
        vector<Key> color;
        Key current_color = DEFAULT_COLOR;

        color.resize(this->vertex_count);

        for (Key start_vertex = 0; start_vertex < this->vertex_count; start_vertex++) {
            if (color[start_vertex] == DEFAULT_COLOR) {
                current_color++;
                this->dfs(start_vertex, color, current_color);
            }
        }

        return make_pair(color, current_color);
    }

};

int main() {
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;
    Graph<int> graph(vertex_count);
    int first_vertex, second_vertex;

    for (int i = 0; i < edge_count; i++) {
        cin >> first_vertex >> second_vertex;
        graph.add_edge(first_vertex - 1, second_vertex - 1);
    }

    pair<vector<int>, int> result = graph.get_connected_components();

    cout << result.second << endl;

    for (int i = 0; i < vertex_count; i++) {
        cout << result.first[i] << " ";
    }
    
    return 0;
}