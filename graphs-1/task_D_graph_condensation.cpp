#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

template<class Key>
class Graph {
    Key vertex_count;
    vector<vector<Key>> edges;
    vector<vector<Key>> reverced_edges;

    void dfs(Key vertex, vector<bool>& visited, vector<Key>& result, bool is_reverce, Key marker = 0) {
        visited[vertex] = true;
        vector<Key>* current_subtree;

        if (is_reverce) {
            result[vertex] = marker;
            current_subtree = &(this->reverced_edges[vertex]);
        }
        else {
            current_subtree = &(this->edges[vertex]);
        }

        for (Key second_vertex : *(current_subtree)) {
            if (!visited[second_vertex]) {
                this->dfs(second_vertex, visited, result, is_reverce, marker);
            }
        }

        if (!is_reverce) {
            result.push_back(vertex);
        }
    }

public:

    Graph(Key vertex_count = 0) {
        this->vertex_count = vertex_count;
        this->edges.resize(this->vertex_count);
        this->reverced_edges.resize(this->vertex_count);
    }

    void add_edge(Key first_vertex, Key second_vertex) {
        this->edges[first_vertex].push_back(second_vertex);
        this->reverced_edges[second_vertex].push_back(first_vertex);
    }

    vector<Key> get_condensation() {
        vector<bool> visited;
        vector<Key> tout;
        vector<Key> components;
        bool is_reverce = false;
        int component_counter = 0;

        visited.resize(this->vertex_count);
        components.resize(this->vertex_count);

        for (Key start_vertex = 0; start_vertex < this->vertex_count; start_vertex++) {
            if (!visited[start_vertex]) {
                this->dfs(start_vertex, visited, tout, is_reverce);
            }
        }

        fill(visited.begin(), visited.end(), false);
        is_reverce = true;

        for (Key i = 0; i < this->vertex_count; i++) {
            Key start_vertex = tout[this->vertex_count - 1 - i];

            if (!visited[start_vertex]) {
                this->dfs(start_vertex, visited, components, is_reverce, component_counter++);
            }
        }

        return components;
    }

    set<pair<Key, Key>> get_condensated_edges() {
        vector<Key> components = this->get_condensation();
        set<pair<Key, Key>> condensation_edges;

        for (Key first_vertex = 0; first_vertex < this->vertex_count; first_vertex++) {
            for(Key second_vertex : this->edges[first_vertex]) {
                Key first_super_vertex = components[first_vertex];
                Key second_super_vertex = components[second_vertex];
                if (first_super_vertex != second_super_vertex) {
                    condensation_edges.insert(make_pair(
                        components[first_vertex],
                        components[second_vertex]
                    ));
                }
            }
        }

        return condensation_edges;
    }

    Key get_edge_count() {
        set<pair<Key, Key>> condensation_edges = this->get_condensated_edges();

        return condensation_edges.size();
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

    cout << graph.get_edge_count() << endl;
    
    return 0;
}