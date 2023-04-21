//
// Created by Les on 4/19/2023.
//

#ifndef FINAL_PROJECT_SORTING_H
#define FINAL_PROJECT_SORTING_H
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class Sorting{
public:
    Sorting();
    void mergeSort(vector<int> &data, int start, int end, const map<string, float>& macro);
    void merge(vector<int> &data, int left, int mid, int right, const map<string, float>& macro);

    void testMergeSort();


private:
    json allData;
    map<string, float> proteinData;
    map<string, float> carbData;
    map<string, float> fatData;
    map<int, string> mapper;
    vector<int> indices;
};


#endif //FINAL_PROJECT_SORTING_H
