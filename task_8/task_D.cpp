#include <iostream>
#include <string>

using namespace std;

uint64_t MOD_CONST_FROM_TASK = 1e9;

template<class Key>
class Tree {

    struct Node {
        Key key;
        Node* left;
        Node* right;
        uint64_t height;
        Key left_count;
        Key right_count;

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

    void delete_node(Node* node) {
        if (!node) {
            return;
        }
        delete_node(node->left);
        delete_node(node->right);
        delete node;
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

    uint64_t prefix_sum(Node* current_node, uint64_t left_border, uint64_t current_sum) {
        if (!current_node) {
            return current_sum;
        }
        if (current_node->key < left_border) {
            current_sum += current_node->left_count + current_node->key;
            return this->prefix_sum(current_node->right, left_border, current_sum);
        }
        else {
            return this->prefix_sum(current_node->left, left_border, current_sum);
        }
    }

    uint64_t postfix_sum(Node* current_node, uint64_t right_border, uint64_t current_sum) {
        if (!current_node) {
            return current_sum;
        }
        if (current_node->key > right_border) {
            current_sum += current_node->right_count + current_node->key;
            return this->postfix_sum(current_node->left, right_border, current_sum);
        }
        else {
            return this->postfix_sum(current_node->right, right_border, current_sum);
        }
    }

    void print_node(Node* current_node) {
        if (!current_node) {
            return;
        }
        if (current_node->left) {
            cout << current_node->key << " " << current_node->left_count << " " << current_node->right_count;
            cout << " -> " << current_node->left->key << " (l)" << endl;
            print_node(current_node->left);
        }
        if (current_node->right) {
            cout << current_node->key << " " << current_node->left_count << " " << current_node->right_count;
            cout << " -> " << current_node->right->key << " (r)" << endl;
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
        if (!current_node) {
            return;
        }
        int left_height = this->get_height(current_node->left);
        int right_height = this->get_height(current_node->right);

        current_node->height = (left_height > right_height ? left_height : right_height) + 1;
        current_node->left_count = current_node->left ? current_node->left->left_count + 
            current_node->left->right_count + current_node->left->key : 0;
        current_node->right_count = current_node->right ? current_node->right->left_count +
            current_node->right->right_count + current_node->right->key : 0;
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

    uint64_t sum(unsigned int left_border, unsigned int right_border) {
        if (!this->head) {
            return 0;
        }

        uint64_t current_sum = this->head->left_count + this->head->key + this->head->right_count;
        uint64_t pref_sum = this->prefix_sum(this->head, left_border, 0);
        uint64_t post_sum = this->postfix_sum(this->head, right_border, 0);

        return current_sum - pref_sum - post_sum;
    }

    void print_tree() {
        this->print_node(this->head);
        cout << endl;
    }

    ~Tree() {
        delete_node(this->head);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);

    Tree<uint64_t> tree;
    string cmd;
    string prev_cmd = "";
    uint64_t n, key_1, key_2;
    uint64_t prev_res = 0;

    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> cmd;

        if (cmd == "+") {
            cin >> key_1;

            if (prev_cmd == "?") {
                key_1 = (key_1 + prev_res) % MOD_CONST_FROM_TASK;
            }

            tree.insert(key_1);
        }
        else if (cmd == "?") {
            cin >> key_1 >> key_2;
            prev_res = tree.sum(key_1, key_2);
            cout << prev_res << endl;
        }

        prev_cmd = cmd;
    }

    return 0;
}