// Своппер
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

int64_t get_sum_range(Node*& root, int64_t l, int64_t r) {
  auto tmp = split(root, l);
  auto tmp2 = split(tmp.second, r + 1);
  int64_t ans = get_sum(tmp2.first);
  root = merge(tmp.first, merge(tmp2.first, tmp2.second));
  return ans;
}

void insert(Node*& root, Node* v, int64_t x) {
  if (exists(v, x)) return;
  auto tmp = split(v, x);
  root = merge(tmp.first, merge(new Node(x), tmp.second));
}

void erase(Node*& root, int64_t x) {
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

int64_t next(Node*& root, Node* v, int64_t x) {
  auto tmp = split(root, x + 1);
  Node* ans = get_min(tmp.second);
  merge(tmp.first, tmp.second);
  if (!ans) return INF;
  return ans->key;
}

int64_t prev(Node*& root, Node* v, int64_t x) {
  auto tmp = split(root, x);
  Node* ans = get_max(tmp.first);
  merge(tmp.first, tmp.second);
  if (!ans) return -INF;
  return ans->key;
}

int64_t get_kth(Node*& root, Node* v, int64_t k) {
  push(v);
  if (k > root->sz) return -INF;
  if (!v) return -INF;
  int64_t lsz = get_sz(v->l);
  if (lsz + 1 == k) return v->key;
  if (lsz >= k) {
    return get_kth(root, v->l, k);
  } else {
    return get_kth(root, v->r, k - lsz - 1);
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

void to_start(Node*& root, int64_t l, int64_t r) {
  auto tmp = split_sz(root, l - 1);
  auto tmp2 = split_sz(tmp.second, r - l + 1);
  root = merge(tmp2.first, merge(tmp.first, tmp2.second));
}

void reverse(Node*& root, int64_t l, int64_t r) {
  auto tmp = split_sz(root, l - 1);
  auto tmp2 = split_sz(tmp.second, r - l + 1);
  if (tmp2.first) {
    tmp2.first->rev ^= 1;
  }
  root = merge(tmp.first, merge(tmp2.first, tmp2.second));
}

int64_t get_min_range(Node*& root, int64_t l, int64_t r) {
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

void swapper(Node*& root_odd, Node*& root_even, int64_t l, int64_t r) {
  int64_t even_l, odd_l, even_r, odd_r;
  if (l & 1) {
    even_l = (l >> 1) + 1;
    odd_l = even_l;
  } else {
    even_l = l >> 1;
    odd_l = even_l + 1;
  }
  if (r & 1) {
    even_r = r >> 1;
    odd_r = (r >> 1) + 1;
  } else {
    even_r = r >> 1;
    odd_r = r >> 1;
  }
  auto [odd_left, odd_to_split] = split_sz(root_odd, odd_l - 1);
  auto [odd_mid, odd_right] = split_sz(odd_to_split, odd_r - odd_l + 1);
  auto [even_left, even_to_split] = split_sz(root_even, even_l - 1);
  auto [even_mid, even_right] = split_sz(even_to_split, even_r - even_l + 1);
  root_odd = merge(odd_left, merge(even_mid, odd_right));
  root_even = merge(even_left, merge(odd_mid, even_right));
}

int64_t get_sum_range_swapper(Node*& root_odd, Node*& root_even, int64_t l,
                              int64_t r) {
  int64_t even_l, odd_l, even_r, odd_r;
  if (l & 1) {
    even_l = (l >> 1) + 1;
    odd_l = even_l;
  } else {
    even_l = l >> 1;
    odd_l = even_l + 1;
  }
  if (r & 1) {
    even_r = r >> 1;
    odd_r = (r >> 1) + 1;
  } else {
    even_r = r >> 1;
    odd_r = r >> 1;
  }
  auto [odd_left, odd_to_split] = split_sz(root_odd, odd_l - 1);
  auto [odd_mid, odd_right] = split_sz(odd_to_split, odd_r - odd_l + 1);
  auto [even_left, even_to_split] = split_sz(root_even, even_l - 1);
  auto [even_mid, even_right] = split_sz(even_to_split, even_r - even_l + 1);
  int64_t ans = get_sum(odd_mid) + get_sum(even_mid);
  root_odd = merge(odd_left, merge(odd_mid, odd_right));
  root_even = merge(even_left, merge(even_mid, even_right));
  return ans;
}

void solve() {
  int64_t n, m;
  cin >> n >> m;
  int64_t index_swapper = 1;
  while (n != 0) {
    Node* root_odd = nullptr;
    Node* root_even = nullptr;
    for (int64_t i = 1; i <= n; ++i) {
      int64_t t;
      cin >> t;
      if (i & 1) {
        root_odd = merge(root_odd, new Node(t));
      } else {
        root_even = merge(root_even, new Node(t));
      }
    }
    cout << "Swapper " << index_swapper++ << ':' << '\n';
    for (int64_t i = 0; i < m; ++i) {
      int64_t move;
      cin >> move;
      if (move == 1) {
        // swap
        int64_t x, y;
        cin >> x >> y;
        swapper(root_odd, root_even, x, y);
      } else {
        int64_t a, b;
        cin >> a >> b;
        cout << get_sum_range_swapper(root_odd, root_even, a, b) << '\n';
        // getsum
      }
    }
    cin >> n >> m;
  }
}

signed main() {
  cout << boolalpha;
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}