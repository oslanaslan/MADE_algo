#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

template<class Entity>
class Array {

    uint64_t size = 0;
    uint16_t capacity = 1;
    Entity *data = nullptr;

public:

    Array(uint64_t size = 0) {
        this->capacity = 2 * size + 1;
        this->size = size;
        this->data = new Entity[capacity];
    }

    Array(const Array &other_array) {
        this->size = other_array.size;
        this->capacity = other_array.capacity;
        this->data = new Entity[this->capacity];

        for (uint64_t i = 0; i < this->size; i++) {
            this->data[i] = other_array.data[i];
        }
    }

    uint64_t get_size() {
        return this->size;
    }

    Entity operator[](uint64_t index) {
        if (index >= this->size) {
            throw out_of_range("Array index out of range");
        }

        return this->data[index];
    }

    void insert(uint64_t index, Entity value) {
        if (index > this->size) {
            throw out_of_range("Array index out of range");
        }

        this->size++;
        
        if (this->size >= this->capacity) {
            this->capacity = this->capacity * 2 + 1;
        }

        Entity *new_data = new Entity[this->capacity];
        uint64_t copy_index = 0;

        while (copy_index < index) {
            new_data[copy_index] = this->data[copy_index];
            copy_index++;
        }

        new_data[copy_index++] = value;

        while (copy_index < this->size) {
            new_data[copy_index] = this->data[copy_index - 1];
            copy_index++;
        }

        if (this->data != nullptr) {
            delete[] this->data;
        }

        this->data = new_data;
    }

    void append(Entity value) {
        this->insert(this->size, value);
    }

    Entity pop(uint64_t index) {
        if (index >= this->size) {
            throw out_of_range("Array index out of range");
        }

        this->size--;

        if (this->size < this->capacity / 4) {
            this->capacity = this->capacity / 2 + 1;
        }

        Entity value;
        Entity *new_data = new Entity[this->capacity];
        uint64_t copy_index = 0;

        while (copy_index < index) {
            new_data[copy_index] = this->data[copy_index];
            copy_index++;
        }

        value = data[copy_index++];
        
        while (copy_index < this->size) {
            new_data[copy_index - 1] = this->data[copy_index];
            copy_index++;
        }

        delete[] this->data;
        this->data = new_data;

        return value;
    }

    Entity pop_last() {
        return this->pop(this->size - 1);
    }

    void remove(uint64_t index) {
        this->pop(index);
    }

    Entity get_last() {
        return this->data[this->size - 1];
    }

    ~Array() {
        delete[] this->data;
    }
};

template<class Entity>
class Stack {
    Array<Entity> *data = nullptr;

public:

    Stack() {
        this->data = new Array<Entity>();
    }

    Stack(const Stack &other_stack) {
        this->data = new Array<Entity>(*other_stack.data);
    }

    uint64_t size() {
        return this->data->get_size();
    }

    void add(Entity value) {
        this->data->append(value);
    }

    Entity pop() {
        return this->data->pop_last();
    }

    Entity top() {
        return this->data->get_last();
    }

    ~Stack() {
        if (this->data != nullptr) {
            delete this->data;
        }
    }
};

int main() {
    Stack<int64_t> stack;
    Array<string> input_data;
    string input_str;

    while (cin >> input_str) {
        input_data.append(input_str);
    }

    for (uint64_t i = 0; i < input_data.get_size(); i++) {
        input_str = input_data[i];

        if (input_str.compare("+") == 0) {
            int64_t first_value = stack.pop();
            int64_t second_value = stack.pop();

            stack.add(first_value + second_value);
        }
        else if (input_str.compare("-") == 0) {
            int64_t first_value = stack.pop();
            int64_t second_value = stack.pop();

            stack.add(second_value - first_value);
        }
        else if (input_str.compare("*") == 0) {
            int64_t first_value = stack.pop();
            int64_t second_value = stack.pop();

            stack.add(second_value * first_value);
        }
        else {
            int value;

            sscanf(input_str.c_str(), "%d", &value);
            stack.add(value);
        }
    }

    cout << stack.pop() << endl;

    return 0;
}