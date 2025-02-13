#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 78, MOD = 998244353;
int add(int x, int y) { return (x + y) % MOD; }
int sub(int x, int y) { return ((x - y) % MOD + MOD) % MOD; }
int mult(int x, int y) { return 1ll * x * y % MOD; }

int a[N], pc[N], ps[2][N], c[N], F[N], pF[N];
struct Fenw {
    vector<int> tree;
    void init(vector<int> &a_) {
        tree.assign(a_.size(), {});
        for (int i = 0; i < (int)a_.size(); ++i) {
            add(i, a_[i]);
        }
    }
    void add(int i, int v) {
        for (; i < (int)tree.size(); i = i | (i + 1)) {
            tree[i] = ::add(tree[i], v);
        }
    }
    int get(int i) {
        return sub(get_(i), (i == 0 ? 0 : get_(i - 1)));
    }
    int get(int l, int r) {
        return sub(get_(r), (l == 0 ? 0 : get_(l - 1)));
    }
    int get_(int r) {
        int answer = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            answer = ::add(answer, tree[r]);
        }
        return answer;
    }
};
#define debug(x) cout << (#x) << ": " << x << endl
void solve() {
    string s_;
    cin >> s_;
    int n = s_.size();

    for (int i = 0; i < n; ++i) {
        a[i + 1] = s_[i] - '0';
    }
    vector<vector<int>> needed(2, vector<int>(n + 1));
    vector<vector<int>> s(2, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        pc[i] = pc[i - 1];
        pc[i] = pc[i - 1];
        ps[0][i] = ps[0][i - 1];
        ps[1][i] = ps[1][i - 1];

        c[i] = add(add(pc[i - 1], ps[1 - a[i]][i - 1]), 1);
        s[a[i]][i] = add(add(ps[a[i]][i - 1], ps[1 - a[i]][i - 1]), 1);

        pc[i] = add(pc[i], c[i]);
        ps[a[i]][i] = add(ps[a[i]][i], s[a[i]][i]);
        needed[a[i]][i] = pF[n - i];
    }
    // for (int i = 1; i <= n; ++i) {
    //     cout << c[i] << ' ';
    // }
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << s[0][i] << ' ';
    // }
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << s[1][i] << ' ';
    // }
    // cout << endl;

    // for (int i = 1; i <= n; ++i) {
    //     cout << needed[0][i] << ' ';
    // }
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << needed[1][i] << ' ';
    // }
    // cout << endl;

    Fenw fs[2];
    fs[0].init(s[0]);
    fs[1].init(s[1]);
    Fenw fneed[2];
    fneed[0].init(needed[0]);
    fneed[1].init(needed[1]);
    int answer = pc[n];
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int v;
        cin >> v;
        int todel = fs[1 - a[v]].get_(v - 1);
        int toadd = fs[a[v]].get_(v - 1);

        int sz = fs[a[v]].get(v);
        fs[a[v]].add(v, -sz);
        fs[1 - a[v]].add(v, sz);
        int amount = pF[n - v];

        answer = sub(answer, mult(todel, amount));
        answer = add(answer, mult(toadd, amount));
        int amountsub = mult(sz, fneed[1 - a[v]].get(v + 1, n));
        int amountadd = mult(sz, fneed[a[v]].get(v + 1, n));

        answer = sub(answer, amountsub);

        answer = add(answer, amountadd);
        int need = fneed[a[v]].get(v);
        fneed[a[v]].add(v, -need);
        fneed[1 - a[v]].add(v, +need);
        a[v] = 1 - a[v];
        cout << answer << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    F[0] = 1;
    F[1] = 1;
    pF[0] = 1;
    pF[1] = pF[0] + F[1];
    for (int i = 2; i < N; ++i) {
        F[i] = add(F[i - 1], F[i - 1]);
        pF[i] = add(pF[i - 1], F[i]);
    }
    int t = 1;
    cin >> t;
    while (t--) solve();
}
