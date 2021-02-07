#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        // read input
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i=0; i<n; i++) {
            cin >> a[i];
            a[i]--;
        }

        /*
        Main Idea: This problem is interesting becauses it asks you to examine the properties of the BFS algorithm.
        Remember that the BFS algorithm visits the nodes in layers based on depth away from the starting node.
        We're told that a node visits its children in ascending order, and we want to minimize the depth of the tree formed.
        After the first node, it makes logical sense that we should try to pack as many nodes as children of that node as possible.
        Consider what happens if we don't pack as many nodes as possible. We'll end up placing new nodes as children of deeper nodes instead.
        If the array is [1, 2, 3, 4, 5], We'll get something like this:

            1
           /\
          2  3
         /\
        4 5

        instead of:

            1
         / /\ \
        2 3 4 5

        Clearly, the latter case is more optimal.
        Therefore, we will do the following: keep taking increasing sequences in the array from left to right, and put them underneath the
        shallowest node available. This will minimize the depth of the overall tree.
        Here's an example to clarify:
        a = [1, 2, 3, 4, 6, 5, 7, 8]

             1
           / /\
          2 3  4
         / /  /\
        6 5  7 8

        O(n)
        */

        int ptr = 0;    // ptr points to the shallowest depth with an available node
        vector<int> layer(n + 1);   // layer will store the number of nodes available at each layer
        layer[0] = 1;
        for (int i=1; i<n;) {
            int j = i + 1;
            while (j < n && a[j] > a[j-1])
                j++;    // [i, j-1] will represent an increasing sequence in the array
            layer[ptr]--;   // take a node as high up as possible...
            layer[ptr+1] += j - i;  // ... and make all of the nodes in range [i, j-1] its children!
            if (layer[ptr] == 0)    // if we ran out of available nodes on this layer, we'll move to the next
                ptr++;
            i = j;
        }

        int ans = ptr;
        while (ans < n && layer[ans+1] > 0)
            ans++;  // ans will be the deepest layer for which there are nodes
        cout << ans << "\n";
    }

    return 0;
}
