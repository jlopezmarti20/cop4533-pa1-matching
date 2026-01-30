#include "measure_time.h"
#include "../matcher/matcher.h"
#include "../verifier/verifier.h"
using namespace std;

// ===== Generate random preference lists =====
vector<vector<int>> generate_prefs(int n) {
    vector<vector<int>> prefs(n, vector<int>(n));
    mt19937 rng(random_device{}());

    for (int i = 0; i < n; ++i) {
        iota(prefs[i].begin(), prefs[i].end(), 0);
        shuffle(prefs[i].begin(), prefs[i].end(), rng);
    }

    return prefs;
}

int main() {
    vector<int> ns = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

    ofstream matcher_csv("matcher_times.csv");
    ofstream verifier_csv("verifier_times.csv");

    matcher_csv << "n,runtime_ms\n";
    verifier_csv << "n,runtime_ms\n";

    for (int n : ns) {
        auto h_prefs = generate_prefs(n);
        auto s_prefs = generate_prefs(n);

        cout << "Entering matcher" << endl;
        auto start_match = chrono::high_resolution_clock::now();
        Match match = matcher(n, h_prefs, s_prefs);
        auto end_match = chrono::high_resolution_clock::now();

        long long matcher_time =
            chrono::duration_cast<chrono::milliseconds>(end_match - start_match).count();

        matcher_csv << n << "," << matcher_time << "\n";

        /* --------- Time verifier --------- */
        for (int i = 0; i < n; i++){
            for (int j= 0; j < n; j++){
                h_prefs[i][j]++;
                s_prefs[i][j]++;
            }
        }
        auto start_verify = chrono::high_resolution_clock::now();
        cout << "entering verifier" << endl;
        verifier(
            h_prefs,
            s_prefs,
            match.stud_match,
            match.hosp_match,
            n
        );
        auto end_verify = chrono::high_resolution_clock::now();

        long long verifier_time =
            chrono::duration_cast<chrono::milliseconds>(end_verify - start_verify).count();

        verifier_csv << n << "," << verifier_time << "\n";
    }

    matcher_csv.close();
    verifier_csv.close();

    return 0;
}