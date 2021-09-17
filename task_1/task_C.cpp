#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
 
using namespace std;
 
struct MergeSortResult {
    vector<int> *sorted_data;
    unsigned long long inv_count;
};

MergeSortResult merge_sort(vector<int> *data_vec) {
    if (data_vec->size() == 1) {
        MergeSortResult result;
        result.sorted_data = data_vec;
        result.inv_count = 0;
        return result;
    }
 
    vector<int> *first_part = new vector<int>(data_vec->size() / 2);
    vector<int> *second_part = new vector<int>(data_vec->size() - data_vec->size() / 2);
    vector<int> *sorted_data = new vector<int>();
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
    unsigned long long inv_count = first_part_result.inv_count + second_part_result.inv_count;
 
    while (first_part_itr != first_part->end() || second_part_itr != second_part->end()) {
        bool is_second_part_done = second_part_itr == second_part->end();
        bool is_first_and_second_part_done = second_part_itr == second_part->end() || first_part_itr == first_part->end();

        if (!is_first_and_second_part_done && *second_part_itr < *first_part_itr) {
            inv_count += first_part->end() - first_part_itr;
        }

        if (is_second_part_done || (!is_first_and_second_part_done && *first_part_itr < *second_part_itr)) {
            sorted_data->push_back(*first_part_itr);
            first_part_itr++;
        }
        else {
            sorted_data->push_back(*second_part_itr);
            second_part_itr++;
        }
    }
 
    result.sorted_data = sorted_data;
    result.inv_count = inv_count;

    return result;
}

int main() {
    int n;
    vector<int> *data_vec = new vector<int>();
    MergeSortResult sorted_result;
 
    cin >> n;

    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        data_vec->push_back(temp);
    }
 
    sorted_result = merge_sort(data_vec);
    cout << sorted_result.inv_count;

    return 0;
}
