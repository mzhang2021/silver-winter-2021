#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    int n, k;
    cin >> n >> k;
    vector<int> b(n);
    for (int i=0; i<n; i++)
        cin >> b[i];

    // try all x (cutoff between lower half and upper half), for a given x, use a greedy strategy to fill all the baskets
    int answer = 0;
    for (int x=1; x<=1000; x++) {
        // first, fill in upper half with baskets of size x
        int reqUpper = k / 2, reqLower = k / 2, currentAnswer = 0;
        vector<int> remaining;
        for (int i=0; i<n; i++) {
            int full = b[i] / x, rem = b[i] % x, giveToUpper = min(reqUpper, full);
            reqUpper -= giveToUpper;
            full -= giveToUpper;
            // if there are leftover full baskets of size x, give to lower half
            int giveToLower = min(reqLower, full);
            reqLower -= giveToLower;
            currentAnswer += giveToLower * x;
            if (rem != 0)
                remaining.push_back(rem);
        }
        if (reqUpper > 0) {
            // I haven't filled the upper half, so this x won't work
            continue;
        }
        sort(remaining.rbegin(), remaining.rend());
        for (int i=0; i<min(reqLower, (int)remaining.size()); i++)
            currentAnswer += remaining[i];
        answer = max(answer, currentAnswer);
    }
    cout << answer << "\n";

    return 0;
}
