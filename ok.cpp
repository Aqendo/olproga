#include "bits/stdc++.h"
using namespace std;

void solve() {
  long double a, b, c;
  cin >> a >> b >> c;
  cout << (2 * a * b * c) / (b * c + a * c + a * b) << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(4) << fixed;
  int tt;
  cin >> tt;
  while (tt--) {
    solve();
  }
}
