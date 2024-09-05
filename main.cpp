#include "bits/stdc++.h"
using namespace std;
#ifndef LOCAL
#pragma GCC optimize("O3")
#define debug(...) 32
#else
#include "debug.h"
#endif
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define int int64_t
bool is_prime(int n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      if (is_prime(i ^ j)) {
        cout << i << ' ' << j << '\n';
      }
    }
  }
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  cin >> t;
  while (t--) solve();
}