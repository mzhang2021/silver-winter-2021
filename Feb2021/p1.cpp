#include <bits/stdc++.h>
using namespace std;

// map (0, 0) -> (501, 501)

const int MAX = 2005;
const int OFFSET = 501;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int neighborCount[MAX][MAX], answer = 0;
bool hasCow[MAX][MAX], isGhost[MAX][MAX];

void dfs(int x, int y, bool isReal) {
    // if (x + 1, y)
    // if (x - 1, y)
    // hardcode 4 if statements
    // alternatively:
    hasCow[x][y] = true;
    if (!isReal) {
        isGhost[x][y] = true;
        answer++;
    }
    for (int d=0; d<4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        // (nx, ny) is a neighbor of (x, y)
        if (hasCow[nx][ny]) {
            neighborCount[x][y]++;
            neighborCount[nx][ny]++;
        }
    }
    if (neighborCount[x][y] == 3) {
        for (int e=0; e<4; e++)
            if (!hasCow[x + dx[e]][y + dy[e]])
                dfs(x + dx[e], y + dy[e], false);   // triggers for the one empty spot
    }
    for (int d=0; d<4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (neighborCount[nx][ny] == 3) {
            for (int e=0; e<4; e++)
                if (!hasCow[nx + dx[e]][ny + dy[e]])
                    dfs(nx + dx[e], ny + dy[e], false); // triggers for the one empty spot
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        x += OFFSET;
        y += OFFSET;
        if (isGhost[x][y]) {
            isGhost[x][y] = false;
            answer--;
        } else {
            dfs(x, y, true);
        }
        cout << answer << "\n";
    }

    return 0;
}
