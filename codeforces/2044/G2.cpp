#include <bits/stdc++.h>
using namespace std;
#define int int64_t
vector<vector<int>> g, gT;
vector<int8_t> used;
vector<int> topsort;
vector<int> comp;
int timer = 1;
int compcolor = 1;
void topsortd(int x) {
    used[x] = 1;
    for (int u : g[x]) {
        if (!used[u]) {
            topsortd(u);
        }
    }
    topsort.push_back(x);
}
vector<int> tin, fup;
vector<int> st;
vector<int> compsize;
void compd(int x) {
    used[x] = true;
    fup[x] = tin[x] = timer++;
    st.push_back(x);
    for (int u : g[x]) {
        if (!used[u]) compd(u);
        if (!comp[u]) {
            fup[x] = min(fup[x], fup[u]);
        }
    }
    if (fup[x] == tin[x]) {
        int col = compcolor++;
        compsize.push_back(0);
        while (st.back() != x) {
            comp[st.back()] = col;
            compsize.back()++;
            st.pop_back();
        }
        comp[st.back()] = col;
        compsize.back()++;
        st.pop_back();
    }
}
void solve() {
    int n;
    cin >> n;
    timer = 1;
    compcolor = 1;
    topsort.clear();
    g.assign(n + 1, {});
    gT.assign(n + 1, {});
    tin.assign(n + 1, {});
    fup.assign(n + 1, {});
    comp.assign(n + 1, {});
    compsize.assign(1, 0);
    for (int i = 1; i <= n; ++i) {
        int r;
        cin >> r;
        g[i].push_back(r);
        gT[r].push_back(i);
    }
    used.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) topsortd(i);
    }
    reverse(topsort.begin(), topsort.end());
    used.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            compd(i);
        }
    }
    vector<int> need(n + 1, 1);
    vector<int> compneed(compcolor, 0);
    int answer = 0;
    for (int i : topsort) {
        if (compsize[comp[i]] == 1) {
            for (int j : gT[i]) {
                need[i] += need[j];
            }
        } else {
            for (int j : gT[i]) {
                if (compsize[comp[j]] == 1) {
                    compneed[comp[i]] = max(compneed[comp[i]], need[j]);
                }
            }
            answer = max(answer, compneed[comp[i]]);
        }
    }
    cout << answer + 2 << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}