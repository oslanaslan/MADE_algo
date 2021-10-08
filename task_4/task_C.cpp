#include <iostream>

using namespace std;

template<class Entity>
class Queue {
    uint64_t size = 0;
    uint64_t capacity = 0;
    Entity *data = nullptr;
    uint64_t head = 0;
    uint64_t tail = 0;

public:

    Queue() {
        this->capacity = 1;
        this->data = new Entity[this->capacity];
    }

    Queue(const Queue &other_array) {
        this->size = other_array.get_size();
        this->capacity = this->size * 2 + 1;
        this->data = new Entity[this->capacity];

        for (uint64_t i = 0; i < this->size; i++) {
            this->data[i] = other_array.data[i];
        }
    }

    uint64_t next(uint64_t &index) {
        return index++ % this->capacity;
    }

    void reshape(uint64_t new_capacity) {
        Entity *new_data = new Entity[new_capacity];

        for (uint64_t i = 0; i < this->size; i++) {
            new_data[i] = this->data[this->next(this->head)];
        }

        this->capacity = new_capacity;
        this->head = 0;
        this->tail = this->size;

        if (this->data != nullptr) {
            delete[] this->data;
        }

        this->data = new_data;
    }

    void push(Entity value) {
        if (this->size >= this->capacity) {
            this->reshape(this->capacity * 2 + 1);
        }

        this->data[this->next(this->tail)] = value;
        this->size++;
    }

    Entity pop() {
        if (this->size == 0) {
            throw out_of_range("Queue index out of range");
        }

        if (this->size - 1 < this->capacity / 4) {
            this->reshape(this->capacity / 2 + 1);
        }

        this->size--;

        return this->data[this->next(this->head)];
    }

    uint64_t get_size() {
        return this->size;
    }

    void print() {
        uint64_t index = this->head;

        while (index < this->size) {
            cout << this->data[this->next(index)] << endl;
        }
    }

    ~Queue() {
        if (this->data != nullptr) {
            delete[] this->data;
        }
    }
};

int main() {
    uint64_t m, value;
    char cmd;
    Queue<int64_t> queue;
    Queue<int64_t> result;

    cin >> m;

    for (uint64_t i = 0; i < m; i++) {
        cin >> cmd;
        
        if (cmd == '+') {
            cin >> value;
            queue.push(value);
        }
        else {
            result.push(queue.pop());
        }
    }

    result.print();

    return 0;
}