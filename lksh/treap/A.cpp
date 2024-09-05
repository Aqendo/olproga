// Двоичное дерево поиска

#include <bits/stdc++.h>

using namespace std;

constexpr int64_t INF = 1e18;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  int64_t key;
  int64_t priority;

  Node(int64_t x) : key(x), priority(rng()) {}

  Node *l, *r;
};

bool exists(Node* v, int64_t x) {
  if (!v) {
    return false;
  }
  if (v->key == x) {
    return true;
  }
  if (v->key < x) {
    return exists(v->r, x);
  }
  return exists(v->l, x);
}

// <, >=
pair<Node*, Node*> split(Node* v, int64_t x) {
  if (!v) return {nullptr, nullptr};
  if (x <= v->key) {
    auto tmp = split(v->l, x);
    v->l = tmp.second;
    return {tmp.first, v};
  } else {
    auto tmp = split(v->r, x);
    v->r = tmp.first;
    return {v, tmp.second};
  }
}

void print(Node* v) {
  if (!v) return;
  print(v->l);
  cout << v->key << ' ';
  print(v->r);
}

Node* merge(Node* l, Node* r) {
  if (!l) return r;
  if (!r) return l;
  if (l->priority > r->priority) {
    l->r = merge(l->r, r);
    return l;
  }
  r->l = merge(l, r->l);
  return r;
}

Node* root;

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

void solve() {
  string move;
  while (cin >> move) {
    int64_t data;

    if (move != "print") cin >> data;
    if (move[0] == 'i') {
      insert(data);
    } else if (move[0] == 'd') {
      erase(data);
    } else if (move[0] == 'e') {
      cout << exists(root, data) << '\n';
    } else if (move[0] == 'n') {
      int64_t ans = next(root, data);
      if (ans == INF) {
        cout << "none" << '\n';
      } else {
        cout << ans << '\n';
      }
    } else if (move == "print") {
      print(root);
      cout << '\n';
    } else {
      int64_t ans = prev(root, data);
      if (ans == -INF) {
        cout << "none" << '\n';
      } else {
        cout << ans << '\n';
      }
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