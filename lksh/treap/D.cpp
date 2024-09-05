// Вперёд!
#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 1e9;
constexpr int MOD = 1e9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  int key;
  int priority;
  int sz = 1;
  int sum;

  Node(int x) : key(x), priority(rng()), sum(x) {}

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

int get_sum(Node* v) {
  return v ? v->sum : 0;
}

void upd(Node* v) {
  if (!v) return;
  v->sz = get_sz(v->l) + get_sz(v->r) + 1;
  v->sum = get_sum(v->l) + get_sum(v->r) + v->key;
}

// <, >=
pair<Node*, Node*> split(Node* v, int x) {
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

int get_sum_range(int l, int r) {
  auto tmp = split(root, l);
  auto tmp2 = split(tmp.second, r + 1);
  int ans = get_sum(tmp2.first);
  root = merge(tmp.first, merge(tmp2.first, tmp2.second));
  return ans;
}

void insert(int x) {
  if (exists(root, x)) return;
  auto tmp = split(root, x);
  root =
      merge(tmp.first, merge(new Node(x), tmp.second));  // тут немного не так
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

void to_start(int l, int r) {
  auto tmp = split_sz(root, l - 1);
  auto tmp2 = split_sz(tmp.second, r - l + 1);
  root = merge(tmp2.first, merge(tmp.first, tmp2.second));
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    root = merge(root, new Node(i));
  }
  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    to_start(l, r);
  }
  for (int i = 1; i <= n; ++i) {
    cout << get_kth(root, i) << ' ';
  }
}

int main() {
  cout << boolalpha;
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}