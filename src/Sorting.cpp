#pragma once
#include "Sorting.h"
#include <chrono>

typedef chrono::high_resolution_clock Clock;

// Constructor for Sorting Class
Sorting::Sorting()
{
    // Initialize data. Each map contains the food name, and it's relevant macro
    // Mapper contains the index value for a description. We sort a vector of index values based on macro value
    ifstream file("../assets/dataset/food.json");
    json temp = json::parse(file);
    int i = 0;
    for (auto &entry : temp)
    {
        string description = entry["Description"];
        allData[description] = entry;
        allData[description]["Category"] = entry["Category"];
        proteinData[description] = entry["Data"]["Protein"];
        carbData[description] = entry["Data"]["Carbohydrate"];
        fatData[description] = entry["Data"]["Fat"]["Total Lipid"];
        mapper[i] = description;
        indices.push_back(i);
        i++;
    }
}

/// @brief Recursive sorting algorithm
/// @param data Data to sort
/// @param start Start index of data
/// @param end End index of data
/// @param macro Macro to sort by
void Sorting::mergeSort(vector<int> &data, int start, int end, const map<string, float> &macro)
{
    if (start < end)
    {
        int middle = (start + end) / 2;
        mergeSort(data, start, middle, macro);
        mergeSort(data, middle + 1, end, macro);

        merge(data, start, middle, end, macro);
    }
}

/// @brief Implementation of the merge sort algorithm
/// @param data The given data to sort
/// @param start Index to start at
/// @param middle Index of the middle
/// @param end Index to end at
/// @param macro The macro being sorted
void Sorting::merge(vector<int> &data, int start, int middle, int end, const map<string, float> &macro)
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

/// @brief Unit test for merge sort
void Sorting::testMergeSort()
{
    vector<int> testVec = indices;
    vector<int> carbVec = indices;
    vector<int> fatVec = indices;
    mergeSort(testVec, 0, testVec.size() - 1, proteinData);
    mergeSort(carbVec, 0, carbVec.size() - 1, carbData);
    mergeSort(fatVec, 0, fatVec.size() - 1, fatData);
    for (int i = 50; i < 100; i++)
    {
        string food = mapper[carbVec[i]];
        cout << food << ": " << carbData[food] << endl;
    }
    string food = mapper[fatVec[8]];
    cout << allData[food];
}

/// @brief Helper function to get the minimum
/// @param data Given data to search through
/// @param size Size of the data
/// @param macro The macro specified
/// @return The index of the lowest macro found
int Sorting::getMin(vector<int> &data, int size, const map<string, float> &macro)
{

    int maxIndex = 0;
    float max = INT_MAX;
    for (int i = 0; i < size; i++)
    {
        string name = mapper[data[i]];
        if (macro.at(name) < max)
        {
            maxIndex = i;
            max = macro.at(name);
        }
    }
    return maxIndex;
}

/// @brief Helper function for the pancake sort algorithm
/// @param data Given data to sort
/// @param size The size of the data
void Sorting::pancakeFlip(vector<int> &data, int size)
{
    for (int i = 0; i < size; i++)
        swap(data[i], data[size - i]);
}

/// @brief Implementation of the pancake sort algorithm
/// @param data
/// @param size The specified size of the data
/// @param macro The macro the algorithm is sorting by
/// @return The time in milliseconds that the sort takes
double Sorting::pancakeSort(vector<int> &data, int size, const map<string, float> &macro)
{
    auto t1 = Clock::now();
    int n = size;
    while (n > 1)
    {
        int maxIndex = getMin(data, n, macro);
        pancakeFlip(data, maxIndex);
        pancakeFlip(data, n - 1);
        n--;
    }
    auto t2 = Clock::now();
    return std::chrono::duration<double, std::milli>(t2 - t1).count();
}

/// @brief Unit test for pancake sort
void Sorting::testPancakeSort()
{
    vector<int> carbVec = indices;
    pancakeSort(carbVec, carbVec.size() - 1, carbData);
    for (int i = 50; i < 100; i++)
    {
        //        string food = mapper[testVec[i]];
        //        cout << food << ": " << proteinData[food] << endl;
        //        string food = mapper[carbVec[i]];
        //        cout << food << ": " << carbData[food] << endl;
        string food = mapper[carbVec[i]];
        cout << food << "; " << carbData[food] << endl;
    }
}

/// @brief Calls the chooseFood functions and returns a JSON of the chosen foods
/// @param algorithm Whether the program should use merge sort or pancake sort
/// @param protein Amount of protein (in g)
/// @param carb Amount of carb (in g)
/// @param fat Amount of fat (in g)
/// @return returns a json of the chosen foods
json Sorting::calculateFoods(bool algorithm, float protein, float carb, float fat)
{
    // Choose which algorithm to sort the foods by. True = mergeSort False = pancakeSort
    carbIdx = indices;
    proteinIdx = indices;
    fatIdx = indices;

    if (algorithm)
    {
        mergeSort(proteinIdx, 0, proteinIdx.size() - 1, proteinData);
        mergeSort(carbIdx, 0, carbIdx.size() - 1, carbData);
        mergeSort(fatIdx, 0, fatIdx.size() - 1, fatData);
    }
    else
    {
        pancakeSort(proteinIdx, proteinIdx.size() - 1, proteinData);
        pancakeSort(carbIdx, carbIdx.size() - 1, carbData);
        pancakeSort(fatIdx, fatIdx.size() - 1, fatData);
    }

    // For reasonable food options, cut off first 100 entries. This is the pool of foods we pull from
    carbIdx.assign(carbIdx.begin() + 100, carbIdx.end());
    proteinIdx.assign(proteinIdx.begin() + 100, proteinIdx.end());
    fatIdx.assign(fatIdx.begin() + 100, fatIdx.end());

    // Get vector of indices of foods
    vector<int> foods = chooseFoods(protein, carb, fat);

    // Return a json of the foods
    return createFoodJSON(foods);
}

/// @brief A function to find the optimal foods for consumption
/// @param protein Amount of protein (in g)
/// @param carb Amount of carbs (in g)
/// @param fat Amount of fat (in g)
/// @return vector of the indices of the chosen foods
vector<int> Sorting::chooseFoods(float protein, float carb, float fat)
{
    // Keep running while there is a category of macro to fulfil
    // Depending on which macro is most needed, find the value that most closely matches
    // Keep track of the values of all macros when food is added
    // Using modulus, pick a value 1.5x or better of requested amount

    string food;
    int foodIdx = 0;
    vector<int> foods;
    bool checkDouble;

    while (protein > 0 && fat > 0)
    {
        if (protein >= fat) // protein >= carb &&
            foodIdx = choose(proteinIdx, proteinData, protein);
        else if (fat >= protein) // && fat >= carb
            foodIdx = choose(fatIdx, fatData, fat);

        for (int &i : foods)
        {
            string inFoods = mapper[i];
            string checkFood = mapper[foodIdx];
            string cat1 = allData[inFoods]["Category"];
            string cat2 = allData[checkFood]["Category"];
            if (cat1 == cat2)
            {
                checkDouble = true;
                break;
            }
        }

        if (foodIdx != -1 && !checkDouble)
        {
            foods.emplace_back(foodIdx);
            food = mapper[foodIdx];
            carb -= carbData[food];
            protein -= proteinData[food];
            fat -= fatData[food];
        }
        checkDouble = false;
    }

    while (carb > 10)
    {
        foodIdx = choose(carbIdx, carbData, carb);

        if (foodIdx != -1)
        {
            foods.emplace_back(foodIdx);
            food = mapper[foodIdx];
            carb -= carbData[food];
            protein -= proteinData[food];
            fat -= fatData[food];
        }
    }

    return foods;
}

/// @brief Finds the optimal macro based on the given values
/// @param macroIdx The indices of the foods
/// @param macroData Vector of the macros stored
/// @param macro Value to match
/// @return returns the ID of the food, otherwise returns -1
int Sorting::choose(vector<int> &macroIdx, map<string, float> &macroData, float &macro)
{
    for (int &idx : macroIdx)
    {
        string food = mapper[idx];
        int tempIdx = idx;

        if (macroData[food] < macro && idx != -1)
        {
            idx = -1;
            return tempIdx;
        }
    }
    return -1;
}

/// @brief Creates a JSON of the foods
/// @param foods Indices of the foods
/// @return json object of the foods
json Sorting::createFoodJSON(const vector<int> &foods)
{
    json outputFoods;
    for (int foodIdx : foods)
    {
        string food = mapper[foodIdx];
        outputFoods.emplace_back(allData[food]);
    }
    return outputFoods;
}
