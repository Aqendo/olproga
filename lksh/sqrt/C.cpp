#include <bits/stdc++.h>

using namespace std;

struct Query {
    int l, r, x, y, index;
};

struct Arithmetic_Progression {
    int a1, k;
    Arithmetic_Progression operator+(const Arithmetic_Progression& q) const { return {a1 + q.a1, k + q.k}; }
    Arithmetic_Progression& operator+=(Arithmetic_Progression const& q) {
        a1 += q.a1;
        k += q.k;
        return *this;
    }
};

constexpr int k = 300;

void solve() {
    int n, q;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    cin >> q;
    vector<vector<Query>> queries((q + k - 1) / k);
    for (int qq = 0; qq < q; ++qq) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        l--;
        r--;
        queries[qq / k].push_back(Query{l, r, x, y, qq});
    }
    vector<int> answer(n, INT_MIN);
    for (int i = 0; i < n; ++i) {
        a[i] -= b[i];
        if (a[i] >= 0) answer[i] = 0;
    }
    vector<int> now = a;
    for (auto& block : queries) {
        vector<int> next_ = now;
        vector<Arithmetic_Progression> blocks(n / k + 2, {0, 0});
        for (auto [l, r, x, y, index] : block) {
            int old_l = l, old_r = r;
            if (r - l <= 2 * k) {
                for (int i = l; i <= r; ++i) {
                    next_[i] += x + (i - l) * y;
                }
            } else {
                for (; l % k != 0 && l < n; ++l) {
                    next_[l] += x + (l - old_l) * y;
                }
                for (; r % k != k - 1 && r >= 0; --r) {
                    next_[r] += x + (r - old_l) * y;
                }
                for (int i = l / k; i <= r / k; ++i) {
                    blocks[i] += {x + y * (i * k - old_l), y};
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            auto& current_block = blocks[i / k];
            int result = next_[i] + current_block.a1 + current_block.k * (i - i / k * k);
            if (answer[i] == INT_MIN && result >= 0) {
                int el = now[i];
                for (auto [l, r, x, y, index] : block) {
                    if (l <= i && i <= r) {
                        el += x + (i - l) * y;
                        if (el >= 0) {
                            answer[i] = index + 1;
                            break;
                        }
                    }
                }
            }
            now[i] = result;
        }
    }
    for (int i : answer) {
        cout << (i == INT_MIN ? -1 : i) << ' ';
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}