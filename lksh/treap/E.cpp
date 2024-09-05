// Переворот
#include <bits/stdc++.h>

using namespace std;

constexpr int64_t INF = 1e18;
constexpr int64_t MOD = 1e9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  int64_t key;
  int64_t priority;
  int64_t sz = 1;
  int64_t mn;
  bool rev = false;
  int64_t sum;

  Node(int64_t x) : key(x), priority(rng()), sum(x), mn(key) {}

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

int64_t get_min_node(Node* v) {
  return v ? v->mn : INF;
}

void upd(Node* v) {
  if (!v) return;
  v->sz = get_sz(v->l) + get_sz(v->r) + 1;
  v->sum = get_sum(v->l) + get_sum(v->r) + v->key;
  v->mn = min({get_min_node(v->l), get_min_node(v->r), v->key});
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
pair<Node*, Node*> split(Node* v, int64_t x) {
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
  cout << v->key << '(' << v->sz << ", rev=" << v->rev << ")" << ' ';
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
  root =
      merge(tmp.first, merge(new Node(x), tmp.second));  // тут немного не так
}

void erase(int64_t x) {
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

int64_t next(Node* v, int64_t x) {
  auto tmp = split(root, x + 1);
  Node* ans = get_min(tmp.second);
  merge(tmp.first, tmp.second);
  if (!ans) return INF;
  return ans->key;
}

int64_t prev(Node* v, int64_t x) {
  auto tmp = split(root, x);
  Node* ans = get_max(tmp.first);
  merge(tmp.first, tmp.second);
  if (!ans) return -INF;
  return ans->key;
}

int64_t get_kth(Node* v, int64_t k) {
  push(v);
  if (k > root->sz) return -INF;
  if (!v) return -INF;
  int64_t lsz = get_sz(v->l);
  if (lsz + 1 == k) return v->key;
  if (lsz >= k) {
    return get_kth(v->l, k);
  } else {
    return get_kth(v->r, k - lsz - 1);
  }
}

// <, >=
pair<Node*, Node*> split_sz(Node* v, int64_t x) {
  push(v);
  if (!v) return {nullptr, nullptr};
  if (get_sz(v->l) + 1 > x) {
    auto tmp = split_sz(v->l, x);
    v->l = tmp.second;
    upd(v);
    return {tmp.first, v};
  } else {
    auto tmp = split_sz(v->r, x - get_sz(v->l) - 1);
    v->r = tmp.first;
    upd(v);
    return {v, tmp.second};
  }
}

void to_start(int64_t l, int64_t r) {
  auto tmp = split_sz(root, l - 1);
  auto tmp2 = split_sz(tmp.second, r - l + 1);
  root = merge(tmp2.first, merge(tmp.first, tmp2.second));
}

void reverse(int64_t l, int64_t r) {
  auto tmp = split_sz(root, l - 1);
  auto tmp2 = split_sz(tmp.second, r - l + 1);
  if (tmp2.first) {
    tmp2.first->rev ^= 1;
  }
  root = merge(tmp.first, merge(tmp2.first, tmp2.second));
}

int64_t get_min_range(int64_t l, int64_t r) {
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

void solve() {
  int64_t n, m;
  cin >> n >> m;
  vector<int64_t> a(n);
  for (int64_t i = 0; i < n; ++i) {
    int64_t t;
    cin >> t;
    root = merge(root, new Node(t));
  }
  for (int64_t i = 0; i < m; ++i) {
    int64_t move, l, r;
    cin >> move >> l >> r;
    if (move == 1) {  // reverse
      reverse(l, r);
    } else {
      cout << get_min_range(l, r) << '\n';
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