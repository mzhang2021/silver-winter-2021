#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1e9 + 5;

struct Edge {
    int a, b, w;
};

int id, p[MAXN], compId[MAXN];
Edge edges[MAXN];
vector<int> adj[MAXN];

void dfs(int u) {
    compId[u] = id;
    for (int v : adj[u])
        if (compId[v] == -1)
            dfs(v);
}

int main() {
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

    // read input
    int n, m;
    cin >> n >> m;
    for (int i=0; i<n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for (int i=0; i<m; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].w;
        edges[i].a--, edges[i].b--;
    }

    /*
    Main Idea: Let's build a graph! The "locations" are nodes and the "wormholes" are edges.
    Notice that as long as nodes A and B are in the same component, there is always a way to perform swaps to move from A to B.
    Just pick a path of edges from A to B, and swap the cow along those edges.
    Now for the hard part of this problem: maximizing the minimum weight edge we use.
    It's a bit difficult to determine the "optimal" path from A to B directly. If we try to DFS from A and greedily pick small edges,
    we risk trapping ourself with a larger edge later in the path. Plus, the time complexity of that solution will be too high!
    Notice something else about the minimum weight edge: we don't care what other edges we use in our path,
    as long as they're cheaper than the minimum weight edge. As an example, if I determine that '6' will be the minimum weight edge, then
    it doesn't matter if I use lots of edges of weight '7', '8', etc.
    Another way to phrase this observation is that if the minimum edge weight is D, we should be able to connect each cow to its proper
    location using only edges of weight D or higher. Checking if a certain value D is a much easier problem! Just build a graph with only
    edges of weight D or higher, run DFS, and check if each cow is in the same component as its proper location.
    But here's something else cool about D: if D works, then D - 1, D - 2, ... all work! Does that sound familiar?
    We will binary search for the value of D, and for a certain value of D, we will build a graph and check if all the cows can reach their locations.
    O((N + M) log W)
    */

    int l = 0, r = INF;
    while (l < r) {
        int d = (l + r) / 2;
        // build a graph with only edge weights of D or greater
        for (int i=0; i<n; i++) {
            adj[i].clear();
            compId[i] = -1; // -1 signifies an unvisited node
        }
        for (int i=0; i<m; i++)
            if (edges[i].w >= d) {
                adj[edges[i].a].push_back(edges[i].b);
                adj[edges[i].b].push_back(edges[i].a);
            }
        id = 0;
        for (int i=0; i<n; i++)
            if (compId[i] == -1) {
                dfs(i);
                id++;   // each component gets assigned a different ID
            }
        int cnt = 0;
        for (int i=0; i<n; i++)
            if (compId[i] == compId[p[i]])  // count number of cows in same component as proper location
                cnt++;
        if (cnt == n)
            l = d + 1;
        else
            r = d;
    }
    if (l >= INF)
        cout << "-1\n";
    else
        cout << l - 1 << "\n";

    return 0;
}
