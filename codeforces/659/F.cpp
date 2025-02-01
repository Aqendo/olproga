#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> a;
vector<vector<int8_t>> used;
clock_t ST;
double TL() {
    return (double)(clock() - ST) / CLOCKS_PER_SEC;
}
int n, m, amount;
long long k, mn;
struct DSU {
    vector<int> sizes, parent;
    vector<long long> sum;
    void init(int nn) {
        sizes.assign(nn, 1);
        sum.assign(nn, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                sum[i * m + j] = a[i][j];
            }
        }
        parent.assign(nn, {});
        iota(parent.begin(), parent.end(), 0);
    }
    int getp(int x) {
        if (x == parent[x]) return x;
        return parent[x] = getp(parent[x]);
    }
    void unite(int aa, int b) {
        aa = getp(aa);
        b = getp(b);
        if (aa == b) return;
        if (sizes[aa] < sizes[b]) swap(aa, b);
        sizes[aa] += sizes[b];
        sum[aa] += sum[b];
        parent[b] = aa;
    }
};

bool check(int i, int j) {
    return 0 <= i && i <= n - 1 && 0 <= j && j <= m - 1 && a[i][j] >= mn;
}
int timer = 0;
void dfs(vector<vector<int>> &answer, int i, int j) {
    if (timer == amount) return;
    used[i][j] = 1;
    answer[i][j] = mn;
    timer++;
    if (timer == amount) return;
    for (auto [ioff, joff] : vector<pair<int, int>>{{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}}) {
        if (timer == amount) return;
        if (check(i + ioff, j + joff) && !used[i + ioff][j + joff]) {
            dfs(answer, i + ioff, j + joff);
        }
    }
}

void solve() {
    cin >> n >> m >> k;
    a.assign(n, vector<int>(m));
    set<int> was;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            was.insert(a[i][j]);
        }
    }
    vector<int> amount_cells;
    for (int i = 1; i <= n * m; ++i) {
        if (k % i == 0) {
            if (was.contains(k / i))
                amount_cells.push_back(i);
        }
    }
    DSU dsu;
    sort(amount_cells.begin(), amount_cells.end());
    amount_cells.erase(unique(amount_cells.begin(), amount_cells.end()), amount_cells.end());
    int l = 0, r = amount_cells.size();
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        int am = amount_cells[mid];
        timer = 0;
        amount = am;
        mn = k / am;
        // cout << mn << ' ' << amount << endl;
        dsu.init(n * m);
        int good_id = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] >= mn) {
                    for (auto [ioff, joff] : vector<pair<int, int>>{{{-1, 0}, {0, -1}}}) {
                        if (check(i + ioff, j + joff)) {
                            dsu.unite(i * m + j, (i + ioff) * m + j + joff);
                        }
                    }
                }
            }
        }
        long long mx = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                mx = max(mx, dsu.sum[dsu.getp(i * m + j)]);
            }
        }
        if (good_id == -1) {
            if (mx >= k) {
                l = mid;
            } else {
                r = mid;
            }
            continue;
        }
    }
    if (amount_cells.empty()) {
        cout << "NO\n";
        return;
    }
    for (int index = l; index >= 0; --index) {
        if (TL() > 3.7) break;
        int am = amount_cells[index];
        timer = 0;
        amount = am;
        mn = k / am;
        // cout << mn << ' ' << amount << endl;
        dsu.init(n * m);
        int good_id = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] >= mn) {
                    for (auto [ioff, joff] : vector<pair<int, int>>{{{-1, 0}, {0, -1}}}) {
                        if (check(i + ioff, j + joff)) {
                            dsu.unite(i * m + j, (i + ioff) * m + j + joff);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dsu.sizes[dsu.getp(i * m + j)] >= am) {
                    if (a[i][j] == mn) {
                        good_id = i * m + j;
                    }
                }
            }
        }
        if (good_id == -1) {
            continue;
        }
        vector<vector<int>> answer(n, vector<int>(m));
        used.assign(n, vector<int8_t>(m));
        dfs(answer, good_id / m, good_id % m);
        cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << answer[i][j] << ' ';
            }
            cout << '\n';
        }
        return;
    }
    cout << "NO\n";
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}