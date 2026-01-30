#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Match{
    unordered_map<int, int> stud_match;
    unordered_map<int, int> hosp_match;
};

void matcher(int n);

Match matcher(size_t n, 
    vector<vector<int>> hosps, 
    vector<vector<int>> studs
    );