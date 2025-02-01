#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int OPEN = 0, CLOSE = 1;

struct Event {
    int type;
    int x;
    int index;
};

const int N = 1e5 + 1;

int a[N], ar[N];

int n;

struct comp {
    bool operator()(int i, int j) const {
        return ar[i] > ar[j];
    }
};

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<array<vector<int>, 2>> events(n);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        ar[i] = r;
        events[l][OPEN].push_back(i);
        events[r][CLOSE].push_back(i);
    }
    multiset<int, comp> now;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j : events[i][OPEN]) {
            now.insert(j);
        }
        while ((int)now.size() > a[i]) {
            answer++;
            now.erase(now.begin());
        }
        for (int j : events[i][CLOSE]) {
            now.erase(j);
        }
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}