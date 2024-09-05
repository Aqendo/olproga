#include "bits/stdc++.h"

using namespace std;
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    bool is_number = false;
    int current_number = 0;
    char current_char = ' ';
    vector<pair<char, int>> input;
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if ('0' <= c && c <= '9') {
            current_number = current_number * 10 + (c - '0');
        } else {
            if (current_char != ' ') {
                input.emplace_back(current_char, current_number);
            }
            if ('A' <= c && c <= 'Z') {
                current_char = c;
            }
            c = s[++i];
            current_number = c - '0';
            is_number = true;
        }
    }
    input.emplace_back(current_char, current_number);
    int cnt = 0;
    for (int i = 1; i < input.size(); ++i) {
        if (input[i].first == input[i - 1].first) {
            input[i].second += input[i - 1].second;
            input[i - 1].second = 0;
            cnt++;
        }
    }
    vector<pair<char, int>> new_input;
    new_input.reserve((int)input.size() - cnt);
    for (int i = 0; i < input.size(); ++i) {
        if (input[i].second) {
            new_input.push_back(input[i]);
        }
    }
    swap(input, new_input);
    new_input.clear();
    int K;
    cin >> K;
    int n = input.size();
    debug(input);
    vector<vector<vector<int>>> dp(n, vector(n, vector(K + 1, int(0))));
    for (int l = 0; l < n - 1; ++l) {
        if (input[l].first == 'C' && input[l + 1].first == 'G' ||
            input[l].first == 'G' && input[l + 1].first == 'C') {
            for (int k = 1;
                 k <= K && k <= min(input[l].second, input[l + 1].second);
                 ++k) {
                debug(l, l + 1, k, "=", k);
                dp[l][l + 1][k] = k;
            }
        } else if (input[l].first == 'A' && input[l + 1].first == 'U' ||
                   input[l].first == 'U' && input[l + 1].first == 'A') {
            debug(l, l + 1, 0, "=", min(input[l].second, input[l + 1].second));
            dp[l][l + 1][0] = min(input[l].second, input[l + 1].second);
        }
    }
    for (int len = 3; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            for (int i = l + 1; i <= r - 1; ++i) {
                for (int k = 0; k <= K; ++k) {
                    for (int next_k = 0; next_k + k <= K; ++next_k) {
                        debug(l, r, k + next_k, "=", i,
                              max(dp[l][r][k + next_k],
                                  dp[l][i][k] + dp[i + 1][r][next_k]));
                        dp[l][r][k + next_k] =
                            max(dp[l][r][k + next_k],
                                dp[l][i][k] + dp[i + 1][r][next_k]);
                    }
                }
            }
            for (int k = 0; k <= K; ++k) {
                if (input[l].first == 'C' && input[r].first == 'G' ||
                    input[l].first == 'G' && input[r].first == 'C') {
                    for (int add_k = 0;
                         add_k + k <= K &&
                         add_k <= min(input[l].second, input[r].second);
                         ++add_k) {
                        debug(l, r, k + add_k, "=",
                              max(dp[l][r][k + add_k],
                                  dp[l + 1][r - 1][k] + add_k));
                        dp[l][r][k + add_k] = max(dp[l][r][k + add_k],
                                                  dp[l + 1][r - 1][k] + add_k);
                    }
                } else if (input[l].first == 'A' && input[r].first == 'U' ||
                           input[l].first == 'A' && input[r].first == 'U') {
                    debug(l, r, k, "=",
                          max(dp[l][r][k],
                              dp[l + 1][r - 1][k] +
                                  min(input[l].second, input[r].second)));
                    dp[l][r][k] = max(
                        dp[l][r][k], dp[l + 1][r - 1][k] +
                                         min(input[l].second, input[r].second));
                }
            }
        }
    }
    int mx = INT_MIN;
    for (int k = 0; k <= K; ++k) {
        mx = max(mx, dp[0][n - 1][k]);
    }
    cout << mx << '\n';
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case " << i << ": ";
        solve();
    }
}
