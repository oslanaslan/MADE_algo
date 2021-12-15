#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

vector<int> create_prefix_function(string& str) {
    vector<int> prefix(str.size());
    prefix[0] = 0;

    for (int i = 1; i < str.size(); i++) {
        int k = prefix[i - 1];

        while (k > 0 && str[i] != str[k]) {
            k = prefix[k - 1];
        }

        if (str[i] == str[k]) {
            k++;
        }
        
        prefix[i] = k;
    }

    return prefix;
}

vector<int> kmp(vector<int>& prefix, int str_1_len, int str_2_len) {
    vector<int> res;

    for (int i = 0; i < str_2_len; i++) {
        if (prefix[str_1_len + 1 + i] == str_1_len) {
            res.push_back(i - str_1_len + 2);
        }
    }

    return res;
}

int main() {
    string str_1, str_2;
    
    cin >> str_1;
    cin >> str_2;

    string str = str_1 + "#" + str_2;
    vector<int> prefix = create_prefix_function(str);
    int target = str_1.size();
    vector<int> res = kmp(prefix, str_1.size(), str_2.size());

    cout << res.size() << endl;
    for (int i : res) {
        cout << i << " ";
    }

    return 0;
}