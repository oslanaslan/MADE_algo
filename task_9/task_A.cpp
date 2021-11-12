#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Treap {
    struct Node {
        int key;
        int value;
        Node* left;
        Node* right;

        Node() {
            this->key = 0;
            this->value = 0;
            this->right = nullptr;
            this->left = nullptr;
        }

        Node(int value, int key) {
            this->key = key;
            this->value = value;
            this->right = nullptr;
            this->left = nullptr;
        }
    };

    Node* head;

    void print_node(Node* current_node) {
        if (!current_node) {
            return;
        }
        if (current_node->left) {
            print_node(current_node->left);
        }
        cout << current_node->value << " " << current_node->key << " ";
        if (current_node->right) {
            print_node(current_node->right);
        }
    }

    pair<Node*, Node*> split(Node* current_node, int value) {
        if (!current_node) {
            return make_pair(nullptr, nullptr);
        }

        if (current_node->value > value) {
            pair<Node*, Node*> split_res = this->split(current_node->left, value);
            current_node->left = split_res.second;

            return make_pair(split_res.first, current_node);
        }
        else {
            pair<Node*, Node*> split_res = this->split(current_node->right, value);
            current_node->right = split_res.first;

            return make_pair(current_node, split_res.second);
        }
    }

    Node* merge(Node* first_node, Node* second_node) {
        if (first_node && second_node) {
            if (first_node->key > second_node->key) {
                first_node->right = this->merge(first_node->right, second_node);

                return first_node;
            }
            else {
                second_node->left = this->merge(first_node, second_node->left);

                return second_node;
            }
        }
        else {
            return first_node ? first_node : second_node;
        }
    }

    void remove_subtree(Node* current_node) {
        if (current_node) {
            this->remove_subtree(current_node->left);
            this->remove_subtree(current_node->right);
            delete current_node;
        }
    }

    Node* next_node(int value) {
        Node* current_node = this->head;
        Node* res = nullptr;

        while (current_node) {
            if (current_node->value > value) {
                res = current_node;
                current_node = current_node->left;
            }
            else {
                current_node = current_node->right;
            }
        }

        return res;
    }

    Node* prev_node(int value) {
        Node* current_node = this->head;
        Node* res = nullptr;

        while (current_node) {
            if (current_node->value < value) {
                res = current_node;
                current_node = current_node->right;
            }
            else {
                current_node = current_node->left;
            }
        }

        return res;
    }

public:

    Treap() {
        this->head = nullptr;
    }

    string next(int value) {
        Node* res = this->next_node(value);

        return res ? to_string(res->value) : "none";
    }

    string prev(int value) {
        Node* res = this->prev_node(value);

        return res ? to_string(res->value) : "none";
    }

    void print_tree() {
        this->print_node(this->head);
        cout << endl;
    }

    void insert(int value) {
        pair<Node*, Node*> split_res = this->split(this->head, value);
        int key = rand();
        Node* new_node = new Node(value, key);
        Node* temp_node = this->merge(split_res.first, new_node);
        this->head = this->merge(temp_node, split_res.second);
    }

    void delete_value(int value) {
        pair<Node*, Node*> first_split_res = this->split(this->head, value);
        pair<Node*, Node*> second_split_res = this->split(first_split_res.first, value - 1);
        this->head = this->merge(second_split_res.first, first_split_res.second);
    }

    bool exists(int value) {
        Node* current_node = this->head;
        bool is_exists = false;

        while (current_node) {
            if (current_node->value > value) {
                current_node = current_node->left;
            }
            else if (current_node->value < value) {
                current_node = current_node->right;
            }
            else {
                is_exists = true;
                break;
            }
        }

        return is_exists;
    }

    ~Treap() {
        this->remove_subtree(this->head);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    Treap tree;
    string cmd;
    int value;

    while (cin >> cmd >> value) {
        if (cmd == "insert") {
            tree.insert(value);
        }
        else if (cmd == "delete") {
            tree.delete_value(value);
        }
        else if (cmd == "exists") {
            cout << (tree.exists(value) ? "true" : "false")  << endl;
        }
        else if (cmd == "next") {
            cout << tree.next(value) << endl;
        }
        else if (cmd == "prev") {
            cout << tree.prev(value) << endl;

        }
    }

    return 0;
}