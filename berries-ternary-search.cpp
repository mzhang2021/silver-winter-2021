#include <bits/stdc++.h>
using namespace std;

int n, k, b[1005];

int check(int x) {
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
        return INT_MIN;
    }
    sort(remaining.rbegin(), remaining.rend());
    for (int i=0; i<min(reqLower, (int)remaining.size()); i++)
        currentAnswer += remaining[i];
    return currentAnswer;
}

int main() {
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    cin >> n >> k;
    for (int i=0; i<n; i++)
        cin >> b[i];

    // try all x (cutoff between lower half and upper half), for a given x, use a greedy strategy to fill all the baskets
    int l = 1, r = 1005;
    while (r - l > 5) {
        int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (check(m1) < check(m2))
            l = m1;
        else
            r = m2;
    }
    int answer = 0;
    for (int x=l; x<=r; x++)
        answer = max(answer, check(x));
    cout << answer << "\n";

    return 0;
}
