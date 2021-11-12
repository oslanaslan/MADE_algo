#include <iostream>
#include <string>

using namespace std;

template<class Key>
class Tree {

    struct Node {
        Key key;
        Node* left;
        Node* right;
        int height;
        int left_count;
        int right_count;

        Node() {
            this->key = Key();
            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
            this->left_count = 0;
            this->right_count = 0;
        }

        Node(Key key) {
            this->key = key;
            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
            this->left_count = 0;
            this->right_count = 0;
        }
    };

    Node* head;

    void delete_subtree(Node* current_node) {
        if (current_node) {
            this->delete_subtree(current_node->left);
            this->delete_subtree(current_node->right);
            delete current_node;
        }
    }

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

        current_node = this->balance(current_node);

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
            if (!current_node->right && !current_node->left) {
                delete current_node;
                current_node = nullptr;
            }
            else if (current_node->left && !current_node->right) {
                Node* temp = current_node->left;

                delete current_node;
                current_node = temp;
            }
            else if (current_node->right && !current_node->left) {
                Node* temp = current_node->right;

                delete current_node;
                current_node = temp;
            }
            else {
                current_node->key = this->find_max(current_node->left)->key;
                current_node->left = this->delete_node(current_node->left, current_node->key);
            }
        }

        current_node = this->balance(current_node);

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
            cout << current_node->key << " -> " << current_node->left->key << " (l)" << endl;
            print_node(current_node->left);
        }
        if (current_node->right) {
            cout << current_node->key << " -> " << current_node->right->key << " (r)" << endl;
            print_node(current_node->right);
        }
        if (!current_node->left && !current_node->right) {
            cout << current_node->key << endl;
        }
    }

    int get_height(Node* current_node) {
        return current_node ? current_node->height : 0;
    }

    int balance_factor(Node* current_node) {
        return this->get_height(current_node->right) - this->get_height(current_node->left);
    }

    void fix_height(Node* current_node) {
        int left_height = this->get_height(current_node->left);
        int right_height = this->get_height(current_node->right);

        current_node->height = (left_height > right_height ? left_height : right_height) + 1;
        current_node->left_count = current_node->left ? current_node->left->left_count + 
            current_node->left->right_count + 1 : 0;
        current_node->right_count = current_node->right ? current_node->right->left_count +
            current_node->right->right_count + 1 : 0;
    }

    Node* rotate_right(Node* current_node) {
        Node* left_node = current_node->left;

        current_node->left = left_node->right;
        left_node->right = current_node;
        this->fix_height(current_node);
        this->fix_height(left_node);

        return left_node;
    }

    Node* rotate_left(Node* current_node) {
        Node* right_node = current_node->right;

        current_node->right = right_node->left;
        right_node->left = current_node;
        this->fix_height(current_node);
        this->fix_height(right_node);

        return right_node;
    }

    Node* balance(Node* current_node) {
        if (!current_node) {
            return current_node;
        }

        this->fix_height(current_node);
        int current_balance_factor = this->balance_factor(current_node);

        if(current_balance_factor == 2) {
            if(this->balance_factor(current_node->right) < 0) {
                current_node->right = this->rotate_right(current_node->right);
            }

            return rotate_left(current_node);
        }
        if(current_balance_factor == -2) {
            if(this->balance_factor(current_node->left) > 0) {
                current_node->left = this->rotate_left(current_node->left);
            }

            return this->rotate_right(current_node);
        }

        return current_node;
    }

public:

    struct Result {
        Key key;
        bool res;

        Result(Key key, bool res) {
            this->key = key;
            this->res = res;
        }
    };

    Result k_max_node(Node* current_node, Key target) {
        if (!current_node) {
            return Result(0, false);
        }
        if (target == current_node->right_count + 1) {
            return Result(current_node->key, true);
        }
        if (target < current_node->right_count + 1) {
            return this->k_max_node(current_node->right, target);
        }
        else {
            return this->k_max_node(current_node->left, target - current_node->right_count - 1);
        }
    }

    Tree() {
        this->head = nullptr;
    }

    void insert(Key key) {
        this->head = this->insert_node(this->head, key);
    }

    void delete_key(Key key) {
        this->head = this->delete_node(this->head, key);
    }

    bool exists(Key key) {
        Node* res = this->search(this->head, key);

        return res ? true : false;
    }

    Result next(Key key) {
        Node* res = this->next_node(key);

        return res ? Result(res->key, true) : Result(0, false);
    }

    Result prev(Key key) {
        Node* res = this->prev_node(key);

        return res ? Result(res->key, true) : Result(0, false);
    }

    Result k_max(Key target) {
        return this->k_max_node(this->head, target);
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
    std::ios_base::sync_with_stdio(false);

    Tree<int> tree;
    string cmd;
    int key;
    int n;

    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> cmd >> key;

        if (cmd == "1" || cmd == "+1") {
            tree.insert(key);
        }
        else if (cmd == "-1") {
            tree.delete_key(key);
        }
        else if (cmd == "0") {
            Tree<int>::Result res = tree.k_max(key);

            cout << (res.res ? res.key : 0) << endl;
        }
    }

    return 0;
}