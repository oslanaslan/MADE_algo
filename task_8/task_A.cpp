#include <iostream>
#include <string>

using namespace std;

template<class Key>
class Tree {

    struct Node {
        Key key;
        Node* left;
        Node* right;

        Node() {
            this->key = Key();
            this->left = nullptr;
            this->right = nullptr;
        }

        Node(Key key) {
            this->key = key;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    Node* head;

    Node* find_max(Node* current_node) {
        while (current_node->right) {
            current_node = current_node->right;
        }

        return current_node;
    }

    Node* insert_node(Node* current_node, Key key) {
        if (!current_node) {
            return new Node(key);
        }
        else if (key < current_node->key) {
            current_node->left = this->insert_node(current_node->left, key);
        }
        else if (key > current_node->key) {
            current_node->right = this->insert_node(current_node->right, key);
        }

        return current_node;
    }

    Node* search(Node* current_node, Key key) {
        if (!current_node || current_node->key == key) {
            return current_node;
        }
        if (key < current_node->key) {
            return this->search(current_node->left, key);
        }
        else {
            return this->search(current_node->right, key);
        }
    }

    Node* delete_node(Node* current_node, Key key) {
        if (!current_node) {
            return nullptr;
        }
        if (key < current_node->key) {
            current_node->left = delete_node(current_node->left, key);
        }
        else if (key > current_node->key) {
            current_node->right = delete_node(current_node->right, key);
        }
        if (current_node->key == key) {
            if (current_node->right && current_node->left) {
                current_node->key = this->find_max(current_node->left)->key;
                current_node->left = this->delete_node(current_node->left, current_node->key);
            }
            else if (current_node->left) {
                Node* temp = current_node->left;

                delete current_node;
                current_node = temp;
            }
            else if (current_node->right) {
                Node* temp = current_node->right;

                delete current_node;
                current_node = temp;
            }
            else {
                delete current_node;
                current_node = nullptr;
            }
        }

        return current_node;
    }

    Node* next_node(Key key) {
        Node* current_node = this->head;
        Node* res = nullptr;

        while (current_node) {
            if (current_node->key > key) {
                res = current_node;
                current_node = current_node->left;
            }
            else {
                current_node = current_node->right;
            }
        }

        return res;
    }

    Node* prev_node(Key key) {
        Node* current_node = this->head;
        Node* res = nullptr;

        while (current_node) {
            if (current_node->key < key) {
                res = current_node;
                current_node = current_node->right;
            }
            else {
                current_node = current_node->left;
            }
        }

        return res;
    }

    void print_node(Node* current_node) {
        if (!current_node) {
            return;
        }
        if (current_node->left) {
            print_node(current_node->left);
        }
        cout << current_node->key << " ";
        if (current_node->right) {
            print_node(current_node->right);
        }
    }

    void delete_subtree(Node* current_node) {
        if (current_node) {
            this->delete_subtree(current_node->left);
            this->delete_subtree(current_node->right);
            delete current_node;
        }
    }

public:

    Tree() {
        this->head = nullptr;
    }

    void insert(Key key) {
        this->head = this->insert_node(this->head, key);
    }

    void delete_key(Key key) {
        this->head = this->delete_node(this->head, key);
    }

    string exists(Key key) {
        Node* res = this->search(this->head, key);

        return res ? "true" : "false";
    }

    string next(Key key) {
        Node* res = this->next_node(key);

        return res ? to_string(res->key) : "none";
    }

    string prev(Key key) {
        Node* res = this->prev_node(key);

        return res ? to_string(res->key) : "none";
    }

    void print_tree() {
        this->print_node(this->head);
        cout << endl;
    }

    ~Tree() {
        this->delete_subtree(this->head);
    }
};

int main() {
    Tree<int> tree;
    string cmd;
    int key;
    
    while (cin >> cmd >> key) {
        if (cmd == "insert") {
            tree.insert(key);
        }
        else if (cmd == "delete") {
            tree.delete_key(key);
        }
        else if (cmd == "exists") {
            cout << tree.exists(key) << endl;
        }
        else if (cmd == "next") {
            cout << tree.next(key) << endl;
        }
        else if (cmd == "prev") {
            cout << tree.prev(key) << endl;
        }
    }

    return 0;
}