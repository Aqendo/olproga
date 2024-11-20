#include <bits/stdc++.h>

using namespace std;

constexpr int MAX_ARRAY_SIZE = 200000;
constexpr int THRESHOLD_TO_AVOID_OVERFLOW = 5;
constexpr int MAX_ARRAY_SIZE_WITH_THRESHOLD = MAX_ARRAY_SIZE + THRESHOLD_TO_AVOID_OVERFLOW;

int64_t lgg[MAX_ARRAY_SIZE_WITH_THRESHOLD];

struct Sparse {
    vector<vector<int64_t>> sparse_min, sparse_max;
    Sparse(vector<int64_t>& a) : sparse_min(__lg(a.size()) + 1, vector<int64_t>(a.size())), sparse_max(__lg(a.size()) + 1, vector<int64_t>(a.size())) {
        sparse_min[0] = a;
        sparse_max[0] = a;

        for (int64_t power = 1; power <= __lg(a.size()); ++power) {
            for (size_t i = 0; i < a.size(); ++i) {
                sparse_min[power][i] = sparse_min[power - 1][i];
                sparse_max[power][i] = sparse_max[power - 1][i];

                if (i + (1 << (power - 1)) < a.size()) {
                    sparse_min[power][i] = min(sparse_min[power][i], sparse_min[power - 1][i + (1 << (power - 1))]);

                    sparse_max[power][i] = max(sparse_max[power][i], sparse_max[power - 1][i + (1 << (power - 1))]);
                }
            }
        }
    }

    int64_t get_min(int64_t l, int64_t r) {
        int64_t lg_ = lgg[r - l + 1];
        int64_t res = sparse_min[lg_][l];
        if (r - (1 << lg_) + 1 < sparse_min[0].size()) {
            res = min(res, sparse_min[lg_][r - (1 << lg_) + 1]);
        }
        return res;
    }

    int64_t get_max(int64_t l, int64_t r) {
        int64_t lg_ = lgg[r - l + 1];
        int64_t res = sparse_max[lg_][l];
        if (r - (1 << lg_) + 1 < sparse_max[0].size()) {
            res = max(res, sparse_max[lg_][r - (1 << lg_) + 1]);
        }
        return res;
    }
};

void solve() {
    int64_t n;
    cin >> n;
    vector<int64_t> a(n), b(n);
    for (int64_t i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int64_t i = 0; i < n; ++i) {
        cin >> b[i];
    }

    Sparse mxs(a), mns(b);
    int64_t ans = 0;
    for (int64_t i = 0; i < n; ++i) {
        int64_t l = i, r = n;
        while (r - l > 1) {
            int64_t m = (l + r) >> 1;
            int64_t mn = mns.get_min(i, m);
            int64_t mx = mxs.get_max(i, m);
            if (mn >= mx) {
                l = m;
            } else {
                r = m;
            }
        }
        int64_t right_bound = l;
        l = i, r = n;
        while (r - l > 1) {
            int64_t m = (l + r) >> 1;
            int64_t mn = mns.get_min(i, m);
            int64_t mx = mxs.get_max(i, m);
            if (mn > mx) {
                l = m;
            } else {
                r = m;
            }
        }
        if (mns.get_min(i, l) == mxs.get_max(i, l)) l--;
        ans += right_bound - l;
    }
    cout << ans << '\n';
}

signed main() {
    lgg[1] = 0;
    for (int64_t i = 2; i < MAX_ARRAY_SIZE_WITH_THRESHOLD; ++i) {
        lgg[i] = lgg[i >> 1] + 1;
    }
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}