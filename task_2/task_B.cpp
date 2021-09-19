#include <iostream>

using namespace std;

int MAX_ELEMENT_RANGE = 100;

int main() {
    int n;
    int count_of_elements[MAX_ELEMENT_RANGE];

    cin >> n;

    for (int i = 0; i < n; i++) {
        int value;

        cin >> value;
        count_of_elements[value] += 1;
    }

    for (int i = 0; i < MAX_ELEMENT_RANGE; i++) {
        for (int j = 0; j < count_of_elements[i]; j++) {
            cout << i << " ";
        }
    }

    return 0;
}