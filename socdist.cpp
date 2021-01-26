#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18 + 5;

int n, m;
vector<pair<long long, long long>> intervals;

// check if a given D works
bool works(long long d) {
    // O(n * m)
    // no, this is actually O(n + m)
    int numCows = n;
    long long locationOfPreviousCow = -INF;
    for (int i=0; i<m; i++) {
        long long a = intervals[i].first, b = intervals[i].second;
        while (numCows > 0) {
            // while I have cows left over, place them as far left as possible
            // PREV            PREV + D   [........]
            long long nextPosition = max(locationOfPreviousCow + d, a);
            if (nextPosition > b)   // next possible position is beyond this interval
                break;
            // place a cow at nextPosition
            numCows--;
            locationOfPreviousCow = nextPosition;
        }
    }
    return numCows == 0;
}

int main() {
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);

    // handle input
    cin >> n >> m;
    for (int i=0; i<m; i++) {
        long long a, b;
        cin >> a >> b;
        intervals.emplace_back(a, b);
    }

    // sort the intervals
    sort(intervals.begin(), intervals.end());

    // binary search
    // O(log INF * Complexity of "works" function)
    long long l = 1, r = INF;
    while (l < r) {
        long long d = (l + r) / 2;
        if (works(d))
            l = d + 1;
        else
            r = d;
    }

    // print the answer
    cout << l - 1 << "\n";

    return 0;
}
