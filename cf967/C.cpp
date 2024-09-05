#include "bits/stdc++.h"
#define int long long

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
#else
#define debug(...)
#endif

map<pair<int, int>, int> cache;

int ask(int x, int y) {
    if (cache[{x, y}] != 0) {
        return cache[{x, y}];
    }
    cout << "? " << x << ' ' << y << endl;
    int answer;
    cin >> answer;
    cache[{x, y}] = answer;
    cache[{y, x}] = answer;
    return answer;
}
vector<pair<int, int>> answers;

constexpr int MAXN = 1003;

vector<bool> is_visited;
set<pair<int, int>> cache_solve_;
void solve_(int l, int r) {
    if (cache_solve_.contains({l, r})) return;
    cache_solve_.insert({l, r});
    int answer = ask(l, r);
    if (answer == l || answer == r) {
        answers.emplace_back(l, r);
        is_visited[l] = true;
        is_visited[r] = true;
        return;
    }
    // debug(l, answer, r);
    solve_(l, answer);
    solve_(answer, r);
}

void solve() {
    int n;
    cin >> n;
    is_visited.assign(n + 1, false);
    cache_solve_.clear();
    answers.clear();
    cache.clear();
    solve_(1, n);
    for (int i = 2; i <= n; ++i) {
        if (!is_visited[i]) {
            solve_(1, i);
        }
    }
    map<pair<int, int>, bool> already;
    // debug(answers);
    cout << "! ";
    for (auto [u, v] : answers) {
        cout << u << ' ' << v << ' ';
    }
    cout << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
