#include <iostream>
#include <utility>
#include <cstdio>
#include <inttypes.h>

using namespace std;

template<class Entity>
class Stack {
    struct Node
    {
        Entity value;
        Node *next_node = nullptr;
    };
    
    Node *head = nullptr;

public:

    Stack() {}

    void push(Entity value) {
        if (this->head == nullptr) {
            this->head = new Node();
            this->head->value = value;
        }
        else {
            Node *new_node = new Node();

            new_node->next_node = this->head;
            new_node->value = value;
            this->head = new_node;
        }
    }

    Entity pop() {
        Entity value = this->head->value;
        Node *next_node = this->head->next_node;
        // delete this->head;
        this->head = next_node;

        return value;
    }

    Entity top() {
        return this->head->value;
    }

    bool is_empty() {
        return this->head == nullptr ? true : false;
    }

    // ~Stack() {
    //     Node *current_node = this->head;
    //     Node *next_node;

    //     while (current_node != nullptr) {
    //         next_node = current_node->next_node;
    //         // delete current_node;
    //         current_node = next_node;
    //     }
    // }
};

int main() {
    Stack<pair<int64_t, int64_t>> stack;
    int n;
    int result_ind = 0;

    scanf("%d\n", &n);

    int64_t results[n];

    for (int i = 0; i < n; i++) {
        int cmd;

        scanf("%d", &cmd);

        if (cmd == 1) {
            int64_t value;

            scanf(" %" SCNd64 "\n", &value);

            int64_t current_min = stack.is_empty() ? value : stack.top().second;
            current_min = current_min < value ? current_min : value;
            stack.push(make_pair(value, current_min));
        }
        else if (cmd == 2) {
            stack.pop();
        }
        else {
            results[result_ind++] = stack.top().second;
        }
    }

    for (int i = 0; i < result_ind; i++) {
        printf("%" SCNd64 "\n", results[i]);
    }

    return 0;
}