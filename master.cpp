#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <deque>
#include <queue>
#include <numeric>
#include <set>
#include <map>


using namespace std;

using graph = vector<vector<int>>;
using vi = vector<int>;
using ll = long long;

using ll = long long;

bool kun(int u, const graph& g, vector<int>& mt, vector<int>& vis) {
    if (vis[u]) {
        return false;
    }
    vis[u] = true;
    for (int v : g[u]) {
        if (mt[v] == -1 || kun(mt[v], g, mt, vis)) {
            mt[v] = u;
            return true;
        }
    }
    return false;
}

const int black = 1;
const int green = 2;
const int red = 3;

bool dfs(int u, int prev, const graph& g, vi& colour) {
    if (colour[u] != black) {
        if (colour[u] != colour[prev]) {
            return true;
        }
        return false;
    }
    if (colour[prev] == green) {
        colour[u] = red;
    } else {
        colour[u] = green;
    }
    for (int v : g[u]) {
        if (v == prev) {
            continue;
        }
        bool found = dfs(v, u, g, colour);
        if (!found) {
            return false;
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        if (u == v) {
            cout << -1;
            return;
        }
        g[u].push_back(v);
    }
    vi colour(n, black);
    for (int i = 0; i < n; ++i) {
        if (colour[i] == black) {
            if (!dfs(i, i, g, colour)) {
                cout << -1;
                return;
            }
        }
    }
    vector<int> mt(n, -1), vis(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (colour[i] == green) {
            vis.assign(n, 0);
            ans += kun(i, g, mt, vis);
        }
    }
    cout << ans << '\n';
    for (int i = 0; i < n; ++i) {
        if (mt[i] != -1) {
            cout << mt[i] + 1 << ' ' << i + 1 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
}
