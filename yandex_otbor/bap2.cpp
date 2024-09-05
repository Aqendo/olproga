#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
// #define HOME
#include "../debug.h"
#else
#define debug(...)
#endif

int ask(int mn_x, int mn_y, int mx_x, int mx_y) {
    printf("? %lld %lld %lld %lld\n", mn_x, mn_y, mx_x, mx_y);
    fflush(stdout);
    int val;
    cin >> val;
    return val;
}
void solve() {
    mt19937 rng(234234);

    int n;
    cin >> n;
    vector<int> skip_col(n), skip_row(n);
    int amount = max<int>(0, (2 * n + 32 - 2007) / 2 + 1);
    for (int i = 0; i < amount; ++i) {
        int index = -1;
        do {
            index = uniform_int_distribution<int>(0, n - 1)(rng);
        } while (skip_col[index]);
        skip_col[index] = 1;
    }
    for (int i = 0; i < amount; ++i) {
        int index = -1;
        do {
            index = uniform_int_distribution<int>(0, n - 1)(rng);
        } while (skip_row[index]);
        skip_row[index] = 1;
    }
#ifdef HOME
    vector<int> odd_cols = {3, 5}, odd_rows;
#else
    vector<int> odd_cols, odd_rows;
    for (int i = 0; i < n; ++i) {
        if (!skip_col[i]) {
            int answer = ask(i + 1, 1, i + 1, n);
            if (answer & 1) {
                odd_cols.push_back(i);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!skip_row[i]) {
            int answer = ask(1, i + 1, n, i + 1);
            if (answer & 1) {
                odd_rows.push_back(i);
            }
        }
    }
#endif
    if (odd_cols.size() == 2 && odd_rows.size() == 2) {
        pair<int, int> pos1 = {odd_cols[0] + 1, odd_rows[0] + 1};
        pair<int, int> pos2 = {odd_cols[1] + 1, odd_rows[1] + 1};
        if (ask(pos1.first, pos1.second, pos1.first, pos1.second) != 1) {
            swap(pos1.second, pos2.second);
        }
        printf("! %lld %lld %lld %lld\n", pos1.first, pos1.second, pos2.first, pos2.second);
        fflush(stdout);
        return;
    } else {
        vector<pair<int, int>> answers;
        for (int x : odd_cols) {
            int l = -1, r = n - 1;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                if (m == -1) break;
                if (ask(x + 1, 1, x + 1, m + 1) & 1) {
                    r = m;
                } else {
                    l = m;
                }
            }
            if (ask(x + 1, r + 1, x + 1, r + 1) != 1) {
                l = -1, r = n - 1;
                while (r - l > 1) {
                    int m = (l + r) >> 1;
                    if (m == -1) break;
                    if (ask(x + 1, n - m, x + 1, n) & 1) {
                        r = m;
                    } else {
                        l = m;
                    }
                }
            }
            answers.emplace_back(x + 1, r + 1);
        }
        for (int x : odd_rows) {
            int l = -1, r = n - 1;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                if (m == -1) break;
                if (ask(1, x + 1, m + 1, x + 1) & 1) {
                    r = m;
                } else {
                    l = m;
                }
            }
            if (ask(r + 1, x + 1, r + 1, x + 1) != 1) {
                l = -1, r = n - 1;
                while (r - l > 1) {
                    int m = (l + r) >> 1;
                    if (m == -1) break;
                    if (ask(n - m, x + 1, n, x + 1) & 1) {
                        r = m;
                    } else {
                        l = m;
                    }
                }
            }
            answers.emplace_back(r + 1, x + 1);
        }
        debug(answers);
        if (answers.size() != 2) {
            cout << "-1\n";
            return;
        }
        printf("! %lld %lld %lld %lld\n", answers[0].first, answers[0].second, answers[1].first, answers[1].second);
        fflush(stdout);
        return;
    }
}

signed main() {
    solve();
}
