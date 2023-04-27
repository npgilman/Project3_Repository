//
// Created by Les on 4/19/2023.
//

#ifndef FINAL_PROJECT_SORTING_H
#define FINAL_PROJECT_SORTING_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class Sorting{
public:
    Sorting();
    void mergeSort(vector<int> &data, int start, int end, const map<string, float>& macro);
    void merge(vector<int> &data, int left, int mid, int right, const map<string, float>& macro);
    double pancakeSort(vector<int> &data, int size, const map<string, float>& macro); 
    void testPancakeSort();
    void testMergeSort();

    json calculateFoods(bool algorithm, float protein, float carb, float fat);

private:
    json allData;
    json results;
    map<string, float> proteinData;
    map<string, float> carbData;
    map<string, float> fatData;
    map<int, string> mapper;
    vector<int> indices;
    vector<int> carbIdx;
    vector<int> fatIdx;
    vector<int> proteinIdx;

    void pancakeFlip(vector<int> &data, int size); 
    int getMin(vector<int> &data, int size, const map<string, float>& macro);
    vector<int> chooseFoods(float protein, float carb, float fat);
    int choose(vector<int> &macroIdx, map<string, float> &macroData, float &macro);
    json createFoodJSON(const vector<int>& foods);
};


#endif //FINAL_PROJECT_SORTING_H
