#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// TODO
const uint64_t M = 786433;
const uint64_t P = 12582917;
const char OFFSET = 'a';

struct HashAndPowp {
    vector<uint64_t> hash;
    vector<uint64_t> powp;

    HashAndPowp() {}
    HashAndPowp(vector<uint64_t> hash, vector<uint64_t> powp) {
        this->hash = hash;
        this->powp = powp;
    }
};

HashAndPowp init_hashes(string& str) {
    HashAndPowp hash_and_powp;

    hash_and_powp.hash.resize(str.size());
    hash_and_powp.powp.resize(str.size());
    hash_and_powp.hash[0] = str[0];
    hash_and_powp.powp[0] = 1;

    for (uint64_t i = 1; i < str.size(); i++) {
        hash_and_powp.hash[i] = (hash_and_powp.hash[i - 1] * P + str[i]) % M;
        hash_and_powp.powp[i] = (hash_and_powp.powp[i - 1] * P) % M;
    }

    return hash_and_powp;
}

uint64_t get_hash(HashAndPowp& hash_and_powp, uint64_t left, uint64_t right) {
    if (left == 0) {
        return hash_and_powp.hash[right];
    }
    return (hash_and_powp.hash[right] -
        (hash_and_powp.hash[left - 1] * hash_and_powp.powp[right - left + 1]) % M + M) % M;
}

bool substring_search(HashAndPowp& hash_and_powp, 
        string& str, uint64_t a1, uint64_t a2, uint64_t b1, uint64_t b2) {
    // TODO
    uint64_t hash_1 = get_hash(hash_and_powp, a1, a2);
    uint64_t hash_2 = get_hash(hash_and_powp, b1, b2);

    if (hash_1 == hash_2) {
        return true;
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    string str;
    int m;
    cin >> str;
    cin >> m;

    for (int i = 0; i < str.size(); i++) {
        str[i] = str[i] - OFFSET + 1;
    }

    HashAndPowp hash_and_powp = init_hashes(str);

    for (int i = 0; i < m; i++) {
        uint64_t a1, a2, b1, b2;

        cin >> a1 >> a2 >> b1 >> b2;
        bool res = substring_search(hash_and_powp, str, a1 - 1, a2 - 1, b1 - 1, b2 - 1);
        cout << (res ? "Yes" : "No") << endl;
    }

    return 0;
}
