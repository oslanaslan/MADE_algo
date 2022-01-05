#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

vector<int> z_function(string str) {
    vector<int> z_vec;
    int left = 0;
    int right = 0;

    z_vec.resize(str.size());

    for (int i = 1; i < str.size(); i++) {
        if (i <= right) {
            z_vec[i] = min(right - i + 1, z_vec[i - left]);
        }

        while (i + z_vec[i] < str.size() && str[z_vec[i]] == str[i + z_vec[i]]) {
            z_vec[i]++;
        }

        if (i + z_vec[i] - 1 > right) {
            left = i;
            right = i + z_vec[i] - 1;
        }
    }

    return z_vec;
}

int main() {
    string str;
    cin >> str;

    vector<int> res_vec = z_function(str);

    for (int i = 1; i < res_vec.size(); i++) {
        cout << res_vec[i] << " ";
    }

    return 0;
}
