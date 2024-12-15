#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template <class K, class V>
using hash_big =
    gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>,
                  linear_probe_fn<>,
                  hash_standard_resize_policy<hash_exponential_size_policy<>,
                                              hash_load_check_resize_trigger<>, true>>;
vector<vector<int>> g;
vector<int> sizes;
vector<int> head;
vector<int> eulers;
vector<int> tin, tout, p;
int min(int x, int y) {
    return x < y ? x : y;
}
int max(int x, int y) {
    return x > y ? x : y;
}
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
        get_head(u);
    }
    tout[x] = timer;
}
vector<int> a;
struct Segtree {
    vector<hash_big<int, array<int, 2>>> tree;
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
        tree[x].resize(tree[x + 1].size() + tree[x + 2 * (m - lx + 1)].size());
        for (const auto &[u, v] : tree[x + 1]) {
            tree[x][u][0] += v[0];
            tree[x][u][1] += v[1];
        }
        for (const auto &[u, v] : tree[x + 2 * (m - lx + 1)]) {
            tree[x][u][0] += v[0];
            tree[x][u][1] += v[1];
        }
    }
    int get0(int x, int lx, int rx, int l, int r, int v) {
        if (l > r) return 0;
        if (l == lx && r == rx) return tree[x].find(v) != tree[x].end() ? tree[x][v][0] : 0;
        int m = (lx + rx) >> 1;
        int s1 = l <= min(m, r) ? get0(x + 1, lx, m, l, min(m, r), v) : 0;
        int s2 = max(m + 1, l) <= r ? get0(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, v) : 0;
        return s1 + s2;
    }
    int get1(int x, int lx, int rx, int l, int r, int v) {
        if (l > r) return 0;
        if (l == lx && r == rx) return tree[x].find(v) != tree[x].end() ? tree[x][v][1] : 0;
        int m = (lx + rx) >> 1;
        int s1 = l <= min(m, r) ? get1(x + 1, lx, m, l, min(m, r), v) : 0;
        int s2 = max(m + 1, l) <= r ? get1(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, v) : 0;
        return s1 + s2;
    }
    array<int, 4> change(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            array<int, 4> answer;
            answer[0] = lx + a[(*arr_)[lx]];
            answer[2] = lx - a[(*arr_)[lx]];
            tree[x][answer[0]][0] = 0;
            tree[x][answer[2]][1] = 0;
            a[(*arr_)[lx]] = v;
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
        offset += tin[aa] - tin[head[aa]] + 1;
        aa = p[head[aa]];
    }
    while (!is_ancestor(head[bb], aa)) {
        offset += tin[bb] - tin[head[bb]] + 1;
        bb = p[head[bb]];
    }
    return offset + (max(tin[aa], tin[bb]) - min(tin[aa], tin[bb]) + 1);
}

void get_up_left(int &aa, int &bb, int &ans, int &offset) {
    offset = 0;
    while (!is_ancestor(head[aa], bb)) {
        ans += st.get0(0, 0, eulers.size() - 1, tin[head[aa]], tin[aa], tin[aa] + offset);
        offset += tin[aa] - tin[head[aa]] + 1;
        aa = p[head[aa]];
    }
}
void get_up_right(int &aa, int &bb, int &ans, int &offset) {
    while (!is_ancestor(head[aa], bb)) {
        ans += st.get1(0, 0, eulers.size() - 1, tin[head[aa]], tin[aa], tin[aa] - offset);
        offset -= tin[aa] - tin[head[aa]] + 1;
        aa = p[head[aa]];
    }
}

vector<int> solve(int n, int q, vector<int> a_, vector<int> p_, vector<int> qt, vector<int> qx, vector<int> qy) {
    swap(a_, a);
    g.assign(n, {});
    sizes.assign(n, {});
    head.assign(n, {});
    tin.assign(n, {});
    tout.assign(n, {});
    swap(p, p_);
    int root = 0;
    for (int i = 0; i < n; ++i) {
        int pp = p[i];
        if (pp != -1) {
            g[pp].push_back(i);
        } else {
            root = i;
            p[i] = i;
        }
    }
    get_size(root);
    head[root] = root;
    get_head(root);
    st.init(eulers);
    vector<int> answer_;
    for (int i = 0; i < q; ++i) {
        int move = qt[i];
        if (move == 1) {
            int s = qx[i], x = qy[i];
            st.change(0, 0, eulers.size() - 1, tin[s], x);
        } else {
            int u = qx[i], v = qy[i];
            int len = get_up_count(u, v);
            int ans = 0;
            int offset = 0;
            get_up_left(u, v, ans, offset);
            int offset2 = len - 1;
            get_up_right(v, u, ans, offset2);
            if (tin[u] < tin[v]) {
                ans += st.get1(0, 0, eulers.size() - 1, tin[u], tin[v], tin[u] - offset);
            } else {
                ans += st.get0(0, 0, eulers.size() - 1, tin[v], tin[u], tin[u] + offset);
            }
            answer_.push_back(ans);
        }
    }
    return answer_;
}