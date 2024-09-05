#include "bits/stdc++.h"
using namespace std;

int nok(int a, int b) {
  return (long double)a / __gcd(a, b) * b;
}

void solve() {
  int a, b, c;
  cin >> a >> b >> c;
  int shared_nok_minutes = nok(a, nok(b, c));
  int cnt_a = shared_nok_minutes / a;
  int cnt_b = shared_nok_minutes / b;
  int cnt_c = shared_nok_minutes / c;
  int total_twice = cnt_a + cnt_b + cnt_c;
  long double total = total_twice;
  total /= 2;
  cout << setprecision(4);
  cout << shared_nok_minutes / total << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    solve();
  }
}
