#pragma once
#include <vector>
#include <unordered_map>

void verifier();
std::pair<int, int> blockingPair(
    const std::vector<int>& h_to_s_pref, 
    std::unordered_map<int, std::unordered_map<int, int>>& stud_ranks, 
    const std::unordered_map<int, int>& stud_match,
    int h, 
    int s
);

std::unordered_map<int, std::unordered_map<int, int>> createStudentRankings(
    const std::vector<std::vector<int>>& s_to_h_prefs
);

std::vector<int> readVectorLine();

