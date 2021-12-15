#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int MAX_CHAR_COUNT = 30;
int TERM_NODE = -1;

class Tree {
    int size;
    vector<char*> data;
    vector<int> isTerminal;

public:

    Tree() {
        this->size = 1;
        this->add_row();
    }

    void add_row() {
        this->data.push_back(new char[MAX_CHAR_COUNT]);

        for (char i = 0; i < MAX_CHAR_COUNT; i++) {
            this->data[this->data.size() - 1][i] = TERM_NODE;
        }

        this->isTerminal.push_back(false);
    }

    void insert(string& s) {
        int current_vertex = 0;

        for (int i = 0; i < s.size(); i++) {
            if (current_vertex >= this->data.size()) {
                this->add_row();
            }
            if (this->data[current_vertex][s[i]] == TERM_NODE) {
                this->data[current_vertex][s[i]] = this->size++;
            }
            current_vertex = this->data[current_vertex][s[i]];
        }
        this->isTerminal[current_vertex] = true;
    }

    bool contains(string& s) {
        int current_vertex = 0;

        for (int i = 0; i < s.size(); i++) {
            if (this->data[current_vertex][s[i]] == TERM_NODE) {
                return false;
            }
            current_vertex = this->data[current_vertex][s[i]];
        }
        return this->isTerminal[current_vertex];
    }

    ~Tree() {
        for (char* row : this->data) {
            delete[] row;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    string main_str;
    Tree tree;
    bool res;
    int word_count;
    cin >> main_str;
    cin >> word_count;

    for (int i = 0; i < word_count; i++) {
        string str;

        cin >> str;
        tree.insert(str);
    }



    return 0;
}