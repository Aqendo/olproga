#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int get_deg(string& s) {
    char f = s[0];
    char t = s.back();
    s.erase(0, 1);
    s.erase((int)s.size() - 1, 1);
    int answer = 0;
    int num = stoi(s);
    if (f == 'N') {
        if (t == 'E') {
            answer = (num + 360) % 360;
        } else {
            answer = (-num + 360) % 360;
        }
    } else if (f == 'S') {
        if (t == 'W') {
            answer = (180 + num + 360) % 360;
        } else {
            answer = (180 - num + 360) % 360;
        }
    } else if (f == 'W') {
        if (t == 'N') {
            answer = (270 + num + 360) % 360;
        } else {
            answer = (270 - num + 360) % 360;
        }
    } else {
        if (t == 'S') {
            answer = (90 + num + 360) % 360;
        } else {
            answer = (90 - num + 360) % 360;
        }
    }
    return answer;
}

void solve() {
    int n;
    cin >> n;
    vector<int> first_occurence(361, -1);
    vector<int> cnt(361, 0);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int answer = get_deg(s);
        if (first_occurence[answer] == -1) {
            first_occurence[answer] = i + 1;
        }
        cnt[answer]++;
    }
    int mx_index = 0;
    for (int i = 1; i <= 360; ++i) {
        if (cnt[mx_index] < cnt[i]) {
            mx_index = i;
        }
    }
    cout << first_occurence[mx_index] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}