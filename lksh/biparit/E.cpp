#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

struct Query {
    int minutes;
    int a, b, c, d;
};

vector<vector<int>> g;
vector<int> M;
vector<bool> used;

int n;

bool try_kuhn(int x) {
    if (used[x]) return false;
    used[x] = true;
    for (int b : g[x]) {
        if (M[b] == -1 || try_kuhn(M[b])) {
            M[b] = x;
            return true;
        }
    }
    return false;
}

void kuhn() {
    for (int i = 0; i < n; ++i) {
        used.assign(n, {});
        try_kuhn(i);
    }
}

void init() {
    g.assign(n, {});
    M.assign(n, -1);
}

void solve() {
    cin >> n;
    init();
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        string time;
        cin >> time;
        int minutes = 0;
        minutes += (time[0] - '0') * 10 * 60;
        minutes += (time[1] - '0') * 60;
        minutes += (time[3] - '0') * 10;
        minutes += (time[4] - '0');
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        queries[i] = {minutes, a, b, c, d};
    }
    int to_add = 0;
    for (int i = 0; i < n; ++i) {
        int added = queries[i].minutes + abs(queries[i].a - queries[i].c) +
                    abs(queries[i].b - queries[i].d);
        int cnt = 0;
        for (int j = i + 1; j < n; ++j) {
            int dest_time = added + abs(queries[i].c - queries[j].a) +
                            abs(queries[i].d - queries[j].b);
            if (dest_time <= queries[j].minutes - 1) {
                g[i].push_back(j);
                cnt++;
            }
        }
        if (!cnt) to_add++;
    }
    kuhn();
    int count = 0;
    for (int i = 0; i < n; ++i) {
        count += M[i] != -1;
    }
    cout << n - count << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
