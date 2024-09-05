#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define OPTIMIZETHISSHIT       \
  ios::sync_with_stdio(false); \
  cin.tie(nullptr);
#define int long long

#define endl '\n'
#define fi first
#define se second

#define pb push_back
#define eb emplace_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define icin(x) \
  int x;        \
  cin >> x

using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Segtree_can_access {
  vector<int> tree;
  vector<int> lazy;
  int size = 1;

  void init(int n) {
    while (size < n) size *= 2;
    tree.assign(2 * size - 1, 0);
    lazy.assign(2 * size - 1, 0);
  }

  void relax(int x, int lx, int rx) {
    int m = lx + (rx - lx) / 2;
    tree[x] = tree[2 * x + 1] + tree[2 * x + 2] + lazy[2 * x + 1] * (m - lx) + lazy[2 * x + 2] * (rx - m);
  }

  void push(int x, int lx, int rx) {
    lazy[2 * x + 1] += lazy[x];
    lazy[2 * x + 2] += lazy[x];
    lazy[x] = 0;
    relax(x, lx, rx);
  }

  void kill(int l, int r, int p, int x, int lx, int rx) {
    if (rx <= l || lx >= r) {
      return;
    }
    if (lx >= l && rx <= r) {
      lazy[x] -= p;
      return;
    }
    push(x, lx, rx);
    int m = lx + (rx - lx) / 2;
    kill(l, r, p, 2 * x + 1, lx, m);
    kill(l, r, p, 2 * x + 2, m, rx);
    relax(x, lx, rx);
  }

  void kill(int l, int r, int p) {
    kill(l, r, p, 0, 0, size);
  }

  void attack(int l, int r, int a, int d, int x, int lx, int rx) {
    if (rx <= l || lx >= r) {
      return;
    }
    if (rx - lx == 1) {
      tree[x] += a + d * (lx - l);
      return;
    }
    push(x, lx, rx);
    int m = lx + (rx - lx) / 2;
    attack(l, r, a, d, 2 * x + 1, lx, m);
    attack(l, r, a, d, 2 * x + 2, m, rx);
    relax(x, lx, rx);
  }

  void attack(int i, int q) {
    if (i - q + 1 < 0) {
      attack(0, i + 1, 1 + abs(i - q + 1), 1, 0, 0, size);
    } else {
      attack(i - q + 1, i + 1, 1, 1, 0, 0, size);
    }
    attack(i + 1, min(size, i + q), q - 1, -1, 0, 0, size);
  }

  int sum(int l, int r, int x, int lx, int rx) {
    if (rx - lx != 1) {
      push(x, lx, rx);
    } else {
      tree[x] = tree[x] + lazy[x];
      lazy[x] = 0;
    }
    if (l >= rx || lx >= r) {
      return 0;
    }
    if (lx >= l && rx <= r) {
      return tree[x];
    }
    int m = lx + (rx - lx) / 2;
    int s1 = sum(l, r, 2 * x + 1, lx, m);
    int s2 = sum(l, r, 2 * x + 2, m, rx);
    int result = s1 + s2;
    return result;
  }

  int sum(int l, int r) {
    return sum(l, r, 0, 0, size);
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Segtree_can_access st;
  st.init(n);
  for (int i = 0; i < m; i++) {
    char c;
    cin >> c;
    if (c == '?') {
      int l, r;
      cin >> l >> r;
      l--;
      cout << st.sum(l, r) << endl;
    } else if (c == 'R') {
      int j, q;
      cin >> j >> q;
      j--;
      st.attack(j, q);
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      l--;
      st.kill(l, r, x);
    }
  }
}

signed main() {
  OPTIMIZETHISSHIT

  solve();
}
