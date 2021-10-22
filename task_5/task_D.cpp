#include <iostream>
#include <string>
 
using namespace std;
 
const uint64_t MAX_INPUT_LENGTH = 1e5;
 
template<class Key, class Value>
class LinkedMap {
    
    const uint64_t INITIAL_CAPACITY = 2e6;
    const uint64_t A = 257;
    const uint64_t P = 59969537;
    const uint64_t SHIFT = 'a' - 1;
 
    struct ListNode {
        Key key;
        Value value;
        uint64_t key_hash;
        ListNode *next_node;
        ListNode *prev_node;
        ListNode *next_with_same_key;
        ListNode *prev_with_same_key;
 
        ListNode() {
            this->key = Key();
            this->value = Value();
            this->key_hash = 0;
            this->next_node = nullptr;
            this->prev_node = nullptr;
            this->next_with_same_key = nullptr;
            this->prev_with_same_key = nullptr;
        }
 
        ListNode(Key &key, Value &value) {
            this->key = key;
            this->value = value;
            this->next_node = nullptr;
            this->prev_node = nullptr;
            this->next_with_same_key = nullptr;
            this->prev_with_same_key = nullptr;
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
 
    ListNode *find_node(Key &key, Value &value) {
        uint64_t position = this->hash_by_key(key);
        ListNode *current_node = this->data[position].head;

        while (current_node != nullptr && current_node->key != key) {
            current_node = current_node->next_node;
        }
 
        while (current_node != nullptr && current_node->value != value) {
            current_node = current_node->next_with_same_key;
        }
 
        return current_node;
    }
 
    void delete_node(ListNode *current_node) {
        if (current_node->prev_node != nullptr) {
            current_node->prev_node->next_node = current_node->next_node;
        }
        
        if (current_node->next_node != nullptr) {
            current_node->next_node->prev_node = current_node->prev_node;
        }

        if (current_node->prev_with_same_key != nullptr) {
            current_node->prev_with_same_key->next_with_same_key = current_node->next_with_same_key;
        }

        if (current_node->next_with_same_key != nullptr) {
            current_node->next_with_same_key->prev_with_same_key = current_node->prev_with_same_key;
        }
 
        uint64_t position = current_node->key_hash;
 
        if (current_node->prev_node == nullptr) {
            this->data[position].head = current_node->next_node;
        }
 
        if (current_node->next_node == nullptr) {
            this->data[position].tail = current_node->prev_node;
        }
 
        if (current_node != nullptr) {
            delete current_node;
        }
    }
 
public:
 
    LinkedMap() {
        this->capacity = INITIAL_CAPACITY;
        this->data = new ArrayNode[this->capacity];
    }
 
    void put_item(Key key, Value value) {
        ListNode *current_node = this->find_node(key);

        while (current_node != nullptr && current_node->next_with_same_key != nullptr) {
            if (current_node->value == value) {
                return;
            }

            current_node = current_node->next_with_same_key;
        }
 
        if (current_node == nullptr || current_node->value != value) {
            uint64_t position = this->hash_by_key(key);
            ListNode *new_node = new ListNode(key, value);
 
            if (this->data[position].tail != nullptr) {
                this->data[position].tail->next_node = new_node;
            }
            else {
                this->data[position].head = new_node;
            }
 
            new_node->prev_node = this->data[position].tail;
            new_node->key_hash = position;
            this->data[position].tail = new_node;

            if (current_node != nullptr && current_node->value != value) {
                current_node->next_with_same_key = new_node;
                new_node->prev_with_same_key = current_node;
            }
        }
    }
 
    void delete_item(Key &key, Value &value) {
        ListNode *current_node = this->find_node(key, value);
 
        if (current_node != nullptr) {
            this->delete_node(current_node);
        }
    }
 
    void delete_all(Key &key) {
        ListNode *current_node = this->find_node(key);
 
        while (current_node != nullptr) {
            ListNode *next_node = current_node->next_with_same_key;
            this->delete_node(current_node);
            current_node = next_node;
        }
    }
 
    void get_items(Key key, uint64_t *res_count, Value *res_data) {
        ListNode *current_node = this->find_node(key);
        *res_count = 0;
 
        while (current_node != nullptr) {
            res_data[(*res_count)++] = current_node->value;
            current_node = current_node->next_with_same_key;
        }
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
    string *res_data = new string[MAX_INPUT_LENGTH];
 
    while (cin >> cmd >> key) {
        if (cmd == "put") {
            cin >> value;
            map.put_item(key, value);
        }
        else if (cmd == "delete") {
            cin >> value;
            map.delete_item(key, value);
        }
        else if (cmd == "get") {
            map.get_items(key, &res_count, res_data);
 
            cout << res_count;
 
            for (uint64_t i = 0; i < res_count; i++) {
                cout << " " << res_data[i];
            }
            
            cout << endl;
        }
        else if (cmd == "deleteall") {
            map.delete_all(key);
        }
    }
 
    delete[] res_data;
 
    return 0;
}