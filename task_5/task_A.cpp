#include <iostream>
 
using namespace std;
 
const int COMMAND_LENGTH = 7;
const uint64_t MAX_INPUT_LENGTH = 1e6;
 
template<class Key, class Value>
class Hashtable {
 
    struct Node {
        Value value;
        Key key;
        bool is_empty;
        bool is_deleted;
 
        Node () {
            this->value = Value();
            this->key = Key();
            this->is_empty = true;
            this->is_deleted = false;
        }
    };
 
    const uint64_t INITIAL_CAPACITY = 2e6;
 
    Node *data;
    uint64_t capacity;
    uint64_t size;
    uint64_t empty_count;
 
    uint64_t hash_by_key(Key &key) {
        return (key % this->capacity);
    }
 
    void reshape(uint64_t new_capacity) {
        Node *old_data = this->data;
        uint64_t size = this->size;
        this->empty_count = new_capacity - this->size;
        this->capacity = new_capacity;
        this->data = new Node[new_capacity];
 
        for(uint64_t i = 0; i < size; i++) {
            if (!old_data[i].is_empty && !old_data[i].is_deleted) {
                this->insert_item(old_data[i].key, old_data[i].value);
            }
        }
 
        delete[] old_data;
    }
 
public:
 
    Hashtable() {
        this->capacity = INITIAL_CAPACITY;
        this->size = 0;
        this->empty_count = this->capacity;
        this->data = new Node[this->capacity];
    }
 
    void insert_item(Key &key, Value &value) {
        if (this->empty_count == 0) {
            this->reshape(this->size * 2 + 1);
        }
 
        uint64_t position = this->hash_by_key(key);
 
        while (!this->data[position].is_empty && !this->data[position].is_deleted) {
            if (this->data[position].key == key) {
                return;
            }
            
            position++;
        }
 
        this->data[position].value = value;
        this->data[position].key = key;
        this->data[position].is_empty = false;
        this->data[position].is_deleted = false;
        this->size++;
        this->empty_count--;
    }
 
    void delete_item(Key &key) {
        uint64_t position = this->hash_by_key(key);
 
        while (!this->data[position].is_empty && this->data[position].key != key) {
            if (this->data[position].is_deleted && this->data[position].key == key) {
                return;
            }
 
            position++;
        }
 
        if (!this->data[position].is_empty) {
            this->data[position].is_deleted = true;
            this->data[position].is_empty = false;
            this->size--;
        }
    }
 
    bool exists(Key &key) {
        uint64_t position = this->hash_by_key(key);
 
        while (!this->data[position].is_empty && this->data[position].key != key || 
                this->data[position].is_deleted && this->data[position].key == key) {
            position++;
        }
 
        if (!this->data[position].is_empty && !this->data[position].is_deleted) {
            return true;
        }
        else {
            return false;
        }
    }
 
    uint64_t get_size() {
        return this->size;
    }
 
    ~Hashtable() {
        delete[] this->data;
    }
};
 
template<class Value>
class Set {
    Hashtable<Value, Value> *data;
 
public:
 
    Set() {
        this->data = new Hashtable<Value, Value>();
    }
 
    void insert_item(Value &value) {
        this->data->insert_item(value, value);
    }
 
    void delete_item(Value &value) {
        this->data->delete_item(value);
    }
 
    bool exists(Value &value) {
        return this->data->exists(value);
    }
 
    ~Set() {
        delete data;
    }
};
 
int main() {
    Set<int> set;
    char cmd[COMMAND_LENGTH];
    int value;
    uint64_t res_count = 0;
    bool *result = new bool[MAX_INPUT_LENGTH];
 
    while (scanf("%s %d\n", cmd, &value) != EOF) {
        switch (cmd[0]) {
        case 'i':
            set.insert_item(value);
            break;
        case 'd':
            set.delete_item(value);
            break;
        case 'e':
            result[res_count++] = set.exists(value);
            break;
        default:
            cout << "Something went wrong" << endl;
            return 1;
        }
    }
 
    for (uint64_t i = 0; i < res_count; i++) {
        printf("%s\n", result[i] ? "true" : "false");
    }
 
    return 0;
}