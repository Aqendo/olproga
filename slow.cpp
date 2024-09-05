#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// #pragma GCC optimize("Ofast", "unroll-loops")

#define OPTIMIZETHISSHIT       \
  ios::sync_with_stdio(false); \
  cin.tie(nullptr);
#define int long long
// #define double long double

#define fi first
#define se second

#define pb push_back
#define eb emplace_back
// #define deep(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define icin(x) \
  int x;        \
  cin >> x

using namespace std;
using namespace __gnu_pbds;

template <typename K, typename V>
using hash_table = gp_hash_table<K, V>;
template <typename K>
using hash_set = gp_hash_table<K, null_type>;

// #define unordered_map hash_table
// #define unordered_set hash_set

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng(42);
class Solve {
 public:
  int n, q, k;
  vector<int> a;
  vector<pair<int, int>> req;
  void init(int nn, int qq, int kk, vector<int> aa, vector<pair<int, int>> reqq) {
    n = nn, q = qq, k = kk, a = move(aa), req = move(reqq);
  }
  unordered_map<int, int> counter;

  int get_neighbor(int ind) {
    int f1 = ind % k, f2 = (k - f1) % k;
    if (f1 == f2) {
      return counter[f2] - 1;
    } else {
      return counter[f2];
    }
  }

  vector<int> solve() {
    for (int i = 0; i < n; i++) {
      counter[a[i] % k]++;
    }
    unordered_map<int, int> neww = counter;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      neww[a[i] % k]--;
      cnt += neww[(k - (a[i] % k)) % k];
    }
    vector<int> ans;
    for (auto r : req) {
      int x = r.fi, y = r.se;
      x--;
      cnt -= get_neighbor(a[x]);
      counter[a[x] % k]--;
      a[x] = y;
      counter[a[x] % k]++;
      cnt += get_neighbor(a[x]);
      ans.pb(cnt);
    }
    return ans;
  }
};

vector<int> slow(int n, int q, int k, vector<int> a, vector<pair<int, int>> req) {
  vector<int> ans;
  for (auto rq : req) {
    int x = rq.fi, y = rq.se;
    x--;
    a[x] = y;
    int cnt = 0;
    for (int l = 0; l < n; l++) {
      for (int r = l + 1; r < n; r++) {
        cnt += ((a[l] + a[r]) % k == 0);
      }
    }
    ans.pb(cnt);
  }
  return ans;
}

// #define STRESS
signed main() {
  OPTIMIZETHISSHIT
#ifdef STRESS
  int ii = 0;
  while (true) {
    int n = uniform_int_distribution<int>(1, 100)(rng);
    int q = uniform_int_distribution<int>(1, 100)(rng);
    int k = uniform_int_distribution<int>(1, 1e9)(rng);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = uniform_int_distribution<int>(1, 1e9)(rng);
    }
    vector<pair<int, int>> req(q);
    for (int i = 0; i < q; i++) {
      req[i].fi = uniform_int_distribution<int>(1, n)(rng);
      req[i].se = uniform_int_distribution<int>(1, 1e9)(rng);
    }
    auto sol = Solve();
    sol.init(n, q, k, a, req);

    vector<int> f1 = sol.solve();
    vector<int> f2 = slow(n, q, k, a, req);
    if (f1 != f2) {
      cout << "GANG" << endl;
      cout << n << ' ' << q << ' ' << k << endl;
      for (int i : a) {
        cout << i << ' ';
      }
      cout << endl;
      for (auto r : req) {
        cout << r.fi << ' ' << r.se << endl;
      }
      for (int i : f1) {
        cout << i << ' ';
      }
      cout << endl;
      for (int i : f2) {
        cout << i << ' ';
      }
      cout << endl;
      break;
    }
    cout << "test " << ++ii << " ok" << endl;
  }
#else
  int n, q, k;
  cin >> n >> q >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<pair<int, int>> req(q);
  for (int i = 0; i < q; i++) {
    cin >> req[i].fi >> req[i].se;
  }
  auto sol = Solve();
  sol.init(n, q, k, a, req);
  vector<int> f1 = sol.solve();
  for (int i : f1) {
    cout << i << '\n';
  }
  // cout << endl;
#endif
}