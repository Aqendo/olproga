#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
#define int int64_t
// first - weight
// second - cost
int n, x;
int answer = 1e18;
bool check(int max_delta, const vector<pair<int, int>>& a, const vector<pair<int, int>>& b, const vector<pair<int, int>>& c) {
    deque<int> db, dc;
    int lb = 0, rb = -1;
    int lc = 0, rc = -1;
    for (int i = 0; i < n; ++i) {
        while ((int)b.size() > rb + 1 && b[rb + 1].first <= a[i].first) {
            while (!db.empty() && b[db.back()].second > b[rb + 1].second) {
                db.pop_back();
            }
            db.push_back(rb + 1);
            rb++;
        }
        while ((int)b.size() > lb && b[lb].first < a[i].first - max_delta) {
            if (!db.empty() && db.front() <= lb) {
                db.pop_front();
            }
            lb++;
        }
        while ((int)c.size() > rc + 1 && c[rc + 1].first <= a[i].first) {
            while (!dc.empty() && c[dc.back()].second > c[rc + 1].second) {
                dc.pop_back();
            }
            dc.push_back(rc + 1);
            rc++;
        }
        while ((int)c.size() > lc && c[lc].first < a[i].first - max_delta) {
            if (!dc.empty() && dc.front() <= lc) {
                dc.pop_front();
            }
            lc++;
        }
        if (db.empty() || dc.empty()) continue;
        int a1 = b[db.front()].second;
        int a2 = c[dc.front()].second;
        if (a[i].second + a1 + a2 <= x) {
            answer = min(answer, max_delta);
            return true;
        }
    }
    return false;
}
void solve(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b, const vector<pair<int, int>>& c) {
    int l = -1, r = 4e9;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (check(mid, a, b, c)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    check(r, a, b, c);
}

void solve() {
    cin >> n >> x;
    vector<pair<int, int>> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i].second;
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i].second;
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i].second;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    solve(a, b, c);
    solve(b, a, c);
    solve(c, b, a);
    cout << (answer == 1e18 ? -1 : answer) << '\n';
};

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}