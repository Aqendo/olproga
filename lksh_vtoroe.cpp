#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int MOD = 1e9 + 7;
int add(int a, int b) {
  return a + b > MOD ? a + b - MOD : a + b;
}
int sub(int a, int b) {
  return a - b > 0 ? a - b : a - b + MOD;
}
struct Vector {
  int x = 0, y = 0;
};
#ifdef LOCAL
const int L_GRID = -2;
const int R_GRID = 4;
#else
const int L_GRID = -(int) (1e18) - 1;
const int R_GRID = 1e18 + 1;
#endif

vector<Vector> coords;
int dist(Vector &v1, Vector &v2) {
  return abs(v1.x - v2.x) + abs(v1.y - v2.y);
}
int get_max_dist(int x, int y) {
  int ans = LLONG_MIN;
  Vector ourDot = {x, y};
  for (Vector &i : coords) {
    ans = max(ans, dist(ourDot, i));
  }
  return ans;
}
int f(int x) {
  int l = L_GRID, r = R_GRID;
  while (r - l > 3) {
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;
    if (get_max_dist(x, m1) < get_max_dist(x, m2)) {
      r = m2;
    } else {
      l = m1;
    }
  }
  int ans = LLONG_MAX;
  for (int y = l; y <= r; ++y) {
    ans = min(ans, get_max_dist(x, y));
  }
  return ans;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  coords.assign(n, {});
  for (int i = 0; i < n; ++i) {
    cin >> coords[i].x >> coords[i].y;
  }
  int l = L_GRID, r = R_GRID;
  while (r - l > 3) {
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;
    if (f(m1) < f(m2)) {
      r = m2;
    } else {
      l = m1;
    }
  }
  int ans = LLONG_MAX;
  for (int x = l; x <= r; ++x) {
    ans = min(ans, f(x));
  }
  cout << ans << endl;
  return 0;
}




#include <bits/stdc++.h>
#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
using namespace std;
#define int int64_t
const int MOD = 1e9 + 7;
int add(int a, int b) {
  return a + b > MOD ? a + b - MOD : a + b;
}
int sub(int a, int b) {
  return a - b > 0 ? a - b : a - b + MOD;
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  int s = 0;
  for (int &i : a) {
    cin >> i;
    s += i;
  }
  vector<vector<int>> dp(s, vector<int>(s + 1));
  dp[0][1] = 1;
  dp[0][0] = 1;
  for (int i = 1; i < s; ++i) {
    for (int j = 0; j <= i + 1; ++j) {
      dp[i][j] = add(dp[i - 1][j], (j == 0 ? 0 : dp[i - 1][j - 1]));
    }
  }
  int ans = LLONG_MIN;
  for (int i : a) {
    ans = max(ans, dp[s - 1][i]);
  }
  cout << ans;
  return 0;
}

