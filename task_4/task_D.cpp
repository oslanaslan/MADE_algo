#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

uint64_t MAX_POSSIBLE_VALUE = 1e9 + 1;

template<class Entity>
class Heap {
    Entity *data;
    uint64_t size;
    uint64_t capacity;

    uint64_t get_left_node(uint64_t parent) {
        return 2 * parent + 1;
    }

    uint64_t get_right_node(uint64_t parent) {
        return 2 * parent + 2;
    }

    uint64_t get_parent_node(uint64_t child) {
        return (child - 1) / 2;
    } 

    void sift_up(uint64_t node) {
        uint64_t parent_node = get_parent_node(node);

        while (node > 0 && this->data[parent_node] > this->data[node]) {
            swap(this->data[parent_node], this->data[node]);
        }
    }

    void sift_down(uint64_t node) {
        uint64_t left_node = get_left_node(node);
        uint64_t right_node = get_right_node(node);

        while (left_node < this->size) {
            
        }
    }

public:

    Heap(uint64_t n) {
        this->capacity = n;
        this->data = new Entity[this->capacity];
        this->size = 0;
    }

    void insert(Entity value) {
        this->data[this->size++] = value;
        this->sift_up(this->size - 1);
    }

    Entity extract_min() {
        Entity min_element = this->data[0];

        swap(this->data[0], this->data[this->size--]);
        this->sift_down(0);
    }

    bool is_empty() {
        return this->size == 0 ? true : false;
    }
    
    ~Heap() {
        delete[] this->data;
    }
};

int main() {
    

    return 0;
}