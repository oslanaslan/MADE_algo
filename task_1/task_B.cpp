#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<long> *merge_sort(vector<long> *data_vec) {
    if (data_vec->size() == 1)
        return data_vec;

    vector<long> *first_part = new vector<long>(data_vec->size() / 2);
    vector<long> *second_part = new vector<long>(data_vec->size() - data_vec->size() / 2);
    vector<long> *sorted_data = new vector<long>();
    copy_n(data_vec->begin(), data_vec->size() / 2, first_part->begin());
    copy_n(data_vec->begin() + data_vec->size() / 2, data_vec->size() - data_vec->size() / 2, second_part->begin());
    first_part = merge_sort(first_part);
    second_part = merge_sort(second_part);
    auto first_part_itr = first_part->begin();
    auto second_part_itr = second_part->begin();

    while (first_part_itr != first_part->end() && second_part_itr != second_part->end()) {
        if (*first_part_itr < *second_part_itr) {
            sorted_data->push_back(*first_part_itr);
            first_part_itr++;
        }
        else {
            sorted_data->push_back(*second_part_itr);
            second_part_itr++;
        }
    }
    while (first_part_itr != first_part->end()) {
        sorted_data->push_back(*first_part_itr);
        first_part_itr++;
    }
    while (second_part_itr != second_part->end()) {
        sorted_data->push_back(*second_part_itr);
        second_part_itr++;
    }

    return sorted_data;
}


int main() {
    int N;
    vector<long> *data_vec = new vector<long>();

    cin >> N;

    for (int i = 0; i < N; i++) {
        long temp;
        cin >> temp;
        data_vec->push_back(temp);
    }

    data_vec = merge_sort(data_vec);

    for (long i : *data_vec) {
        cout << i << " ";
    }

    return 0;
}
