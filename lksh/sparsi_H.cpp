#include <bits/stdc++.h>

using namespace std;

const int64_t K = 300;
void solve() {
  int64_t n, k;
  cin >> n >> k;
  vector<int64_t> blocks(n / K + 2);
  vector<int64_t> a(n);
  for (int64_t i = 0; i < k; ++i) {
    char move;
    cin >> move;
    if (move == 'A') {
      int64_t index, x;
      cin >> index >> x;
      blocks[(index - 1) / k] += x - a[index - 1];
      a[index - 1] = x;
    } else {
      int64_t l, r;
      cin >> l >> r;
      l--;
      r--;
      int64_t ans = 0;
      if (r - l <= 2 * k) {
        for (int64_t j = l; j <= r; ++j) {
          ans += a[j];
        }
      } else {
        for (; l % k != 0; ++l) {
          ans += a[l];
        }
        for (; r % k != k - 1; --r) {
          ans += a[r];
        }
        for (int64_t j = l / k; j <= r / k; ++j) {
          ans += blocks[j];
        }
      }
      cout << ans << endl;
    }
  }
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}