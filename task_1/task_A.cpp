#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int input_data[n];
    
    for (int i = 0; i < n; i++) {
        cin >> input_data[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (input_data[i] > input_data[j]) {
                swap(input_data[i], input_data[j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << input_data[i] << " ";
    }

    return 0;
}
