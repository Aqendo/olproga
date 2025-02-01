#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define get_bit(x, bit) ((x) >> bit & 1)

int get(int Rx, int Ry, int Rz) {
    vector<int> a;
    a.push_back(1);
    int dp[31][2][2][2] = {0};
    dp[30][1][1][1] = 1;
    // dp[i][F_x][F_y][F_z]
    for (int bit = 29; bit >= 0; --bit) {
        for (int x = 0; x < 2; ++x) {
            for (int y = 0; y < 2; ++y) {
                for (int z = 0; z < 2; ++z) {
                    for (int fx = 0; fx < 2; ++fx) {
                        for (int fy = 0; fy < 2; ++fy) {
                            for (int fz = 0; fz < 2; ++fz) {
                                if ((x | y) != (y ^ z)) continue;
                                if (fx && x > get_bit(Rx, bit)) continue;
                                if (fy && y > get_bit(Ry, bit)) continue;
                                if (fz && z > get_bit(Rz, bit)) continue;
                                int newfx = 0, newfy = 0, newfz = 0;
                                if (fx == 1 && x == get_bit(Rx, bit)) {
                                    newfx = 1;
                                }
                                if (fy == 1 && y == get_bit(Ry, bit)) {
                                    newfy = 1;
                                }
                                if (fz == 1 && z == get_bit(Rz, bit)) {
                                    newfz = 1;
                                }
                                dp[bit][newfx][newfy][newfz] += dp[bit + 1][fx][fy][fz];
                            }
                        }
                    }
                }
            }
        }
    }
    int answer = 0;
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                answer += dp[0][x][y][z];
            }
        }
    }
    return answer;
}

void solve() {
    int l, r;
    cin >> l >> r;
    if (l == 0) {
        cout << get(r, r, r) << '\n';
        return;
    }
    int answer = 0;
    int a[] = {l - 1, r};
    for (int mask = 0; mask < 8; ++mask) {
        int s = get_bit(mask, 0) + get_bit(mask, 1) + get_bit(mask, 2);
        answer += (s & 1 ? 1 : -1) * get(a[get_bit(mask, 0)], a[get_bit(mask, 1)], a[get_bit(mask, 2)]);
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}