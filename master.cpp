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
