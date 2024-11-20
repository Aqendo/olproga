#include <bits/stdc++.h>

using namespace std;

struct Fenwick {
    vector<vector<vector<int64_t>>> fw;
    int64_t n;
    Fenwick(int64_t nn) : fw(nn, vector<vector<int64_t>>(nn, vector<int64_t>(nn))), n(nn) {}
    int64_t get(int64_t x, int64_t y, int64_t z) {
        int64_t ans = 0;
        for (int64_t i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int64_t j = y; j >= 0; j = (j & (j + 1)) - 1) {
                for (int64_t k = z; k >= 0; k = (k & (k + 1)) - 1) {
                    ans += fw[i][j][k];
                }
            }
        }
        return ans;
    }
    void update(int64_t x, int64_t y, int64_t z, int64_t add) {
        for (int64_t i = x; i < n; i |= i + 1) {
            for (int64_t j = y; j < n; j |= j + 1) {
                for (int64_t k = z; k < n; k |= k + 1) {
                    fw[i][j][k] += add;
                }
            }
        }
    }
};

void solve() {
    int64_t n;
    cin >> n;
    int64_t move;
    cin >> move;
    Fenwick fw(n + 1);
    while (move != 3) {
        if (move == 1) {
            int64_t x, y, z, k;
            cin >> x >> y >> z >> k;
            fw.update(x, y, z, k);
        } else {
            int64_t lx, ly, lz, rx, ry, rz;
            cin >> lx >> ly >> lz >> rx >> ry >> rz;
            cout << fw.get(rx, ry, rz) - fw.get(rx, ry, lz - 1) - fw.get(rx, ly - 1, rz) - fw.get(lx - 1, ry, rz) + fw.get(rx, ly - 1, lz - 1) +
                        fw.get(lx - 1, ry, lz - 1) + fw.get(lx - 1, ly - 1, rz) - fw.get(lx - 1, ly - 1, lz - 1)
                 << '\n';
        }
        cin >> move;
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}