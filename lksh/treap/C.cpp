// и снова сумма
#include <bits/stdc++.h>

using namespace std;

constexpr int64_t INF = 1e18;
constexpr int64_t MOD = 1e9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int64_t key;
    int64_t priority;
    int64_t sz = 1;
    int64_t sum;

    Node(int64_t x) : key(x), priority(rng()), sum(x) {}

    Node *l, *r;
};

Node* root;

bool exists(Node* v, int64_t x) {
    if (!v) return false;
    if (v->key == x) return true;
    if (v->key < x) return exists(v->r, x);
    return exists(v->l, x);
}

int64_t get_sz(Node* v) {
    return v ? v->sz : 0;
}

int64_t get_sum(Node* v) {
    return v ? v->sum : 0;
}

void upd(Node* v) {
    if (!v) return;
    v->sz = get_sz(v->l) + get_sz(v->r) + 1;
    v->sum = get_sum(v->l) + get_sum(v->r) + v->key;
}

// <, >=
pair<Node*, Node*> split(Node* v, int64_t x) {
    if (!v) return {nullptr, nullptr};
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
    print(v->l);
    cout << v->key << '(' << v->sz << ')' << ' ';
    print(v->r);
}

Node* merge(Node* l, Node* r) {
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

int64_t get_sum_range(int64_t l, int64_t r) {
    auto tmp = split(root, l);
    auto tmp2 = split(tmp.second, r + 1);
    int64_t ans = get_sum(tmp2.first);
    root = merge(tmp.first, merge(tmp2.first, tmp2.second));
    return ans;
}

void insert(int64_t x) {
    if (exists(root, x)) return;
    auto tmp = split(root, x);
    root = merge(tmp.first, merge(new Node(x), tmp.second));  // тут немного не так
}

void solve() {
    int64_t n;
    cin >> n;
    int64_t good = 0;
    for (int64_t i = 0; i < n; ++i) {
        char move;
        cin >> move;
        if (move == '+') {
            int64_t arg;
            cin >> arg;
            insert((arg + good) % MOD);
            good = 0;
        } else if (move == '?') {
            int64_t l, r;
            cin >> l >> r;
            int64_t ans = get_sum_range(l, r);
            cout << ans << '\n';
            good = ans;
        } else {
            print(root);
        }
    }
}

signed main() {
    cout << boolalpha;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}