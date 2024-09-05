#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif
  
vector<vector<int>> g;
vector<int> M;
vector<bool> used;
vector<bool> used_a, used_b, is_painted;
int m, n;

bool try_kuhn(int a) {
    if (used[a]) return false;
    used[a] = true;
    for (int b : g[a]) {
        if (M[b] == -1 || try_kuhn(M[b])) {
            M[b] = a;
            return true;
        }
    }
    return false;
}

void kuhn() {
    for (int i = 0; i < m; ++i) {
        used.assign(m, {});
        try_kuhn(i);
    }
}

bool try_kuhn_max_independent(int a) {
    if (used_a[a]) return false;
    used_a[a] = true;
    for (int b : g[a]) {
        used_b[b] = true;
        if (M[b] == -1 || try_kuhn_max_independent(M[b])) {
            M[b] = a;
            return true;
        }
    }
    return false;
}

void kuhn_max_independent() {
    used_a.assign(m, {});
    used_b.assign(n, {});
    for (int i = 0; i < m; ++i) {
        if (!is_painted[i]) {
            try_kuhn_max_independent(i);
        }
    }
}

void init() {
    g.assign(m, {});
    M.assign(n, -1);
    used.assign(m, {});
    is_painted.assign(m, {});
}

void solve() {
    cin >> m >> n;
    init();
    for (int i = 0; i < m; ++i) {
        vector<bool> used_(n);
        int x;
        cin >> x;
        while (x-- != 0) {
            used_[x] = true;
            cin >> x;
        }
        for (int j = 0; j < n; ++j) {
            if (!used_[j]) {
                g[i].push_back(j);
            }
        }
    }
    kuhn();
    for (int i = 0; i < n; ++i) {
        if (M[i] != -1) {
            is_painted[M[i]] = true;
        }
    }
    kuhn_max_independent();
    vector<int> S, m_T;
    for (int i = 0; i < m; ++i) {
        if (used_a[i]) {
            S.push_back(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used_b[i]) {
            m_T.push_back(i);
        }
    }
    cout << S.size() + m_T.size() << '\n';
    cout << S.size() << ' ' << m_T.size() << '\n';
    for (int i : S) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
    for (int i : m_T) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
