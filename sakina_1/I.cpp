#include "bits/stdc++.h"
using namespace std;
#define int long long
#define double long double
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#else
#define debug(...)
#endif

#ifndef SEREGA
#define printf(...)
#endif
void solve() {
    string s;
    cin >> s;
    vector<char> before, after;
    map<char, char> rev = {{'}', '{'}, {')', '('}, {']', '['}};
    map<char, char> rev2 = {{'{', '}'}, {'(', ')'}, {'[', ']'}};

    for (char c : s) {
        if (c == '{' || c == '[' || c == '(') {
            after.push_back(c);
        } else {
            if (!after.empty()) {
                if (after.back() == rev[c]) {
                    after.pop_back();
                } else {
                    cout << "IMPOSSIBLE\n";
                    return;
                }
            } else {
                before.push_back(c);
            }
        }
    }
    for (int i = (int)(before.size()) - 1; i >= 0; --i) {
        cout << rev[before[i]];
    }
    cout << s;
    for (int i = (int)(after.size()) - 1; i >= 0; --i) {
        cout << rev2[after[i]];
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
