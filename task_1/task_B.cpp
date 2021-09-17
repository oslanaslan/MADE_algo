#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> *merge_sort(vector<int> *data_vec) {
    if (data_vec->size() == 1)
        return data_vec;

    vector<int> *first_part = new vector<int>(data_vec->size() / 2);
    vector<int> *second_part = new vector<int>(data_vec->size() - data_vec->size() / 2);
    vector<int> *sorted_data = new vector<int>();
    copy_n(data_vec->begin(), data_vec->size() / 2, first_part->begin());
    copy_n(data_vec->begin() + data_vec->size() / 2, data_vec->size() - data_vec->size() / 2, second_part->begin());
    first_part = merge_sort(first_part);
    second_part = merge_sort(second_part);
    auto first_part_itr = first_part->begin();
    auto second_part_itr = second_part->begin();

    while (first_part_itr != first_part->end() || second_part_itr != second_part->end()) {
        bool is_second_part_done = second_part_itr == second_part->end();
        bool is_first_and_second_part_done = second_part_itr == second_part->end() || first_part_itr == first_part->end();

        if (is_second_part_done || (!is_first_and_second_part_done && *first_part_itr < *second_part_itr)) {
            sorted_data->push_back(*first_part_itr);
            first_part_itr++;
        }
        else {
            sorted_data->push_back(*second_part_itr);
            second_part_itr++;
        }
    }

    return sorted_data;
}

int main() {
    int n;
    vector<int> *data_vec = new vector<int>();

    cin >> n;

    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        data_vec->push_back(temp);
    }

    data_vec = merge_sort(data_vec);

    for (int i : *data_vec) {
        cout << i << " ";
    }

    return 0;
}
