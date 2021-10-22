#include <iostream>
#include <string>
 
using namespace std;

template<class Key, class Value>
class LinckedHashtable {
    
    const uint64_t INITIAL_CAPACITY = 1e5;
    const uint64_t A = 31;
    const uint64_t P = 3021377;
    const uint64_t SHIFT = 'a' - 1;
    const string DEFAULT_RESULT = "none";

    struct ListNode {
        Key key;
        Value value;
        ListNode *next_node;
        ListNode *prev_node;

        ListNode() {
            this->key = Key();
            this->value = Value();
            this->next_node = nullptr;
            this->prev_node = nullptr;
        }

        ListNode(Key &key, Value &value) {
            this->key = key;
            this->value = value;
            this->next_node = nullptr;
            this->prev_node = nullptr;
        }
    };

    struct ArrayNode {
        ListNode *head;
        ListNode *tail;

        ArrayNode() {
            this->head = nullptr;
            this->tail = nullptr;
        }
    };

    ArrayNode *data;
    uint64_t capacity;

    uint64_t hash_by_key(Key &key) {
        uint64_t hashed_key = 0;

        for (uint64_t i = 0; i < key.length(); i++) {
            hashed_key = (hashed_key * this->A + (key[i] - this->SHIFT)) % this->P;
        }

        hashed_key %= this->capacity;
        return hashed_key;
    }

    ListNode *find_node(Key &key) {
        uint64_t position = this->hash_by_key(key);
        ListNode *current_node = this->data[position].head;

        while (current_node != nullptr && current_node->key != key) {
            current_node = current_node->next_node;
        }

        return current_node;
    }

public:

    LinckedHashtable() {
        this->capacity = INITIAL_CAPACITY;
        this->data = new ArrayNode[this->capacity];
    }

    void put_item(Key key, Value value) {
        ListNode *current_node = this->find_node(key);

        if (current_node == nullptr) {
            uint64_t position = this->hash_by_key(key);
            ListNode *new_node = new ListNode(key, value);

            new_node->prev_node = this->data[position].tail;

            if (this->data[position].tail != nullptr) {
                this->data[position].tail->next_node = new_node;
            }
            else {
                this->data[position].head = new_node;
            }

            this->data[position].tail = new_node;
        }
        else {
            current_node->value = value;
        }
    }

    void delete_item(Key &key) {
        ListNode *current_node = this->find_node(key);

        if (current_node != nullptr) {
            if (current_node->prev_node != nullptr && current_node->next_node != nullptr) {
                current_node->prev_node->next_node = current_node->next_node;
                current_node->next_node->prev_node = current_node->prev_node;
            }
            
            uint64_t position = this->hash_by_key(key);

            if (current_node->prev_node == nullptr) {
                this->data[position].head = current_node->next_node;
            }

            if (current_node->next_node == nullptr) {
                this->data[position].tail = current_node->prev_node;
            }
        }
    }

    Value get_item(Key key) {
        ListNode *current_node = this->find_node(key);
        Value *result = nullptr;

        if (current_node != nullptr) {
            result = &current_node->value;
        }

        return (result == nullptr ? DEFAULT_RESULT : *result);
    }

    ~LinckedHashtable() {
        for (uint64_t i = 0; i < this->capacity; i++) {
            ListNode *current_node = this->data[i].head;
            ListNode *next_node = nullptr;

            while (current_node != nullptr) {
                next_node = current_node->next_node;
                delete current_node;
                current_node = next_node;
            }
        }

        delete[] this->data;
    }

};
 
int main() {
    LinckedHashtable<string, string> map;
    string cmd, key, value;
    uint64_t res_count = 0;
 
    while (cin >> cmd >> key) {
        if (cmd == "put") {
            cin >> value;
            map.put_item(key, value);
        }
        else if (cmd == "delete") {
            map.delete_item(key);
        }
        else {
            cout << map.get_item(key) << endl;
        }
    }
 
    return 0;
}