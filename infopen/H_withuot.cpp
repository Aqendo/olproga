#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> sizes;
vector<int> head;
vector<int> eulers;
vector<int> tin, tout, p;
void get_size(int x, int par = -1) {
    sizes[x] = 1;
    for (int &u : g[x]) {
        get_size(u, x);
        sizes[x] += sizes[u];
        if (sizes[u] > sizes[g[x][0]]) {
            swap(u, g[x][0]);
        }
    }
}
int timer = 0;
void get_head(int x) {
    tin[x] = timer++;
    eulers.push_back(x);
    for (int u : g[x]) {
        head[u] = u == g[x][0] ? head[x] : u;
        // cout << "head[" << u << "]: " << head[u] << endl;
        get_head(u);
    }
    tout[x] = timer;
}
vector<int> a;
struct Segtree {
    vector<map<int, int[2]>> tree;
    vector<int> *arr_;
    void init(vector<int> &arr) {
        tree.assign(2 * arr.size() - 1, {});
        build(arr, 0, 0, arr.size() - 1);
        arr_ = &arr;
    }
    void build(vector<int> &arr, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x][lx + a[arr[lx]]][0] = 1;
            tree[x][lx - a[arr[lx]]][1] = 1;
            return;
        }
        int m = (lx + rx) >> 1;
        build(arr, x + 1, lx, m);
        build(arr, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = tree[x + 1];
        for (const auto &[u, v] : tree[x + 2 * (m - lx + 1)]) {
            tree[x][u][0] += v[0];
            tree[x][u][1] += v[1];
        }
    }
    int get0(int x, int lx, int rx, int l, int r, int v) {
        if (l > r) return 0;
        if (l == lx && r == rx) return tree[x].contains(v) ? tree[x][v][0] : 0;
        int m = (lx + rx) >> 1;
        int s1 = get0(x + 1, lx, m, l, min(m, r), v);
        int s2 = get0(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, v);
        return s1 + s2;
    }
    int get1(int x, int lx, int rx, int l, int r, int v) {
        if (l > r) return 0;
        if (l == lx && r == rx) return tree[x].contains(v) ? tree[x][v][1] : 0;
        int m = (lx + rx) >> 1;
        int s1 = get1(x + 1, lx, m, l, min(m, r), v);
        int s2 = get1(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, v);
        return s1 + s2;
    }
    array<int, 4> change(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            array<int, 4> answer;
            answer[0] = lx + a[(*arr_)[lx]];
            answer[2] = lx - a[(*arr_)[lx]];
            tree[x][answer[0]][0] = 0;
            tree[x][answer[2]][1] = 0;
            (*arr_)[lx] = v;
            answer[1] = lx + a[(*arr_)[lx]];
            answer[3] = lx - a[(*arr_)[lx]];
            tree[x][answer[1]][0] = 1;
            tree[x][answer[3]][1] = 1;
            return answer;
        }
        int m = (lx + rx) >> 1;
        array<int, 4> answer;
        if (i <= m) {
            answer = change(x + 1, lx, m, i, v);
        } else {
            answer = change(x + 2 * (m - lx + 1), m + 1, rx, i, v);
        }
        tree[x][answer[0]][0]--;
        tree[x][answer[2]][1]--;
        tree[x][answer[1]][0]++;
        tree[x][answer[3]][1]++;
        return answer;
    }
};

bool is_ancestor(int aa, int bb) {
    return tin[aa] <= tin[bb] && tin[bb] < tout[aa];
}

Segtree st;

int get_up_count(int aa, int bb) {
    int offset = 0;
    while (!is_ancestor(head[aa], bb)) {
        // for (int i = tin[aa]; i >= tin[head[aa]]; --i) {
        //     cerr << eulers[i] << ' ';
        // }
        offset += tin[aa] - tin[head[aa]] + 1;
        aa = p[head[aa]];
    }
    while (!is_ancestor(head[bb], aa)) {
        // for (int i = tin[aa]; i >= tin[head[aa]]; --i) {
        //     cerr << eulers[i] << ' ';
        // }
        offset += tin[bb] - tin[head[bb]] + 1;
        bb = p[head[bb]];
    }
    return offset + (max(tin[aa], tin[bb]) - min(tin[aa], tin[bb]) + 1);
}

void get_up_left(int &aa, int &bb, int &ans, int &offset) {
    offset = 0;
    while (!is_ancestor(head[aa], bb)) {
        // for (int i = tin[aa]; i >= tin[head[aa]]; --i) {
        //     cout << eulers[i] << ' ' << i << ' ' << a[eulers[i]] << ' ' << i + a[eulers[i]] << endl;
        // }
        ans += st.get0(0, 0, eulers.size() - 1, tin[head[aa]], tin[aa], tin[aa] + offset);
        offset += tin[aa] - tin[head[aa]] + 1;
        aa = p[head[aa]];
    }
}
void get_up_right(int &aa, int &bb, int &ans, int &offset) {
    while (!is_ancestor(head[aa], bb)) {
        // for (int i = tin[aa]; i >= tin[head[aa]]; --i) {
        //     cout << eulers[i] << ' ' << i << ' ' << a[eulers[i]] << ' ' << i - a[eulers[i]] << endl;
        // }
        ans += st.get1(0, 0, eulers.size() - 1, tin[head[aa]], tin[aa], tin[aa] - offset);
        offset -= tin[aa] - tin[head[aa]] + 1;
        aa = p[head[aa]];
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    g.assign(n, {});
    sizes.assign(n, {});
    head.assign(n, {});
    tin.assign(n, {});
    tout.assign(n, {});
    a.assign(n, {});
    p.assign(n, {});
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int root = 0;
    for (int i = 0; i < n; ++i) {
        int pp;
        cin >> pp;
        if (pp != -1) {
            g[pp].push_back(i);
            p[i] = pp;
        } else {
            root = i;
            p[i] = i;
        }
    }
    get_size(root);
    head[root] = root;
    get_head(root);
    st.init(eulers);
    // for (int i = 0; i < eulers.size(); ++i) {
    //     cout << eulers[i] << ' ';
    // }
    // cout << endl;
    // for (int i = 0; i < eulers.size(); ++i) {
    //     cout << i + a[eulers[i]] << ' ';
    // }
    // cout << endl;
    for (int i = 0; i < q; ++i) {
        int move;
        cin >> move;
        if (move == 1) {
            int s, x;
            cin >> s >> x;
            st.change(0, 0, eulers.size() - 1, tin[s], x);
        } else {
            int u, v;
            cin >> u >> v;
            int len = get_up_count(u, v);
            // cout << "LEN: " << len << endl;
            int ans = 0;
            int offset = 0;
            get_up_left(u, v, ans, offset);
            // cout << "ans1: " << ans << endl;
            int offset2 = len - 1;
            get_up_right(v, u, ans, offset2);
            // cout << "ans2: " << ans << endl;
            if (tin[u] < tin[v]) {
                // for (int j = tin[u]; j <= tin[v]; ++j) {
                //     cout << eulers[j] << ' ' << j << ' ' << a[eulers[j]] << ' ' << j - a[eulers[j]] << endl;
                // }
                // cout << tin[u] - offset << endl;
                ans += st.get1(0, 0, eulers.size() - 1, tin[u], tin[v], tin[u] - offset);
            } else {
                // for (int j = tin[v]; j <= tin[u]; ++j) {
                //     cout << eulers[j] << ' ' << j << ' ' << a[eulers[j]] << ' ' << j + a[eulers[j]] << endl;
                // }
                // cout << tin[u] + offset << endl;
                ans += st.get0(0, 0, eulers.size() - 1, tin[v], tin[u], tin[u] + offset);
            }

            // cout << "ans3:  " << ans << endl;
            // for (int ii = min(tin[u], tin[v]); ii <= max(tin[u], tin[v]); ++ii) {
            //     cerr << eulers[ii] << ' ';
            // }
            // cerr << "\nEND\n";
            cout << ans << endl;
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}