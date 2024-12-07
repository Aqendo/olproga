#include <bits/stdc++.h>
using namespace std;

int solve(int n, int t, vector<int> r, vector<int> c, vector<int> v) {
    vector<vector<int>> vals(2 * n + 2);
    for (int i = 0; i < t; ++i) {
        if (r[i] + c[i] - v[i] >= 0) {
            vals[r[i] + c[i] - v[i]].push_back(v[i]);
        }
    }
    for (auto &vv : vals) {
        if (!vv.empty()) sort(vv.begin(), vv.end());
    }
    int answer = INT_MAX;
    for (int k = 1; k < 2 * n + 2; ++k) {
        int cnt_good = 0;
        for (int start = 0; start < 2 * n + 2; start += k) {
            auto it = lower_bound(vals[start].begin(), vals[start].end(), k);
            cnt_good += it - vals[start].begin();
        }
        answer = min(answer, t - cnt_good);
    }
    return answer;
}