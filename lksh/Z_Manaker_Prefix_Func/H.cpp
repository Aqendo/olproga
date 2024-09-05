#include <random>
#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<int> manaker(vector<int>& s) {
    int l = 0, r = 0;
    vector<int> z(s.size());
    for (int i = 0; i <= s.size(); ++i) {
        z[i] = min(max(0, r - i), z[l + r - i]);
        while (z[i] <= i && i + z[i] < s.size() && s[i - z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (z[i] + i > r) {
            l = i - z[i];
            r = i + z[i];
        }
    }
    return z;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(2 * n + 1);
    for (int i = 0; i < n; ++i) {
        a[2 * i] = 0;
        cin >> a[2 * i + 1];
    }
    a.back() = 0;
    vector<int> man = manaker(a);
    vector<int> answer;
    for (int i = 0; i < (2 * n + 2) / 2; ++i) {
        if (a[i] == 0) {
            if (man[i] == i + 1 || man[i] == 2 * n + 1 - i) {
                answer.push_back((2 * n + 1 - i) / 2);
            }
        }
    }
    sort(answer.begin(), answer.end());
    for (int i : answer) cout << i << ' ';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
