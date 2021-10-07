#include <iostream>
#include <utility>

using namespace std;

template<class Entity>
class List {

    struct Node {
        Entity value = Entity();
        Node *next_node = nullptr;
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    int size = 0;

public:

    List(int size = 0) {
        for (int i = 0; i < size; i++) {
            push_back(Entity());
        }
    }

    List(const List &other_list) {
        Node *current_node = other_list.head;

        for (int i = 0; i < other_list.size; i++) {
            this->push_back(current_node->value);
            current_node = current_node->next_node;
        }
    }

    Node *get_node_by_index(int index) {
        if (index < 0 || size >= this->size) {
            throw out_of_range("List index out of range");
        }

        Node *current_node = this->head;

        for (int i = 0; i < index; i++) {
            current_node = current_node->next_node;
        }

        return current_node;
    }

    void push_back(Entity value) {
        Node *current_node = this->tail;

        this->tail = new Node();
        this->tail->value = value;

        if (current_node != nullptr) {
            current_node->next_node = this->tail;
        }
        else {
            this->head = this->tail;
        }

        this->size++;
    }

    void push_start(Entity value) {
        Node *current_node = this->head;

        this->head = new Node();
        this->head->value = value;
        this->head->next_node = current_node;
        this->size++;
    }

    Entity get_first() {
        return this->head->value;
    }

    Entity get_last() {
        return this->tail->value;
    }

    Entity pop_first() {
        if (this->size > 0) {
            Node *first_node = this->head;
            Entity first_value = first_node->value;

            this->head = this->head->next_node;
            this->size--;
            delete first_node;

            return first_value;
        }

        throw out_of_range("List is empty");
    }

    Entity pop_last() {
        if (this->size > 0) {
            Node *last_node = this->tail;
            Entity last_value = last_node->value;

            this->tail = get_node_by_index(this->size - 2);
            this->tail->next_node = nullptr;
            this->size--;
            delete last_node;

            return last_value;
        }

        throw out_of_range("List is empty");
    }

    Entity operator[](int index) {
        Node *target_node = get_node_by_index(index);

        return target_node->value;
    }

    int get_size() {
        return this->size;
    }

    Entity find_min() {
        if (this->size == 0) {
            throw out_of_range("List is empty");
        }

        Node *current_node = this->head;
        Entity min_element = current_node->value;

        current_node = current_node->next_node;

        while (current_node != nullptr) {
            if (current_node->value < min_element) {
                min_element = current_node->value;
            }

            current_node = current_node->next_node;
        }

        return min_element;
    }

    void print() {
        Node *current_node = this->head;

        while (current_node != nullptr) {
            cout << current_node->value << endl;
            current_node = current_node->next_node;
        }
    }

    ~List() {
        Node *current_node = this->head;

        while (current_node != nullptr) {
            Node *next_node = current_node->next_node;

            delete current_node;
            current_node = next_node;
        }
    }
};

class Stack {
    List<int> *data = nullptr;

public:

    Stack() {
        this->data = new List<int>();
    }

    void add(int value) {
        if (this->data == nullptr) {
            this->data = new List<int>();
        }

        this->data->push_start(value);
    }

    int pop() {
        if (this->data == nullptr) {
            throw out_of_range("Stack is empty");
        }

        return this->data->pop_first();
    }

    int size() const {
        if (this->data == nullptr) {
            return 0;
        }
        else {
            return this->data->get_size();
        }
    }

    int top() {
        if (this->data == nullptr) {
            throw out_of_range("Stack is empty");
        }

        return this->data->get_first();
    }

    int bottom() {
        if (this->data == nullptr) {
            throw out_of_range("Stack is empty");
        }

        return this->data->get_last();
    }

    bool is_empty() const {
        if (this->data == nullptr || this->data->get_size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    int find_min() {
        return this->data->find_min();
    }

    void print() {
        if (this->data != nullptr) {
            this->data->print();
        }
    }

    ~Stack() {
        delete this->data;
    }
};

int main() {
    Stack stack;
    int n;
    pair<int, int> input_data[n] = {make_pair(0, 0)};
    int results[n];
    int result_ind = 0;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> input_data[i].first;

        if (input_data[i].first == 1) {
            cin >> input_data[i].second;
        }
    }

    for (int i = 0; i < n; i++) {
        pair<int, int> cmd = input_data[i];

        if (cmd.first == 1) {
            int value;

            stack.add(cmd.second);
        }
        else if (cmd.first == 2) {
            stack.pop();
        }
        else {
            int min_value = stack.find_min();

            results[result_ind++] = min_value;
        }
    }

    for (int i = 0; i < result_ind; i++) {
        cout << results[i] << endl;
    }

    return 0;
}