//
// Created by Les on 4/19/2023.
//
#include "Sorting.h"

Sorting::Sorting()
{
    // Initialize data. Each map contains the food name, and it's relevant macro
    // Mapper contains the index value for a description. We sort a vector of index values based on macro value
    ifstream file("./food.json");
    json temp = json::parse(file);
    int i = 0;
    for (auto& entry : temp)
    {
        string description = entry["Description"];
        allData[description] = entry;
        proteinData[description] = entry["Data"]["Protein"];
        carbData[description] = entry["Data"]["Carbohydrate"];
        fatData[description] = entry["Data"]["Fat"]["Total Lipid"];
        mapper[i] = description;
        indices.push_back(i);
        i++;
    }
}

void Sorting::mergeSort(vector<int> &data, int start, int end, const map<string, float>& macro)
{
    if (start < end)
    {
        int middle = (start+end)/2;
        mergeSort(data, start, middle, macro);
        mergeSort(data, middle + 1, end, macro);

        merge(data, start,  middle, end, macro);
    }
}

void Sorting::merge(vector<int> &data, int start, int middle, int end, const map<string, float>& macro)
{
    // Split into sub-arrays [start : middle] and [middle + 1 : end]
    vector<int> leftPortion;
    vector<int> rightPortion;

    for (int i = start; i <= middle; i++)
        leftPortion.emplace_back(data[i]);

    for (int i = middle + 1; i <= end; i++)
        rightPortion.emplace_back(data[i]);

    // While both portions are not empty, pick the smallest value to add to final container
    int mergedIdx = start;
    while (!leftPortion.empty() && !rightPortion.empty())
    {
        // Grab macro value from food:
        // 1. Data contains a food id. Use the mapper to determine the food name.
        // 2. Use the food name to get the food's macro value. Use this for comparison
        // 3. Delete the front of the relevant portion
        string leftMacro = mapper[leftPortion[0]];
        string rightMacro = mapper[rightPortion[0]];
        float leftMacroVal = macro.at(leftMacro);
        float rightMacroVal = macro.at(rightMacro);

        if (leftMacroVal > rightMacroVal)
        {
            data[mergedIdx++] = leftPortion[0];
            leftPortion.erase(leftPortion.begin());
        }
        else
        {
            data[mergedIdx++] = rightPortion[0];
            rightPortion.erase(rightPortion.begin());
        }
    }
    // Now one portion is empty. Add all the non-empty portion to data
    while (!leftPortion.empty())
    {
        data[mergedIdx++] = leftPortion[0];
        leftPortion.erase(leftPortion.begin());
    }
    while (!rightPortion.empty())
    {
        data[mergedIdx++] = rightPortion[0];
        rightPortion.erase(rightPortion.begin());
    }
}

void Sorting::testMergeSort()
{
    vector<int> testVec = indices;
    vector<int> carbVec = indices;
    vector<int> fatVec = indices;
//    testVec.assign(indices.begin(), indices.begin()+8);
    mergeSort(testVec, 0, testVec.size()-1, proteinData);
    mergeSort(carbVec, 0, carbVec.size()-1, carbData);
    mergeSort(fatVec, 0, fatVec.size()-1, fatData);
    for (int i = 0; i < 50; i++)
    {
//        string food = mapper[testVec[i]];
//        cout << food << ": " << proteinData[food] << endl;
//        string food = mapper[carbVec[i]];
//        cout << food << ": " << carbData[food] << endl;
        string food = mapper[fatVec[i]];
        cout << food << "; " << fatData[food] << endl;
    }
}
int Sorting::getMax(vector<int> &data, int size, const map<string, float>& macro)    {
    int maxIndex = 0; 
    float max = FLOAT_MIN; 
    for (int i = 0; i < size; i++)    {
        string name = mapper[arr[i]];
        if (macro.at(name) > max)    {
            maxIndex = i; 
            max = macro.at(name); 
        }
    }
    return maxIndex; 
}
void Sorting::pancakeFlip(vector<int> &data, int size)   {

    for (int i = 0; i < n; i++)    {
        swap(arr[i], arr[n-i]); 
    }
}
void Sorting::pancakeSort(vector<int> &data, int size, const map<string, float>& macro)    {
    int n = size; 
    while (n > 1)    {
        int maxIndex = getMax(arr, n);
        pancakeFlip(arr, maxIndex);
        pancakeFlip(arr, n - 1); 
        n--; 
    }
}
void Sorting::testPancakeSort()
{
    vector<int> carbVec = indices;
    pancakeSort(carbVec, carbVec.size()-1, carbData);
    for (int i = 0; i < 50; i++)
    {
//        string food = mapper[testVec[i]];
//        cout << food << ": " << proteinData[food] << endl;
//        string food = mapper[carbVec[i]];
//        cout << food << ": " << carbData[food] << endl;
        string food = mapper[carbVec[i]];
        cout << food << "; " << carbData[food] << endl;
    }
}