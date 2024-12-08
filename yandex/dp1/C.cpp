#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<string>> dp(n, vector<string>(n, string(n + 1, 'Z')));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = s[i];
    }
    for (int size = 1; size <= n; ++size) {
        for (int l = 0; l + size - 1 < n; ++l) {
            int r = l + size - 1;
            // [l ... mid] [mid + 1 ... r]
            for (int mid = l; mid <= r - 1; ++mid) {
                if (dp[l][mid].size() + dp[mid + 1][r].size() < dp[l][r].size()) {
                    dp[l][r] = dp[l][mid] + dp[mid + 1][r];
                } else if (dp[l][mid].size() + dp[mid + 1][r].size() == dp[l][r].size()) {
                    dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r]);
                }
            }
            int len = r - l + 1;
            vector<int> factorization;
            for (int del = 1; del * del <= len; ++del) {
                if (len % del == 0) {
                    factorization.push_back(del);
                    if (len / del != del) {
                        factorization.push_back(len / del);
                    }
                }
            }
            for (int del : factorization) {
                vector<string> substrings;
                substrings.reserve(len / del);
                for (int start = l; start <= r; start += del) {
                    substrings.push_back(s.substr(start, del));
                }
                bool good = true;
                for (int i = 1; i < (int)substrings.size(); ++i) {
                    if (substrings[i] != substrings[i - 1]) {
                        good = false;
                        break;
                    }
                }
                if (good) {
                    if (to_string(substrings.size()).size() + 2 + dp[l][l + del - 1].size() <= dp[l][r].size()) {
                        string result = to_string(substrings.size()) + "(";
                        result += dp[l][l + del - 1];
                        result += ")";
                        if (result.size() < dp[l][r].size()) {
                            dp[l][r] = result;
                        } else {
                            dp[l][r] = min(dp[l][r], result);
                        }
                    }
                }
            }
        }
    }
    cout << dp[0][n - 1] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
