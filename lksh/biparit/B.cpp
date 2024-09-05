#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<vector<int>> g;
vector<int> M;
vector<int> used_a, used_b;
vector<bool> is_painted;
int n, m;

bool try_kuhn(int a) {
    if (used_a[a]) return false;
    used_a[a] = true;
    for (int b : g[a]) {
        used_b[b] = true;
        if (M[b] == -1 || try_kuhn(M[b])) {
            M[b] = a;
            return true;
        }
    }
    return false;
}

void kuhn() {
    for (int i = 0; i < m; ++i) {
        if (!is_painted[i]) {
            try_kuhn(i);
        }
    }
}

void init() {
    g.assign(m, {});
    M.assign(n, -1);
    is_painted.assign(m, {});
    used_a.assign(m, {});
    used_b.assign(n, {});
}

void solve() {
    cin >> m >> n;
    init();
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int u;
            cin >> u;
            u--;
            g[i].push_back(u);
        }
    }
    for (int i = 0; i < m; ++i) {
        int index;
        cin >> index;
        if (index != 0) {
            M[index - 1] = i;
            is_painted[i] = true;
        }
    }
    kuhn();
    vector<int> m_S, T;
    for (int i = 0; i < m; ++i) {
        if (!used_a[i]) {
            m_S.push_back(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (used_b[i]) {
            T.push_back(i);
        }
    }
    cout << m_S.size() + T.size() << '\n';
    cout << m_S.size() << ' ';
    for (int i : m_S) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
    cout << T.size() << ' ';
    for (int i : T) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
