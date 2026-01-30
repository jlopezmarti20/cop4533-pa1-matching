#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include "verifier.h"





void verifier(){
    try{
        size_t n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::vector<int>> h_to_s_prefs = readPrefList(n);
    std::vector<std::vector<int>> s_to_h_prefs = readPrefList(n);

    std::cout << "\nHospitals' preference list:" << std::endl;
    printPrefList(h_to_s_prefs);

    std::cout << "\nStudents' preference list:" << std::endl;
    printPrefList(s_to_h_prefs);

    Matchings m = readMatches(n);

    std::unordered_map<int, int> stud_match = m.student_to_hospital;
    std::unordered_map<int, int> hosp_match = m.hospital_to_student;


    std::unordered_map<int, std::unordered_map<int, int>>stud_ranks = createStudentRankings(s_to_h_prefs);
    // look for unstable matches
    for (auto it = hosp_match.begin(); it != hosp_match.end(); ++it){
        int h = it->first;
        int s = it->second;
        std::pair<int, int> blocking_pair = blockingPair(h_to_s_prefs[h - 1], stud_ranks, stud_match, h, s);
        if (blocking_pair.first != -1){
            std::cout<< "\nUNSTABLE: Found blocking pair composed by hospital " << blocking_pair.first << " and student " 
            << blocking_pair.second << std::endl;
            return;
        }
    }
    std::cout << "\nSTABLE VALID" << std::endl;
    return;
    } catch (const std::invalid_argument& e){
        std::cout << e.what() << std::endl;
        return;
    }
    
}

void verifier(std::vector<std::vector<int>> h_to_s_prefs, 
    std::vector<std::vector<int>> s_to_h_prefs,
    std::unordered_map<int, int> stud_match,
    std::unordered_map<int, int> hosp_match,
    size_t n
    ){
        try{
            if (h_to_s_prefs.size() != n){
            throw std::invalid_argument("Hospital preference list does not match expected size");
        }
        if (s_to_h_prefs.size() != n){
            throw std::invalid_argument("Student preference list does not match expected size");
        }

        std::unordered_map<int, std::unordered_map<int, int>>stud_ranks = createStudentRankings(s_to_h_prefs);
        std::cout<< "Student ranks created" << std::endl;
        // look for unstable matches
        for (auto it = hosp_match.begin(); it != hosp_match.end(); ++it){
            int h = it->first;
            int s = it->second;
            std::pair<int, int> blocking_pair = blockingPair(h_to_s_prefs[h - 1], stud_ranks, stud_match, h, s);
            if (blocking_pair.first != -1){
                std::cout<< "UNSTABLE: Found blocking pair composed by hospital " << blocking_pair.first << " and student " 
                << blocking_pair.second << std::endl;
                return;
            }
        }
        std::cout << "STABLE VALID" << std::endl;
        return;
        } catch (std::invalid_argument& e){
            std::cout << e.what() << std::endl;
            return;
        }
        
}

std::pair<int, int> blockingPair(
    const std::vector<int> &h_to_s_pref, 
    std::unordered_map<int, std::unordered_map<int, int>>& stud_ranks, 
    const std::unordered_map<int, int>& stud_match,
    int h, 
    int s
){
    for (size_t i = 0; i < h_to_s_pref.size() && h_to_s_pref[i] != s; i++){
        int curr_student = h_to_s_pref[i];
        int curr_stud_match = stud_match.at(curr_student);
        // smaller rank means higher up on list -> more desired candidate, so blocking pair
        if (stud_ranks[curr_student][h] < stud_ranks[curr_student][curr_stud_match]) 
            return {h, curr_student};
    }
    // did not find a blocking pair
    return {-1, -1};
}

/**
 * @brief Creates a mapping for quickly retrieving ranking given to a hospital by a student from 0 to (n - 1).
 *      i.e. map[student][hospital] = rank
 */
std::unordered_map<int, std::unordered_map<int, int>> createStudentRankings(
    const std::vector<std::vector<int>>& s_to_h_prefs
){
    
    std::unordered_map<int, std::unordered_map<int, int>> stud_ranks;
    // iterate over pref list of each student
    for (size_t i = 1; i < s_to_h_prefs.size() + 1; i++){
        // ranking = index of each value in vector
        for (size_t rank = 0; rank < s_to_h_prefs[i - 1].size(); rank++){
            // retrieve hospital at given rank
            int h = s_to_h_prefs.at(i - 1).at(rank);
            // set value
            stud_ranks[i][h] = rank;
        }
    }
    return stud_ranks;
}

std::vector<int> readVectorLine(){
    std::string line;
    std::getline(std::cin, line);

    std::istringstream ss(line);
    std::vector<int> vec;
    int x;

    while (ss >> x){
        vec.push_back(x);
    }
    return vec;
}

void sanityCheck1DVec(const std::vector<int>& vec, int n){
    std::unordered_set<int> seen;
    for (int id : vec) {
        if (id < 1 || id > n) {
            std::cout << "INVALID: ID " << id << " out of range [1," << n << "]\n";
            return;
        }
        if (!seen.insert(id).second){
            throw std::invalid_argument(
                "INVALID: Duplicate ID " + std::to_string(id) +
                " in preference list"
            );
        }
    }
}

void printPrefList(const std::vector<std::vector<int>> &pref_list)
{
    for (size_t row = 0; row < pref_list.size(); row++){
        std::cout << row + 1 << ": ";
        for (size_t entry = 0; entry < pref_list[row].size(); entry++){
            std::cout << pref_list[row][entry] << " ";
        }
        std::cout << std::endl;

    }
}

std::vector<std::vector<int>> readPrefList(size_t n){
    std::vector<std::vector<int>> pref_list;
    for (size_t i = 0; i < n; i++){
        std::vector<int> vec = readVectorLine();
        if (vec.size() != n) {
            throw std::invalid_argument(
                "INVALID: reference list expected to be of size " +
                std::to_string(n) +
                ". Received size " +
                std::to_string(vec.size()) +
                " instead"
            );
        }
        pref_list.push_back(vec);
        sanityCheck1DVec(vec, n);
    }
    return pref_list;
}

Matchings readMatches(size_t n) {
    Matchings m;

    for (size_t i = 0; i < n; i++) {
        auto pair = readVectorLine();

        if (m.hospitals.find(pair[0]) != m.hospitals.end()) {
            throw std::invalid_argument(
                "INVALID: Hospitals must only be in one matching. "
                "Received multiple matching for hospital " +
                std::to_string(pair[0])
            );
        }

        if (m.students.find(pair[1]) != m.students.end()) {
            throw std::invalid_argument(
                "INVALID: Students must only be in one matching. "
                "Received multiple matching for student " +
                std::to_string(pair[1])
            );
        }

        m.hospitals.insert(pair[0]);
        m.students.insert(pair[1]);
        m.student_to_hospital[pair[1]] = pair[0];
        m.hospital_to_student[pair[0]] = pair[1];
    }

    return m;
}
