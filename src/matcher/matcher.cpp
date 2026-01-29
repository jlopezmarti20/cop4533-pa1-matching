

#include <iostream>
#include <vector>
using namespace std;

void matcher(int n)
{
    // 2d tables
    vector<vector<int>> hosps(n, vector<int>(n));
    vector<vector<int>> studs(n, vector<int>(n));

    // intializing hospital preferences
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> hosps[i][j];
            hosps[i][j]--;
        }
    }

    // Initializing student preference
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> studs[i][j];
            studs[i][j]--;
        }
    }

    // ranking student choice preference
    vector<vector<int>> rank(n, vector<int>(n));
    for (int s = 0; s < n; s++)
    {
        for (int pos = 0; pos < n; pos++)
        {
            int h = studs[s][pos];
            rank[s][h] = pos;
        }
    }

    // matched/unmatched
    //  -1 = free
    vector<int> hosps_match(n, -1);
    vector<int> studs_match(n, -1);
    vector<int> next_proposal(n, 0);

    bool hosps_is_free = true;

    // G-S algo
    while (hosps_is_free)
    {

        hosps_is_free = false;

        for (int h = 0; h < n; h++)
        {
            if (hosps_match[h] == -1 && next_proposal[h] < n)
            {
                hosps_is_free = true;

                int s = hosps[h][next_proposal[h]];
                next_proposal[h]++;

                // student also free
                if (studs_match[s] == -1)
                {
                    // match h <-> s
                    studs_match[s] = h;
                    hosps_match[h] = s;
                }
                else
                {
                    // student current match
                    int h2 = studs_match[s];

                    // if student prefers new hospital h over current hospital h2
                    if (rank[s][h] < rank[s][h2])
                    {
                        // student switches to h
                        studs_match[s] = h;
                        hosps_match[h] = s;

                        // old hospital becomes free
                        hosps_match[h2] = -1;
                    }
                    else
                    {
                        // student rejects h
                        // nothing changes
                    }
                }
                break;
            }
        }
    }
    for (int h = 0; h < n; h++)
    {
        cout << (h + 1) << " " << (hosps_match[h] + 1) << "\n";
    }
}
int main()
{
    int n;
    cin >> n;
    matcher(n);
    return 0;
}
