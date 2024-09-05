#include "bits/stdc++.h"
#define int long long

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
#endif
struct Node {
    int mx, mn, mx_index, mn_index;
};
string to_string(const Node& n) {
    string s = "(mn=(" + to_string(n.mn) + ";" + to_string(n.mn_index) + "), mx=(" + to_string(n.mx) + ";" + to_string(n.mx_index) + "))";
    return s;
}
const Node null = {.mx = INT_MIN, .mn = INT_MAX, .mx_index = 0, .mn_index = 0};
struct Segtree {
    vector<Node> tree;
    int n;
    Node combine(Node s1, Node s2) {
        Node res;
        if (s1.mn < s2.mn) {
            res.mn = s1.mn;
            res.mn_index = s1.mn_index;
        } else {
            res.mn = s2.mn;
            res.mn_index = s2.mn_index;
        }
        if (s1.mx > s2.mx) {
            res.mx = s1.mx;
            res.mx_index = s1.mx_index;
        } else {
            res.mx = s2.mx;
            res.mx_index = s2.mx_index;
        }
        return res;
    }
    Segtree(vector<int>& a) : tree(4 * a.size()), n(a.size()) {
        for (int i = 0; i < 4 * a.size(); ++i) {
            tree[i] = null;
        }
        build(a, 1, 0, n - 1);
    }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = {a[lx], a[lx], lx, lx};
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
    Node get(int x, int lx, int rx, int l, int r) {
        // debug(tree[x], lx, rx);
        if (l > r) return null;
        if (lx == l && rx == r) {
            return tree[x];
        }
        int m = (lx + rx) >> 1;
        Node s1 = get(x << 1, lx, m, l, min(r, m));
        Node s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return combine(s1, s2);
    }
    void set(int x, int lx, int rx, int i, Node v) {
        if (lx == rx) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            set(x << 1, lx, m, i, v);
        } else {
            set(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
};

string to_string(Segtree& seg) {
    string res;
    for (int i = 0; i < seg.n; ++i) {
        res += to_string(seg.get(1, 0, seg.n - 1, i, i)) + ' ';
    }
    return res;
}

int c = 0;

vector<int> solve_fast(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> indexes(n + 1);
    vector<int> last_index(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        indexes[a[i]].push_back(i);
        last_index[a[i]] = i;
    }
    set<int> index;
    for (int i = 0; i <= n; ++i) {
        if (last_index[i] != -1) {
            index.insert(last_index[i]);
        }
    }
    bool searching_max = true;
    Segtree seg(a);
    vector<int> answer;
    for (int i = 0; i < n; ++i) {
        while (!index.empty() && i > *index.begin()) {
            index.erase(index.begin());
        }
        if (index.empty()) break;
        int last_index_now = *index.begin();
        Node ans = seg.get(1, 0, n - 1, i, last_index_now);
        int answer_index = searching_max ? ans.mx_index : ans.mn_index;
        answer.push_back(a[answer_index]);
        bool already_set = false;
        for (int d : indexes[a[answer_index]]) {
            if (!already_set) {
                if (d >= i) {
                    i = d;
                    already_set = true;
                }
            }
            seg.set(1, 0, n - 1, d, null);
        }
        searching_max = !searching_max;
        index.erase(last_index[a[answer_index]]);
    }
    return answer;
}

vector<int> solve_slow(vector<int>& a) {
    int n = a.size();
    vector<int> cnt(n + 1, {});
    vector<int> cnt_full(n + 1, {});

    vector<bool> is_used(n + 1);
    for (int i = 0; i < n; ++i) {
        cnt[a[i]]++;
        cnt_full[a[i]]++;
    }
    bool searching_max = true;
    int start = 0;
    vector<int> answer;
    for (int i = 0; i < n; ++i) {
        // cout << "iterating over a[" << i << "]: " << a[i] << '\n';
        if (!is_used[a[i]] && cnt[a[i]] == 1) {
            // cout << "found that !is_used && cnt == 1\n";
            int index_result = -1;
            for (int j = start; j <= i; ++j) {
                if (!is_used[a[j]]) {
                    if (searching_max) {
                        if (index_result == -1 || a[j] > a[index_result]) {
                            index_result = j;
                        }
                    } else {
                        if (index_result == -1 || a[j] < a[index_result]) {
                            index_result = j;
                        }
                    }
                }
            }
            // cout << "index_result is " << index_result << '\n';
            answer.push_back(a[index_result]);
            // debug(index_result + 1, i);
            for (int j = index_result + 1; j < i; ++j) {
                cnt[a[j]]++;
            }
            // debug(is_used);
            // debug(cnt);
            searching_max = !searching_max;
            i = index_result;
            is_used[a[index_result]] = true;
            start = index_result + 1;
        } else {
            cnt[a[i]]--;
        }
    }
    return answer;
}
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        int n = uid(3, 15);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = uid(1, n);
        }
        vector<int> slow = solve_slow(a);
        vector<int> fast = solve_fast(a);
        if (slow != fast) {
            cout << n << '\n';
            for (int i : a) cout << i << ' ';
            cout << '\n';
            debug(slow);
            debug(fast);
            return 0;
        }
    }
}
