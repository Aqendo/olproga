#ifndef SEREGA
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
using namespace std;
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto __freop = freopen(INPUT_PATH, "r", stdin);
#else
#define debug(...)
#endif
// #define int int64_t
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
vector<vector<int>> g;
vector<int> gT;
vector<vector<int>> conG;
vector<pair<int, int>> how_much_for_ended;
vector<vector<int>> comp_includes;
vector<int> used;
vector<int> comp, st, tin, dp, ended, is_end, pos_in_condensed;
vector<vector<int>> binup;
int n;
int timer = 0, next_color = 1;
void color_verticies(int x) {
    used[x] = 1;
    dp[x] = tin[x] = timer++;
    st.push_back(x);
    for (int u : g[x]) {
        if (!used[u]) {
            color_verticies(u);
        }
        if (!comp[u]) {
            dp[x] = min(dp[x], dp[u]);
        }

    }
    if (tin[x] == dp[x]) {
        int col = next_color++;
        int cnt = 0;
        while (st.back() != x) {
            comp[st.back()] = col;
            cnt++;
            st.pop_back();
        }
        // cout << x << endl;
        // debug("cnt", cnt, g[x]);
        if (cnt > 0 || (gT[x] == x)) {
            // cout << "good: " << x << endl;
            ended.push_back(col);
            is_end[col] = 1;
        }
        comp[st.back()] = col;
        st.pop_back();
    }
}

void condensed(int x) {
    used[x] = 1;
    for (int u : g[x]) {
        if (comp[x] != comp[u]) {
            conG[comp[x]].push_back(comp[u]);
        }
        if (!used[u]) {
            condensed(u);
        }
    }
}

void get_binup(int x, int p = -1) {
    // cout << "in binup: " << x << endl;
    used[x] = true;
    binup[x][0] = (p == -1 ? x : p);
    for (int power = 1; power <= 21; ++power) {
        binup[x][power] = binup[binup[x][power - 1]][power - 1];
    }
    for (int u : conG[x]) {
        if (!used[u]) {
            get_binup(u, x);
        }
    }
}
void get_how_much(int x) {
    if (is_end[x]) {
        how_much_for_ended[x] = {0, comp_includes[x][0]};
        return;
    }
    int old = x;
    int answer = 1;
    // cout << "in " << x << endl;
    for (int i = 21; i >= 0; --i) {
        if (!is_end[binup[x][i]]) {
            // cout << "to " << binup[x][i] << ' ' << endl;
            // cout << "can go up to 2^" << i << endl;
            answer += (1 << i);
            x = binup[x][i];
        }
    }
    // cout << "recieved in " << x << " with answer =" << answer << endl;
    // debug(comp_includes[x]);
    // debug(is_end);
    x = gT[comp_includes[x][0]];
    // debug("resulting in ", x);
    how_much_for_ended[old] = {answer, x};
}
void get_pos_condensed(int x, int index = 0) {
    used[x] = true;
    pos_in_condensed[x] = index;
    comp_includes[comp[x]].push_back(x);
    int u = gT[x];
    if (comp[u] != comp[x]) return;
    if (!used[u]) {
        get_pos_condensed(u, index + 1);
    }
}
void init() {
}
void solve() {
    cin >> n;
    init();
    g.assign(n + 1, {});
    gT.assign(n + 1, {});
    for (int i = 0; i < n; ++i) {
        int t; cin >> t;
        g[(i + t) % n].push_back(i);
        gT[i] = (i + t) % n;
    }
    // for (int i = 0; i < n; ++i) {
    //     for (int j : g[i]) {
    //         cout << i << ' ' << j << endl;
    //     }
    // }
    // cout << endl;
    used.assign(n + 1, {});
    comp.assign(n + 1, {});
    tin.assign(n + 1, {});
    dp.assign(n + 1, {});
    is_end.assign(n + 1, {});
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            color_verticies(i);
        }
    }
    tin.clear();
    dp.clear();
    conG.assign(next_color, {});
    used.assign(n + 1, {});
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            condensed(i);
        }
    }
    g.clear();

    // for (int i = 1; i < next_color; ++i) {
    //     for (int j : conG[i]) {
    //         cout << i << ' ' << j << endl;
    //     }
    // }
    binup.assign(next_color, vector<int> (22));
    used.assign(next_color, {});
    for (int i : ended) {
        if (!used[i]) {
            get_binup(i);
        }
    }
    used.assign(n + 1, {});
    comp_includes.assign(next_color, {});
    pos_in_condensed.assign(n + 1, {});
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            get_pos_condensed(i);
        }
    }
    how_much_for_ended.assign(next_color, {});
    for (int i = 1; i < next_color; ++i) {
        get_how_much(i);
    }
    int q; cin >> q;
    // cerr << "STARTED" << endl;
    for (int i = 0; i < q; ++i) {
        int s, k;
        cin >> s >> k;
        s--;
        // cout << "["<<s+1<<";"<<k<<"] started in " << comp[s] << endl;
        // debug("\nquery s =", s, "k =", k);
        // debug(comp);
        auto [how_many_before_cycle, what_would_be] = how_much_for_ended[comp[s]];
        if (comp[what_would_be] == comp[s]) {
            how_many_before_cycle = 0;
            what_would_be = s;
        }
        // cout << "how_many_before_cycle = " << how_many_before_cycle << ", what_would_be = " << what_would_be << endl;
        // cout << size_condensed[comp[what_would_be]] << endl;
        if (k >= how_many_before_cycle) {
            k -= how_many_before_cycle;
            int current_pos = pos_in_condensed[what_would_be];
            // cout << "first_pos = " << current_pos << endl;
            // debug(comp_includes[comp[what_would_be]]);
            current_pos += k;
            current_pos %= comp_includes[comp[what_would_be]].size();
            // cout << "end_pos = " << current_pos << endl;
            cout << comp_includes[comp[what_would_be]][current_pos] + 1 << ' ';
        } else {
            s = comp[s];
            for (int power = 21; power >= 0; --power) {
                if (k - (1 << power) >= 0) {
                    s = binup[s][power];
                    k -= (1 << power);
                }
            }
            cout << comp_includes[s][0] + 1 << ' ';
        }
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}