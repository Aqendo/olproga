#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    string s = R"(

   16 24
   1 2
2 3
3 4
4 5
10 9
9 8
7 8
6 7
13 12
11 12
1 10
2 9
3 8
4 7
9 11
8 12
7 13
11 14
13 15
5 6
12 16
16 15
16 14
3 11

    )";
    stringstream ss(s);
    int n, m;
    ss >> n >> m;
    vector<vector<int>> g(n, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int a, b;
        ss >> a >> b;
        g[a - 1][b - 1] = 1;
        g[b - 1][a - 1] = 1;
    }
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << g[i][j];
        }
        cout << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
