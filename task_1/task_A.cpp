#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    long input_data[N];
    
    for (int i = 0; i < N; i++) {
        cin >> input_data[i];
    }

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (input_data[i] > input_data[j]) {
                long temp = input_data[i];
                input_data[i] = input_data[j];
                input_data[j] = temp;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << input_data[i] << " ";
    }

    return 0;
}
