#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;

int n;
vector<int> a;
vector<int> b;
vector<vector<int>> g;
clock_t ST;
long double TL() {
    return (long double)(clock() - ST) / CLOCKS_PER_SEC;
}

void solve() {
    cin >> n;
    a.assign(n, -1);
    b.assign(n, -1);
    g.assign(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    if (n == 1) {
        cout << "YES\n1\n1\n";
        return;
    } else if (n <= 3) {
        vector<vector<int>> ab(2);
        for (int j = 0; j < 2; ++j) {
            for (int i = 1; i <= n; ++i) {
                ab[j].push_back(i);
            }
        }
        vector<vector<int>> ab_orig = ab;
        do {
            ab[1] = ab_orig[1];
            do {
                bool good = true;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (ab[0][i] != g[i][j] && ab[1][j] != g[i][j]) {
                            good = false;
                            break;
                        }
                    }
                    if (!good) break;
                }
                if (good) {
                    cout << "YES\n";
                    for (int i : ab[0]) cout << i << ' ';
                    cout << endl;
                    for (int i : ab[1]) cout << i << ' ';
                    cout << endl;
                    return;
                }
            } while (next_permutation(ab[1].begin(), ab[1].end()));
        } while (next_permutation(ab[0].begin(), ab[0].end()));
        cout << "NO\n";
        return;
    }
    for (int i = 0; i < n; ++i) {
        int cnt_now = 0, el_now = -1;
        int mx = 0, mx_el = 0;
        for (int j : g[i]) {
            if (el_now != j) {
                if (cnt_now > mx) {
                    mx = cnt_now, mx_el = el_now;
                }
                el_now = j;
                cnt_now = 1;
            } else {
                cnt_now++;
            }
        }
        if (cnt_now > mx) {
            mx = cnt_now, mx_el = el_now;
        }
        if (mx >= 3 && n >= 4) {
            a[i] = mx_el;
        }
    }
    for (int i = 0; i < n; ++i) {
        int cnt_now = 0, el_now = -1;
        int mx = 0, mx_el = 0;
        for (int j = 0; j < n; ++j) {
            if (el_now != g[j][i]) {
                if (cnt_now > mx) {
                    mx = cnt_now, mx_el = el_now;
                }
                el_now = g[j][i];
                cnt_now = 1;
            } else {
                cnt_now++;
            }
        }
        if (cnt_now > mx) {
            mx = cnt_now, mx_el = el_now;
        }
        if (mx >= 3 && n >= 4) {
            b[i] = mx_el;
        }
    }
    while (true) {
        bool made_choice = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (a[i] != -1 && b[j] == -1 && a[i] != g[i][j]) {
                    made_choice = true;
                    b[j] = g[i][j];
                    for (int ii = 0; ii < n; ++ii) {
                        if (g[ii][j] != b[j]) {
                            a[ii] = g[ii][j];
                        }
                    }
                }
                if (b[j] != -1 && a[i] == -1 && b[j] != g[i][j]) {
                    made_choice = true;
                    a[i] = g[i][j];
                    for (int jj = 0; jj < n; ++jj) {
                        if (g[i][jj] != a[i]) {
                            b[jj] = g[i][jj];
                        }
                    }
                }
            }
        }
        if (!made_choice) break;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i] == -1 && b[j] == -1) {
                a[i] = g[i][j];
            }
            if (a[i] != g[i][j] && b[j] != g[i][j]) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
    set<int> left;
    for (int i = 1; i <= n; ++i) {
        left.insert(i);
    }
    set<int> left2 = left;
    for (int i = 0; i < n; ++i) {
        left.erase(a[i]);
    }
    for (int i = 0; i < n; ++i) {
        left2.erase(b[i]);
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] != -1) {
            cout << a[i] << ' ';
        } else {
            cout << *left.begin() << ' ';
            left.erase(left.begin());
        }
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        if (b[i] != -1) {
            cout << b[i] << ' ';
        } else {
            cout << *left2.begin() << ' ';
            left2.erase(left2.begin());
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
