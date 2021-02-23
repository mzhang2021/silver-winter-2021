#include <bits/stdc++.h>
using namespace std;

int main() {
    // take input
    int n;
    cin >> n;
    vector<pair<int, int>> cow(n);
    vector<int> sortedX(n), sortedY(n);
    for (int i=0; i<n; i++) {
        cin >> cow[i].first >> cow[i].second;
        sortedX[i] = cow[i].first;
        sortedY[i] = cow[i].second;
    }

    // now coordinates are compressed to values 1, 2, ..., n
    map<int, int> compressX, compressY;
    sort(sortedX.begin(), sortedX.end());
    sort(sortedY.begin(), sortedY.end());
    for (int i=0; i<n; i++) {
        compressX[sortedX[i]] = i + 1;
        compressY[sortedY[i]] = i + 1;
    }

    // using 1-indexing for the prefix sums so I don't have to worry about out of bounds indexing
    vector<vector<int>> pref(n + 1, vector<int>(n + 1));
    for (int i=0; i<n; i++) {
        pref[compressX[cow[i].first]][compressY[cow[i].second]]++;
    }
    for (int i=0; i<=n; i++)
        for (int j=0; j<=n; j++) {
            if (i > 0) pref[i][j] += pref[i-1][j];
            if (j > 0) pref[i][j] += pref[i][j-1];
            if (i > 0 && j > 0) pref[i][j] -= pref[i-1][j-1];
        }

    long long ret = 1;  // add one for empty subset
    sort(cow.begin(), cow.end());
    // sweep left and right boundaries
    for (int l=0; l<n; l++)
        for (int r=l; r<n; r++) {
            int lx = compressX[cow[l].first], ly = compressY[cow[l].second], rx = compressX[cow[r].first], ry = compressY[cow[r].second];
            if (lx > rx)
                swap(lx, rx);
            if (ly > ry)
                swap(ly, ry);
            // count valid top and bottom boundaries
            int above = pref[rx][n] - pref[lx - 1][n] - pref[rx][ry - 1] + pref[lx - 1][ry - 1], below = pref[rx][ly] - pref[lx - 1][ly];
            ret += above * below;
        }
    cout << ret << "\n";

    return 0;
}
