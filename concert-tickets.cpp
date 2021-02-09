#include <bits/stdc++.h>
using namespace std;

int main() {
    // input stuff
    int n, m;
    cin >> n >> m;
    vector<int> h(n);
    for (int i=0; i<n; i++)
        cin >> h[i];
    vector<int> t(m);
    for (int i=0; i<m; i++)
        cin >> t[i];

    map<int, int> mp;
    for (int i=0; i<n; i++)
        mp[h[i]]++;
    // if I access an element that wasn't in the map
    // before, it auto inserts with value 0

    for (int i=0; i<m; i++) {
        auto it = mp.upper_bound(t[i]);
        // one before first element > x = last element <= x
        if (it == mp.begin()) {
            // nothing before it
            // no tickets available, -1
            cout << "-1\n";
        } else {
            it--;
            int ticket = (*it).first;
            cout << ticket << "\n";
            mp[ticket]--;
            if (mp[ticket] == 0)
                mp.erase(ticket);   // no more of this ticket
        }
    }

    return 0;
}
