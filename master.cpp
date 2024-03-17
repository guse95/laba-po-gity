#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <deque>
#include <queue>
#include <numeric>
#include <set>
#include <map>

using namespace std;
#define all(x) x.begin(), x.end()

using graph = vector<vector<int>>;
using vi = vector<int>;
using ll = long long;
using str = char;

const int N = 2e5;
graph g;
vi tin(N), tout(N);

void dfs(int u, int prev, int& t) {
    tin[u] = t++;
    for (int v : g[u]) {
        if (tin[v] == -1) {
            dfs(v, u, t);
        }
    }
    tout[u] = t++;
}

bool is_parent(int u, int v) {
    return (tin[u] < tin[v]) && (tout[v] < tout[u]);
}

void bfs(int str, const graph& g, vi& d) {
    queue<int> q;
    d[str] = 0;
    q.push(str);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (d[v] != -1) {
                continue;
            }
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
}

void bfs_2_0(int s, const graph& g, vector<set<str>>& d) {
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (is_parent(u, v)) {
                for (str el : d[v]) {
                    d[u].insert(el);
                }
            }
            q.push(v);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vi d(n, -1);
    graph g(n);
    for (int i = 0; i < (n - 1); ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs(0, g, d);
    int mx = 0, num = -1;
    for (int i = 0; i < n; ++i) {
        if (d[i] > mx) {
            mx = d[i];
            num = i;
        }
    }
    d.assign(n, -1);
    bfs(num, g, d);
    for (int i = 0; i < n; ++i) {
        if (d[i] > mx) {
            mx = d[i];
        }
    }
    cout << mx << '\n';
}

struct edge {
    int from, to;
    ll w;
};

struct dsu {
    int n;
    vector<int> lead;
    vector<int> rank;
    vector <vector<int>> way;

    dsu(int _n) : n(_n), lead(n), rank(n, 1), way(n) {
        iota(all(lead), 0);
    }

    int find(int u) {
        if (lead[u] == u) {
            way[u].push_back(u);
            return u;
        }
        lead[u] = find(lead[u]);
        way[u].push_back(lead[u]);
        return lead[u];
    }
    bool join(int u, int v) {
        int lu = find(u);
        int lv = find(v);
        if (lu == lv) {
            return false;
        }
        if (rank[lu] < rank[lv]) {
            swap(lu, lv);
        }
        rank[lu] += rank[lv];
        lead[lv] = lu;
        return true;
    }
};

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

void solve() {
    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
    }
    vector<int> mt(n, -1), vis(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vis.assign(n, 0);
        ans += kun(i, g, mt, vis);
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

    int n, q, cnt = 0, ind = 0, n1 = 0;
    cin >> n >> q;
    vector<ll> A(n);
    vector<ll> kex(q);
    vector<ll> kex_s(q);
    map<int, int> ans;
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    for (int i = 0; i < q; ++i) {
        cin >> kex[i];
        kex_s[i] = kex[i];
    }
    sort(all(kex_s));
    for (ll i = 0; i < (1e9 + 1); ++i) {
        if (ind < n) {
            if (i != A[ind]) {
                cnt += 1;
            }
            else {
                ind += 1;
            }
        }
        else {
            cnt += 1;
        }
        while (cnt == kex[n1]) {
            ans[kex[n1]] = i;
            n1 += 1;
            if (n1 > (q - 1)) {
                break;
            }
        }
        if (n1 > (q - 1)) {
            break;
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[kex_s[i]] << ' ';
    }
}
