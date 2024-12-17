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
struct Fenw {
    vector<hash_big<int, array<int, 2>>> fenw;
    void init() {
        fenw.assign(eulers.size(), {});
        for (int i = 0; i < eulers.size(); ++i) {
            fenw[i].resize(2 * (i - (i & (i + 1)) + 1));
            for (int index = i; index >= (i & (i + 1)); --index) {
                fenw[i][index + a[eulers[index]]][0]++;
                fenw[i][index - a[eulers[index]]][1]++;
            }
        }
    }
    int get0_(int r, int v) {
        int answer = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            answer += fenw[r].find(v) != fenw[r].end() ? fenw[r][v][0] : 0;
        }
        return answer;
    }
    int get0(int l, int r, int v) {
        return get0_(r, v) - (l != 0 ? get0_(l - 1, v) : 0);
    }
    int get1_(int r, int v) {
        int answer = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            answer += fenw[r].find(v) != fenw[r].end() ? fenw[r][v][1] : 0;
        }
        return answer;
    }
    int get1(int l, int r, int v) {
        return get1_(r, v) - (l != 0 ? get1_(l - 1, v) : 0);
    }
    void change(int i, int v) {
        int from0 = i + a[eulers[i]];
        int from1 = i - a[eulers[i]];
        int to0 = i + v;
        int to1 = i - v;
        a[eulers[i]] = v;
        for (; i < eulers.size(); i = i | (i + 1)) {
            fenw[i][from0][0]--;
            fenw[i][from1][1]--;
            fenw[i][to0][0]++;
            fenw[i][to1][1]++;
        }
    }
};

bool is_ancestor(int aa, int bb) {
    return tin[aa] <= tin[bb] && tin[bb] < tout[aa];
}

Fenw st;

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
        ans += st.get0(tin[head[aa]], tin[aa], tin[aa] + offset);
        offset += tin[aa] - tin[head[aa]] + 1;
        aa = p[head[aa]];
    }
}
void get_up_right(int &aa, int &bb, int &ans, int &offset) {
    while (!is_ancestor(head[aa], bb)) {
        ans += st.get1(tin[head[aa]], tin[aa], tin[aa] - offset);
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
    st.init();
    vector<int> answer_;
    for (int i = 0; i < q; ++i) {
        int move = qt[i];
        if (move == 1) {
            int s = qx[i], x = qy[i];
            st.change(tin[s], x);
        } else {
            int u = qx[i], v = qy[i];
            int len = get_up_count(u, v);
            int ans = 0;
            int offset = 0;
            get_up_left(u, v, ans, offset);
            int offset2 = len - 1;
            get_up_right(v, u, ans, offset2);
            if (tin[u] < tin[v]) {
                ans += st.get1(tin[u], tin[v], tin[u] - offset);
            } else {
                ans += st.get0(tin[v], tin[u], tin[u] + offset);
            }
            answer_.push_back(ans);
        }
    }
    return answer_;
}