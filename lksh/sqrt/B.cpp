#include <bits/stdc++.h>

using namespace std;

constexpr int k = 300;

void solve() {
    int64_t n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    vector<vector<int64_t>> blocks(n / k + 2);
    vector<int64_t> adder(n / k + 2);

    for (int64_t i = 0; i < n; ++i) {
        cin >> a[i];
        blocks[i / k].push_back(a[i]);
    }
    for (auto& i : blocks) {
        sort(i.begin(), i.end());
    }
    for (int64_t i = 0; i < m; ++i) {
        char move_str;
        cin >> move_str;
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        r--;
        if (move_str == '+') {
            if (r - l <= 2 * k) {
                int ll = l / k;
                int rr = r / k;
                vector<int64_t> res[3];
                for (int j = ll * k; j < (rr + 1) * k && j < n; ++j) {
                    if (l <= j && j <= r) {
                        a[j] += x;
                    }
                    res[j / k - l / k].push_back(a[j]);
                }
                sort(res[0].begin(), res[0].end());
                sort(res[1].begin(), res[1].end());
                sort(res[2].begin(), res[2].end());
                for (int j = ll; j <= rr; ++j) {
                    blocks[j] = move(res[j - ll]);
                }
            } else {
                vector<int64_t> sorted;
                for (int j = l / k * k; j < l; ++j) {
                    sorted.push_back(a[j]);
                }
                for (int j = l; j <= min(r, (l / k + 1) * k - 1); ++j) {
                    a[j] += x;
                    sorted.push_back(a[j]);
                }
                sort(sorted.begin(), sorted.end());
                blocks[l / k] = move(sorted);
                vector<int64_t> sorted2;
                for (int j = r / k * k; j <= r; ++j) {
                    a[j] += x;
                    sorted2.push_back(a[j]);
                }
                for (int j = r + 1; j < (r / k + 1) * k; ++j) {
                    sorted2.push_back(a[j]);
                }
                sort(sorted2.begin(), sorted2.end());
                blocks[r / k] = move(sorted2);
                for (int j = l / k + 1; j <= r / k - 1; ++j) {
                    adder[j] += x;
                }
            }
        } else {
            bool ans = false;
            if (r - l <= 2 * k) {
                for (int j = l; j <= r; ++j) {
                    ans |= a[j] == x - adder[j / k];
                }
            } else {
                for (; l % k != 0 && l < n; ++l) ans |= a[l] == x - adder[l / k];
                for (; r % k != k - 1 && r >= 0; --r) ans |= a[r] == x - adder[r / k];
                for (int64_t j = l / k; j <= r / k; ++j) {
                    ans |= binary_search(blocks[j].begin(), blocks[j].end(), x - adder[j]);
                }
            }

            cout << (ans ? "YES" : "NO") << endl;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}