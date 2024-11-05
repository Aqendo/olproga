#include "bits/stdc++.h"
using namespace std;

void solve() {
    string move;
    cin >> move;
    if (move == "Alice") {
        string s;
        cin >> s;
        int prev = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] - '0' >= prev) {
                for (int j = 0; j < (s[i] - '0') - prev; ++j) {
                    cout << i;
                }
                prev = s[i] - '0';
            } else {
                int j = 0;
                while ((prev + j++) % 11 != s[i] - '0') {
                    cout << i;
                }
                prev = s[i] - '0';
            }
            if (i == (int)s.size() - 1) {
                cout << i;
            }
        }
    } else {
        string s;
        cin >> s;
        vector<int> real;
        int prev = 0;
        int mx = *max_element(s.begin(), s.end()) - '0';
        for (int i = 0; i < mx; ++i) {
            int cnt = count(s.begin(), s.end(), i + '0');
            real.push_back((prev + cnt) % 11);
            prev = (prev + cnt) % 11;
        }
        int cnt = count(s.begin(), s.end(), mx + '0') - 1;
        real.push_back((prev + cnt) % 11);
        prev = (prev + cnt) % 11;
        for (int i : real) {
            cout << i;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}