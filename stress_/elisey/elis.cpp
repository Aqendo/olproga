#include <bits/stdc++.h>
#define int long long

using namespace std;

vector<vector<int>> arr;
bool ok = true;
int n;
string ans;

void go(int v) {
    ans[v % n] = char(v / n + '0');
    for (int to : arr[v]) {
        if (ans[to % n] == '2') {
            go(to);
        } else if (ans[to % n] - '0' != to / n) {
            ok = false;
        }
    }
}

void clear_it(int v) {
    ans[v % n] = '2';
    for (int to : arr[v]) {
        if (ans[to % n] != '2') {
            clear_it(to);
        }
    }
}

signed main() {
    int m;
    while (cin >> n >> m) {
        arr.clear();
        arr.resize(2 * n);
        ans = "";
        for (int i = 0; i < n; ++i) {
            ans += '2';
        }
        for (int i = 0; i < m; ++i) {
            int i1, i2, e1, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            arr[!e1 * n + i1].push_back(e2 * n + i2);
            arr[!e2 * n + i2].push_back(e1 * n + i1);
        }
        for (int i = 0; i < n; ++i) {
            if (ans[i] == '2') {
                ok = true;
                go(i);
                clear_it(i);
                if (!ok) {
                    go(n + i);
                } else {
                    go(i);
                }
            }
        }
        cout << ans << endl;
    }
}