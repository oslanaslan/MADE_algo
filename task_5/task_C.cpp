#include <iostream>
#include <string>
 
using namespace std;

template<class Key, class Value>
class LinkedMap {
    
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
        ListNode *next_added;
        ListNode *prev_added;

        ListNode() {
            this->key = Key();
            this->value = Value();
            this->next_node = nullptr;
            this->prev_node = nullptr;
            this->next_added = nullptr;
            this->prev_added = nullptr;
        }

        ListNode(Key &key, Value &value) {
            this->key = key;
            this->value = value;
            this->next_node = nullptr;
            this->prev_node = nullptr;
            this->next_added = nullptr;
            this->prev_added = nullptr;
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
    ListNode *first_added;
    ListNode *last_added;
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

    void pop_from_order_list(ListNode *current_node) {
        if (current_node == nullptr) {
            return;
        }

        if (current_node->prev_added != nullptr) {
            current_node->prev_added->next_added = current_node->next_added;
        }

        if (current_node->next_added != nullptr) {
            current_node->next_added->prev_added = current_node->prev_added;
        }

        if (this->first_added == current_node) {
            this->first_added = current_node->next_added;
        }

        if (this->last_added == current_node) {
            this->last_added = current_node->prev_added;
        }
    }

    void push_to_order_list(ListNode *current_node) {
        if (current_node == nullptr) {
            return;
        }

        if (this->first_added == nullptr) {
            this->first_added = current_node;
        }

        if (this->last_added != nullptr) {
            this->last_added->next_added = current_node;
            current_node->prev_added = this->last_added;
        }

        current_node->next_added = nullptr;
        this->last_added = current_node;
    }

public:

    LinkedMap() {
        this->capacity = INITIAL_CAPACITY;
        this->data = new ArrayNode[this->capacity];
        this->first_added = nullptr;
        this->last_added = nullptr;
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
            current_node = new_node;
            this->push_to_order_list(current_node);
        }
        else {
            current_node->value = value;
        }
    }

    void delete_item(Key &key) {
        ListNode *current_node = this->find_node(key);

        if (current_node != nullptr) {
            if (current_node->prev_node != nullptr) {
                current_node->prev_node->next_node = current_node->next_node;
            }

            if (current_node->next_node != nullptr) {
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

        this->pop_from_order_list(current_node);
        delete current_node;
    }

    Value get_item(Key key) {
        ListNode *current_node = this->find_node(key);
        Value *result = nullptr;

        if (current_node != nullptr) {
            result = &current_node->value;
        }

        return (result == nullptr ? this->DEFAULT_RESULT : *result);
    }

    Value get_prev(Key key) {
        ListNode *current_node = this->find_node(key);
        Value result = this->DEFAULT_RESULT;

        if (current_node != nullptr && current_node->prev_added != nullptr) {
            result = current_node->prev_added->value;
        }

        return result;
    }

    Value get_next(Key key) {
        ListNode *current_node = this->find_node(key);
        Value result = this->DEFAULT_RESULT;

        if (current_node != nullptr && current_node->next_added != nullptr) {
            result = current_node->next_added->value;
        }

        return result;
    }

    ~LinkedMap() {
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
    LinkedMap<string, string> map;
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
        else if (cmd == "get") {
            cout << map.get_item(key) << endl;
        }
        else if (cmd == "prev") {
            cout << map.get_prev(key) << endl;
        }
        else if (cmd == "next") {
            cout << map.get_next(key) << endl;
        }
    }
 
    return 0;
}