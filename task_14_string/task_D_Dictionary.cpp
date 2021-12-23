#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <algorithm>
 
using namespace std;
 
int MAX_CHAR_COUNT = 30;
int TERM_NODE = -1;
char OFFSET = 'a';
int NO_SUCH_ELEMENT = -1;
int INITIAL_VEC_SIZE = 1e3;
 
class Tree {
    int size;
    vector<unordered_map<char, int> > data;
    vector<int> isTerminal;
 
public:
 
    Tree() {
        this->size = INITIAL_VEC_SIZE;
        this->data.resize(INITIAL_VEC_SIZE, unordered_map<char, int>());
        this->isTerminal.resize(INITIAL_VEC_SIZE, NO_SUCH_ELEMENT);
    }
 
    void print_tree() {
        for (int i = 0; i < this->data.size(); i++) {
            for (char j = 0; j < MAX_CHAR_COUNT; j++) {
                if (this->data[i].count(j)) {
                    cout << i << " -" << (char)(j + OFFSET)  << "-> " << (int)this->data[i][j] << endl;
                }
            }
        }
    }
 
    void add_row() {
        this->data.push_back(unordered_map<char, int>());
        this->isTerminal.push_back(NO_SUCH_ELEMENT);
    }
 
    void insert(string& s, int index) {
        int current_vertex = 0;

        for (int i = 0; i < s.size(); i++) {
            if (current_vertex >= this->data.size()) {
                this->add_row();
            }
            if (!this->data[current_vertex].count(s[i])) {
                this->data[current_vertex][s[i]] = this->size++;
                this->add_row();
            }
            current_vertex = this->data[current_vertex][s[i]];
        }
        this->isTerminal[current_vertex] = index;
    }
 
    vector<int> contains(string& s, int begin, int sub_len) {
        int current_vertex = 0;
        vector<int> all_found_res;
 
        for (int i = begin; i < sub_len + begin; i++) {
            if (!this->data[current_vertex].count(s[i])) {
                return all_found_res;
            }
            current_vertex = this->data[current_vertex][s[i]];

            if (this->isTerminal[current_vertex] != NO_SUCH_ELEMENT) {
                all_found_res.push_back(this->isTerminal[current_vertex]);
            }
        }
        return all_found_res;
    }
};
 
void convert_str(string& str) {
    for (int i = 0; i < str.size(); i++) {
        str[i] -= OFFSET;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    string main_str;
    string current_str;
    int max_str_len = 0;
    Tree tree;
    bool res;
    int word_count;
    cin >> main_str;
    cin >> word_count;
 
    vector<bool> res_vec(word_count, false);
 
    for (int i = 0; i < word_count; i++) {
        cin >> current_str;
        tree.insert(current_str, i);
        if (current_str.size() > max_str_len) {
            max_str_len = current_str.size();
        }
    }

    for (int i = 0; i < main_str.size(); i++) {
        vector<int> res = tree.contains(main_str, i, max_str_len);

        if (res.size() > 0) {
            for (int i : res) {
                res_vec[i] = true;
            }
        }
    }

    for (bool res : res_vec) {
        cout << (res ? "Yes" : "No") << endl;
    }
 
    return 0;
}
