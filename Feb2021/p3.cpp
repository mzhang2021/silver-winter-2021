#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> grid[i][j];

    // in this code I'm sweeping over top and bottom instead of left and right
    // same idea, just rotated
    long long answer = 0;
    for (int r1=0; r1<n; r1++) {
        vector<int> minInCol(n, INF);
        for (int r2=r1; r2<n; r2++) {
            for (int c=0; c<n; c++)
                minInCol[c] = min(minInCol[c], grid[r2][c]);
            // three pointers
            for (int i=0, j=0, k=0; i<n; i++) {
                if (minInCol[i] < 100)
                    continue;
                // find first column to right of i where the min is exactly 100
                if (j <= i) {
                    j = i;
                    while (j < n && minInCol[j] != 100)
                        j++;
                }
                // find first column to right of i where the min is < 100
                if (k <= j) {
                    k = j;
                    while (k < n && minInCol[k] >= 100)
                        k++;
                }
                answer += k - j;
            }
        }
    }
    cout << answer << "\n";

    return 0;
}
