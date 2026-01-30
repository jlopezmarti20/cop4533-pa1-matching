#pragma once
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct Matchings {
    std::unordered_set<int> hospitals;
    std::unordered_set<int> students;
    std::unordered_map<int, int> student_to_hospital;
    std::unordered_map<int, int> hospital_to_student;
};
void verifier();

void verifier(std::vector<std::vector<int>> h_to_s_prefs, 
    std::vector<std::vector<int>> s_to_h_prefs,
    std::unordered_map<int, int> stud_match,
    std::unordered_map<int, int> hosp_match,
    size_t n
);

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

Matchings readMatches(size_t n);

void sanityCheck1DVec(const std::vector<int>& vec, int n);

void printPrefList(const std::vector<std::vector<int>>& pref_list);

std::vector<std::vector<int>> readPrefList(size_t n);


