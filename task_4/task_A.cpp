#include <cstdio>
 
using namespace std;
 
class Stack {
    struct Node
    {
        int value;
        int min_value;
        Node *next_node = nullptr;
    };
    
    Node *head = nullptr;
 
public:
 
    Stack() {}
 
    void push(int value, int current_min) {
        if (this->head == nullptr) {
            this->head = new Node();
            this->head->value = value;
            this->head->min_value = current_min;
        }
        else {
            Node *new_node = new Node();
 
            new_node->next_node = this->head;
            new_node->value = value;
            new_node->min_value = current_min;
            this->head = new_node;
        }
    }
 
    void pop() {
        int value = this->head->value;
        Node *next_node = this->head->next_node;
        delete this->head;
        this->head = next_node;
    }
 
    int top_min() {
        return this->head->min_value;
    }
 
    bool is_empty() {
        return this->head == nullptr ? true : false;
    }
 
    ~Stack() {
        Node *current_node = this->head;
        Node *next_node;
 
        while (current_node != nullptr) {
            next_node = current_node->next_node;
            delete current_node;
            current_node = next_node;
        }
    }
};
 
int main() {
    Stack stack;
    int n;
    int result_ind = 0;
 
    scanf("%d\n", &n);
 
    int *results = new int[n];
 
    for (int i = 0; i < n; i++) {
        int cmd;
 
        scanf("%d", &cmd);
 
        if (cmd == 1) {
            int value;
            int current_min;
 
            scanf(" %d\n", &value);
 
            current_min = stack.is_empty() ? value : stack.top_min();
            current_min = current_min < value ? current_min : value;
            stack.push(value, current_min);
        }
        else if (cmd == 2) {
            stack.pop();
        }
        else {
            results[result_ind++] = stack.top_min();
        }
    }
 
    for (int i = 0; i < result_ind; i++) {
        printf("%d\n", results[i]);
    }
 
    return 0;
}