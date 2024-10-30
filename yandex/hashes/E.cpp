#include "bits/stdc++.h"
using namespace std;

int get_hash(const string& s) {
    int h = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        h = (h * 31 + (int)s[i]);
    }
    return h;
}

void solve() {
    int k;
    cin >> k;
    string s(k, 'a');
    int cnt = 0;
    cout << s << endl;
    cnt++;
    // zz[0] += (char)1;
    // zz[1] -= (char)31;
    for (int i = 0; i < (int)s.size() - 1; ++i) {
        s[i] += 1;
        s[i + 1] -= 31;
        cnt++;
        cout << s << endl;
        // cout << get_hash(s) << endl;
    }
    // cout << cnt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
