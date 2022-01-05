#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;

const uint64_t M = 786433;
const uint64_t P = 12582917;
const char OFFSET = 'a';
const int MAX_LEN = 1e5;

struct MyDataStruct {
    uint64_t hash;
    int start;
    int end;

    MyDataStruct() {
        this->hash = 0;
        this->start = 0;
        this->end = 0;
    }

    MyDataStruct(uint64_t hash, int start, int end) {
        this->hash = hash;
        this->start = start;
        this->end = end;
    }
};

class MyString {

public:

    struct HashAndPowp {
        vector<uint64_t> hash;
        vector<uint64_t> powp;

        HashAndPowp() {}
        HashAndPowp(vector<uint64_t> hash, vector<uint64_t> powp) {
            this->hash = hash;
            this->powp = powp;
        }
    };

    struct HashStruct {
        uint64_t hash;
        int i;
        int j;

        HashStruct() {
            this->hash = 0;
            this->i = 0;
            this->j = 0;
        }

        HashStruct(uint64_t hash, int i, int j) {
            this->hash = hash;
            this->i = i;
            this->j = j;
        }
    };

    string str;
    HashAndPowp hash_and_powp;

    MyString(string& str) {
        this->str = str;
        this->hash_and_powp.hash.resize(str.size());
        this->hash_and_powp.powp.resize(str.size());
        this->hash_and_powp.hash[0] = str[0];
        this->hash_and_powp.powp[0] = 1;

        for (uint64_t i = 1; i < str.size(); i++) {
            this->hash_and_powp.hash[i] = (this->hash_and_powp.hash[i - 1] * P + str[i]) % M;
            this->hash_and_powp.powp[i] = (this->hash_and_powp.powp[i - 1] * P) % M;
        }
    }

    uint64_t get_hash(uint64_t left, uint64_t right) {
        if (left == 0) {
            return this->hash_and_powp.hash[right];
        }
        return (this->hash_and_powp.hash[right] -
            (this->hash_and_powp.hash[left - 1] * this->hash_and_powp.powp[right - left + 1]) % M + M) % M;
    }
};

int main() {
    vector<MyString> input_strings;
    int input_count;
    int min_substring_len = MAX_LEN;
    cin >> input_count;

    for (int i = 0; i < input_count; i++) {
        string str;

        cin >> str;
        input_strings.push_back(MyString(str));

        if (str.size() < min_substring_len) {
            min_substring_len = str.size();
        }
    }

    for (int window_len = min_substring_len; window_len > 0; window_len--) {
        vector<MyDataStruct> current_hashes;

        for (int i = 0; i < input_strings[0].str.size() - window_len + 1; i++) {
            current_hashes.push_back(
                MyDataStruct(
                    input_strings[0].get_hash(i, i + window_len),
                    i,
                    i + window_len
                )
            );
        }

        cout << current_hashes.size() << endl;

        for (int i = 1; i < input_count; i++) {
            for (int j = 0; j < input_strings[i].str.size() - window_len + 1; j++) {
                uint64_t current_hash = input_strings[i].get_hash(j, j + window_len);
                vector<MyDataStruct> new_current_hashes;

                for (MyDataStruct current_data : current_hashes) {
                    if (current_data.hash == current_hash) {
                        new_current_hashes.push_back(current_data);
                    }
                }
                current_hashes = new_current_hashes;
                if (new_current_hashes.size() == 0) {
                    break;
                }
            }
            if (current_hashes.size() == 0) {
                break;
            }
        }
        if (current_hashes.size() != 0) {
            int start = current_hashes[0].start;
            int end = current_hashes[0].end;

            for (int i = start; i < end; i++) {
                cout << input_strings[0].str[i];
            }
            cout << endl;

            return 0;
        }
    }



    return 0;
}