#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i=0; i<n; i++)
        cin >> a[i];

    k--;    // decrement k to account for jump to end
    sort(a.begin(), a.end());
    vector<int> gaps;
    int answer = 0, last = 0;   // last refers to the first portal occurring after the previous cow
    for (int i=0; i<n; i++) {
        // find the gaps, add gaps containing cows to answer, add empty gaps to 'gaps' vector
        int before = a[i] - a[i] % 12, after = a[i] + 12 - a[i] % 12;
        // this condition confirms there actually is an empty gap in between two cows
        if (before > last) {
            answer += before - last;
            gaps.push_back(before - last);
        }
        // if there are two cows in the same gap, I don't want to count the gap twice
        if (after > last) {
            answer += after - before;
            last = after;
        }
        // since both conditions have (before > last), I could probably combine both into one if, but wanted to make logic more clear
    }

    // sorts the gaps in reverse order
    sort(gaps.rbegin(), gaps.rend());
    for (int i=0; i<min(k, (int)gaps.size()); i++)
        answer -= gaps[i];
    cout << answer << "\n";

    return 0;
}
