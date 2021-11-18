#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

const int START_VERTEX = 0;
const int NO_PARENT = -1;

template<class Key>
class Graph {
    Key vertex_count;
    vector<vector<Key>> edges;
    vector<bool> visited;
    vector<Key> tin;
    vector<Key> fup;
    Key timer = 0;

    void modified_dfs(Key vertex, Key parent, set<Key>& all_points) {
        int children_count = 0;

        this->timer++;
        visited[vertex] = true;
        this->tin[vertex] = this->timer;
        this->fup[vertex] = this->timer;

        for (Key next_vertex : this->edges[vertex]) {
            if (next_vertex != parent) {
                if(this->visited[next_vertex]) {
                    this->fup[vertex] = (this->fup[vertex] <= this->tin[next_vertex] ?
                        this->fup[vertex] : this->tin[next_vertex]);
                }
                else {
                    this->modified_dfs(next_vertex, vertex, all_points);
                    this->fup[vertex] = (this->fup[vertex] <= this->fup[next_vertex] ?
                        this->fup[vertex] : this->fup[next_vertex]);
                    if (this->fup[next_vertex] >= this->tin[vertex] && parent != NO_PARENT) {
                        all_points.insert(vertex);
                    }
                    children_count++;
                }
            }
        }

        if (parent == NO_PARENT && children_count > 1) {
            all_points.insert(vertex);
        }
    }

public:

    Graph(Key vertex_count = 0) {
        this->vertex_count = vertex_count;
        this->edges.resize(this->vertex_count);
        this->tin.resize(this->vertex_count);
        this->fup.resize(this->vertex_count);
        this->visited.resize(this->vertex_count);
        this->timer = 0;
    }

    void add_edge(Key first_vertex, Key second_vertex) {
        this->edges[first_vertex].push_back(second_vertex);
        this->edges[second_vertex].push_back(first_vertex);
    }

    set<Key> get_points() {
        set<Key> all_points;

        for (Key start_vertex = 0; start_vertex < this->vertex_count; start_vertex++) {
            this->modified_dfs(start_vertex, NO_PARENT, all_points);
        }

        return all_points;
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

    set<int> all_points = graph.get_points();
    cout << all_points.size() << endl;
    for (int item : all_points) {
        cout << (item + 1) << " ";
    }
    
    return 0;
}