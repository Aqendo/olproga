#include <bits/stdc++.h>

#include "testlib.h"

using namespace std;

long double max_diff_n = 2;
long double max_diff_m = 2;

int maxn = 1e4;
int maxm = 1e5;
int maxc = 1e9;

bool sun, bamboo, tree;

int get(int v, vector<int>& par) { return par[v] == v ? v : get(par[v], par); }
void dsu(int a, int b, vector<int>& par, vector<int>& sz) {
  a = get(a, par), b = get(b, par);
  if (a == b) return;
  if (sz[a] < sz[b]) swap(a, b);
  par[b] = par[a];
  sz[a] += sz[b];
}

void gen_sun(int n) {
  vector<pair<pair<int, int>, int>> a;
  for (int i = 2; i <= n; ++i) {
    int u = 1, v = i, c = rnd.next(0, maxc);
    if (rnd.next(0, 1)) swap(u, v);
    a.push_back({{u, v}, c});
  }
  shuffle(a.begin(), a.end());

  cout << n << " " << n - 1 << "\n";
  for (auto& x : a) {
    cout << x.first.first << " " << x.first.second << " " << x.second << "\n";
  }
  cout << rnd.next(1, n) << " " << rnd.next(1, n) << "\n";
}

void gen_bamboo(int n) {
  vector<pair<pair<int, int>, int>> a;
  for (int i = 2; i <= n; ++i) {
    int u = i - 1, v = i, c = rnd.next(0, maxc);
    if (rnd.next(0, 1)) swap(u, v);
    a.push_back({{u, v}, c});
  }
  shuffle(a.begin(), a.end());

  cout << n << " " << n - 1 << "\n";
  for (auto& x : a) {
    cout << x.first.first << " " << x.first.second << " " << x.second << "\n";
  }
  cout << rnd.next(1, n) << " " << rnd.next(1, n) << "\n";
}

void gen_tree(int n) {
  vector<int> par(n + 1), sz(n + 1, 1);
  for (int i = 1; i <= n; ++i) par[i] = i;

  vector<pair<pair<int, int>, int>> a;
  while (a.size() != n - 1) {
    int u = rnd.next(1, n), v = rnd.next(1, n);
    int c = rnd.next(0, maxc);

    if (get(u, par) != get(v, par)) {
      dsu(u, v, par, sz);
      a.push_back({{u, v}, c});
    }
  }

  cout << n << " " << n - 1 << "\n";
  for (auto& x : a) {
    cout << x.first.first << " " << x.first.second << " " << x.second << "\n";
  }
  cout << rnd.next(1, n) << " " << rnd.next(1, n) << "\n";
}

void gen_graph(int n, int m) {
  vector<int> par(n + 1), sz(n + 1, 1);
  for (int i = 1; i <= n; ++i) par[i] = i;

  map<pair<int, int>, bool> edge;
  vector<pair<pair<int, int>, int>> a;
  while (a.size() != n - 1) {
    int u = rnd.next(1, n), v = rnd.next(1, n);
    int c = rnd.next(0, maxc);

    if (get(u, par) != get(v, par)) {
      dsu(u, v, par, sz);
      edge[{u, v}] = edge[{v, u}] = 1;
      a.push_back({{u, v}, c});
    }
  }

  while (a.size() != m) {
    int u = rnd.next(1, n), v = rnd.next(1, n);
    int c = rnd.next(0, maxc);

    if (edge[{u, v}] == 0 && u != v) {
      edge[{u, v}] = edge[{v, u}] = 1;
      a.push_back({{u, v}, c});
    }
  }

  cout << n << " " << m << "\n";
  for (auto& x : a) {
    cout << x.first.first << " " << x.first.second << " " << x.second << "\n";
  }
  cout << rnd.next(1, n) << " " << rnd.next(1, n) << "\n";
}

void gen_max() { max_diff_n = 1.125; }

void gen_group1() { sun = 1; }

void gen_group2() { bamboo = 1; }

void gen_group3() { tree = 1; }

void gen_group4() { maxc = 100; }

void gen_group5() {}

void gen_test() {
  int n = rnd.next(max(2, int(maxn / max_diff_n)), maxn);
  int m = rnd.next(n - 1, (n <= 632 ? n * (n - 1) / 2 : maxm));

  if (sun) {
    gen_sun(n);
    return;
  }

  if (bamboo) {
    gen_bamboo(n);
    return;
  }

  if (tree) {
    gen_tree(n);
    return;
  }

  gen_graph(n, m);
  return;
}

void gen_test(int group) {
  if (group == 1) {
    gen_group1();
  } else if (group == 2) {
    gen_group2();
  } else if (group == 3) {
    gen_group3();
  } else if (group == 4) {
    gen_group4();
  } else {
    gen_group5();
  }

  gen_test();
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int group = rnd.next(1, 5);

  gen_test(group);
}
