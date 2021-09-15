#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>

using namespace std;

struct MergeSortResult {
    vector<long> *sorted_data;
    int inv_count;
};


MergeSortResult merge_sort(vector<long> *data_vec) {
    if (data_vec->size() == 1) {
        MergeSortResult result;
        result.sorted_data = data_vec;
        result.inv_count = 0;
        return result;
    }

    vector<long> *first_part = new vector<long>(data_vec->size() / 2);
    vector<long> *second_part = new vector<long>(data_vec->size() - data_vec->size() / 2);
    vector<long> *sorted_data = new vector<long>();
    MergeSortResult first_part_result;
    MergeSortResult second_part_result;
    MergeSortResult result;
    copy_n(data_vec->begin(), data_vec->size() / 2, first_part->begin());
    copy_n(data_vec->begin() + data_vec->size() / 2, data_vec->size() - data_vec->size() / 2, second_part->begin());
    first_part_result = merge_sort(first_part);
    second_part_result = merge_sort(second_part);
    first_part = first_part_result.sorted_data;
    second_part = second_part_result.sorted_data;
    auto first_part_itr = first_part->begin();
    auto second_part_itr = second_part->begin();
    int inv_count = first_part_result.inv_count + second_part_result.inv_count;

    while (first_part_itr != first_part->end() && second_part_itr != second_part->end()) {
        if (*first_part_itr <= *second_part_itr) {
            sorted_data->push_back(*first_part_itr);
            first_part_itr++;
        }
        else {
            sorted_data->push_back(*second_part_itr);
            second_part_itr++;
            inv_count += first_part->end() - first_part_itr;
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

    result.sorted_data = sorted_data;
    result.inv_count = inv_count;
    return result;
}


int inv_count_with_merge(vector<long> *data_vec) {
    MergeSortResult sorted_result;

    sorted_result = merge_sort(data_vec);
    return sorted_result.inv_count;
}


int inv_count_stright(vector<long> *data_vec) {
    int inv_count = 0;

    for (int i = 0; i < data_vec->size(); i++) {
        for (int j = i+1; j < data_vec->size(); j++) {
            if ((*data_vec)[i] > (*data_vec)[j])
                inv_count++;
        }
    }

    return inv_count;
}


int main() {
    long loop_count = 10000;

    for (long i = 0; i < loop_count; i++) {
        // int N = rand() % 1000 + 1;
        int N = 1000;
        vector<long> *data_vec = new vector<long>();

        // long current = i;
        // for (long g = loop_count / 10; g > 0; g /= 10) {
        //     data_vec->push_back(current / g);
        //     current %= g;
        // }

        for (int j = 0; j < N; j++) {
            data_vec->push_back(rand() % 100);
        }
        

        int inv_count_1 = inv_count_with_merge(data_vec);
        int inv_count_2 = inv_count_stright(data_vec);
        if (inv_count_1 != inv_count_2) {
            for (long j : *data_vec)
                cout << j << " ";
            cout << endl << inv_count_1 << endl << inv_count_2 << endl;
        }

        delete data_vec;
    }
}