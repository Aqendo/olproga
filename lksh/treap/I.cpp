#ifdef SEREGA
#define _LIBCPP_ENABLE_DEBUG_MODE 2
#include "../debug.cpp"
#include "bits/stdc++.h"
#else
#include "bits/stdc++.h"
#endif

using namespace std;

#ifdef SEREGA
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

constexpr int INF = 1e9;
constexpr int MOD = 1e9;

mt19937 rng(42);

struct Node {
    int key;
    int priority;
    int sz = 1;
    Node* parent;
    int mn;
    bool rev = false;
    int64_t sum;

    Node(int x) : key(x), priority(rng()), sum(x), mn(key), parent(nullptr) {}

    Node *l, *r;
};

Node* root;

bool exists(Node* v, int x) {
    if (!v) return false;
    if (v->key == x) return true;
    if (v->key < x) return exists(v->r, x);
    return exists(v->l, x);
}

int get_sz(Node* v) {
    return v ? v->sz : 0;
}

int64_t get_sum(Node* v) {
    return v ? v->sum : 0;
}

int get_min_node(Node* v) {
    return v ? v->mn : INF;
}

void upd(Node* v) {
    if (!v) return;
    v->sz = get_sz(v->l) + get_sz(v->r) + 1;
    v->sum = get_sum(v->l) + get_sum(v->r) + v->key;
    v->mn = min({get_min_node(v->l), get_min_node(v->r), v->key});
    if (v->r) v->r->parent = v;
    if (v->l) v->l->parent = v;
}

void push(Node* x) {
    if (!x) return;
    if (x->rev) {
        swap(x->l, x->r);
        if (x->l) x->l->rev ^= 1;
        if (x->r) x->r->rev ^= 1;
        x->rev = false;
    }
}

// <, >=
pair<Node*, Node*> split(Node* v, int x) {
    if (!v) return {nullptr, nullptr};
    push(v);
    if (x <= v->key) {
        auto tmp = split(v->l, x);
        v->l = tmp.second;
        upd(v);
        return {tmp.first, v};
    } else {
        auto tmp = split(v->r, x);
        v->r = tmp.first;
        upd(v);
        return {v, tmp.second};
    }
}

void print(Node* v) {
    if (!v) return;
    push(v);
    print(v->l);
    //    cout << v->key << '(' << v->sz << ", rev=" << v->rev << ")" << ' ';
    cout << v->key << ' ';
    print(v->r);
}

Node* merge(Node* l, Node* r) {
    push(l);
    push(r);
    if (!l) return r;
    if (!r) return l;
    if (l->priority > r->priority) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
    r->l = merge(l, r->l);
    upd(r);
    return r;
}

int64_t get_sum_range(int l, int r) {
    auto tmp = split(root, l);
    auto tmp2 = split(tmp.second, r + 1);
    int64_t ans = get_sum(tmp2.first);
    root = merge(tmp.first, merge(tmp2.first, tmp2.second));
    return ans;
}

void insert(int x) {
    if (exists(root, x)) return;
    auto tmp = split(root, x);
    root = merge(tmp.first, merge(new Node(x),
                                  tmp.second));  // тут немного не так
}

void erase(int x) {
    if (!exists(root, x)) return;
    auto tmp = split(root, x);
    // <x , >= x
    auto tmp2 = split(tmp.second, x + 1);
    delete tmp2.first;
    root = merge(tmp.first, tmp2.second);
}

Node* get_max(Node* v) {
    if (!v) return nullptr;
    if (!v->r) return v;
    return get_max(v->r);
}

Node* get_min(Node* v) {
    if (!v) return nullptr;
    if (!v->l) return v;
    return get_min(v->l);
}

int next(Node* v, int x) {
    auto tmp = split(root, x + 1);
    Node* ans = get_min(tmp.second);
    merge(tmp.first, tmp.second);
    if (!ans) return INF;
    return ans->key;
}

int prev(Node* v, int x) {
    auto tmp = split(root, x);
    Node* ans = get_max(tmp.first);
    merge(tmp.first, tmp.second);
    if (!ans) return -INF;
    return ans->key;
}

int get_kth(Node* v, int k) {
    push(v);
    if (k > root->sz) return -INF;
    if (!v) return -INF;
    int lsz = get_sz(v->l);
    if (lsz + 1 == k) return v->key;
    if (lsz >= k) {
        return get_kth(v->l, k);
    } else {
        return get_kth(v->r, k - lsz - 1);
    }
}

// <, >=
pair<Node*, Node*> split_sz(Node* v, int x) {
    push(v);
    if (!v) return {nullptr, nullptr};
    if (get_sz(v->l) + 1 > x) {
        auto tmp = split_sz(v->l, x);
        v->l = tmp.second;
        if (tmp.first) tmp.first->parent = nullptr;
        upd(v);
        return {tmp.first, v};
    } else {
        auto tmp = split_sz(v->r, x - get_sz(v->l) - 1);
        v->r = tmp.first;
        if (tmp.second) tmp.second->parent = nullptr;
        upd(v);
        return {v, tmp.second};
    }
}

void to_start(int l, int r) {
    auto tmp = split_sz(root, l - 1);
    auto tmp2 = split_sz(tmp.second, r - l + 1);
    root = merge(tmp2.first, merge(tmp.first, tmp2.second));
}

void reverse(int l, int r) {
    auto tmp = split_sz(root, l - 1);
    auto tmp2 = split_sz(tmp.second, r - l + 1);
    if (tmp2.first) {
        tmp2.first->rev ^= 1;
    }
    root = merge(tmp.first, merge(tmp2.first, tmp2.second));
}

int64_t get_min_range(int l, int r) {
    auto tmp = split_sz(root, l - 1);
    auto tmp2 = split_sz(tmp.second, r - l + 1);
    upd(tmp2.first);
    int64_t ans = INF;
    if (tmp2.first) {
        ans = tmp2.first->mn;
    }
    root = merge(tmp.first, merge(tmp2.first, tmp2.second));
    return ans;
}

struct Frog {
    int color, place;
};

vector<Frog> queries;

bool replace(Frog& f) {
    auto [left, el_plus_right] = split_sz(root, f.place - 1);
    auto [el, right] = split_sz(el_plus_right, 1);
    if (!el || el->key != f.color) {
        return false;
    }
    root = merge(el, merge(left, right));
    return true;
}

Node* get_first(Node* v) {
    while (v->l) v = v->l;
    return v;
}

void replace_frog(Frog& frog) {
    auto [frog_, other] = split_sz(root, 1);
    auto [first, second] = split_sz(other, frog.place - 1);
    root = merge(first, merge(frog_, second));
}

void solve() {
    int n, m;
    cin >> n >> m;
    queries.assign(m, {});
    for (int i = m - 1; i >= 0; --i) {
        int c, p;
        cin >> c >> p;
        queries[i] = {c, p};
    }
    int count = 0;
    vector<bool> used(n + 1);
    for (int i = m - 1; i >= 0; --i) {
        if (count < queries[i].place) {
            if (used[queries[i].color]) {
                cout << -1 << '\n';
                return;
            }
            used[queries[i].color] = true;
            root = merge(new Node(queries[i].color), root);
            count++;
        } else {
            if (!replace(queries[i])) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            root = merge(root, new Node(i));
        }
    }
    for (int i = 0; i < m; ++i) {
        Node* first = get_first(root);
        if (first->key != queries[i].color) {
            cout << -1 << '\n';
            return;
        }
        replace_frog(queries[i]);
    }
    print(root);
}

signed main() {
    cout << boolalpha;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}