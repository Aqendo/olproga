#include <iterator>
#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

int next_pair_index = 1;

vector<multiset<int>> g = {{}};
vector<multiset<int>> gT = {{}};

vector<int> order;

map<pair<char, char>, int> pair_to_int;
map<int, pair<char, char>> int_to_pair;

void dfs(int x) {
    while (!g[x].empty()) {
        int u = *g[x].begin();
        g[x].extract(u);
        dfs(u);
    }
    order.push_back(x);
}

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        pair<char, char> pref = {s[0], s[1]};
        pair<char, char> suff = {s[1], s[2]};
        if (!pair_to_int[pref]) {
            pair_to_int[pref] = next_pair_index++;
            int_to_pair[next_pair_index - 1] = pref;
            g.push_back({});
            gT.push_back({});
        }
        if (!pair_to_int[suff]) {
            pair_to_int[suff] = next_pair_index++;
            int_to_pair[next_pair_index - 1] = suff;
            g.push_back({});
            gT.push_back({});
        }
        g[pair_to_int[pref]].insert(pair_to_int[suff]);
        gT[pair_to_int[suff]].insert(pair_to_int[pref]);
    }
    int cnt_same = 0;
    vector<int> cnt_inbigger;
    vector<int> cnt_outbigger;
    for (int i = 1; i <= next_pair_index - 1; ++i) {
        if (g[i].size() == gT[i].size()) {
            cnt_same++;
        } else if (g[i].size() == gT[i].size() - 1) {
            cnt_outbigger.push_back(i);
        } else if (g[i].size() - 1 == gT[i].size()) {
            cnt_inbigger.push_back(i);
        } else {
            cout << "NO\n";
            return;
        }
    }
    if (cnt_inbigger.size() > 1 || cnt_outbigger.size() > 1) {
        cout << "NO\n";
        return;
    }
    if (cnt_inbigger.empty()) {
        cnt_inbigger.push_back(1);
    }
    dfs(cnt_inbigger.front());
    for (int i = 1; i <= next_pair_index - 1; ++i) {
        if (!g[i].empty()) {
            cout << "NO\n";
            return;
        }
    }
    reverse(order.begin(), order.end());
    cout << "YES\n";
    cout << int_to_pair[order.front()].first;
    for (int i : order) {
        cout << int_to_pair[i].second;
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
