#include <bits/stdc++.h>

using namespace std;

constexpr int k = 1;
const int INF = 1e9;
struct Arithmetic_Progression {
  int a1, k, index;
  Arithmetic_Progression operator+(const Arithmetic_Progression& rhs) const {
    return {a1 + rhs.a1, k + rhs.k};
  }
};
void solve() {
  int n;
  cin >> n;
  vector<int> a(n), b(n), answer(n, INT_MIN);
  vector<vector<Arithmetic_Progression>> blocks(n / k + 2);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
    if (a[i] >= b[i]) answer[i] = 0;
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int l, r, x, y;
    cin >> l >> r >> x >> y;
    l--;
    r--;
    int old_l = l, old_r = r;
    static auto get_with_last_arithmetic_progression = [&](int j) -> long long {
      if (blocks[j / k].empty()) return a[j];
      return a[j] + blocks[j / k].back().a1 +
             blocks[j / k].back().k * (j - j / k * k);
    };
    if (r - l <= 2 * k) {
      for (int j = l; j <= r; ++j) {
        a[j] += x + (j - old_l) * y;
        if (answer[j] == INT_MIN) {
          if (get_with_last_arithmetic_progression(j) >= b[j]) {
            answer[j] = i + 1;
          }
        }
      }
    } else {
      for (; l % k != 0; ++l) {
        a[l] += x + (l - old_l) * y;
        if (answer[l] == INT_MIN) {
          if (get_with_last_arithmetic_progression(l) >= b[l]) {
            answer[l] = i;
          }
        }
      }
      for (; r % k != k - 1 && r >= 0; --r) {
        a[r] += x + (r - old_l) * y;
        if (answer[r] == INT_MIN) {
          if (get_with_last_arithmetic_progression(r) >= b[r]) {
            answer[r] = i;
          }
        }
      }
      for (int j = l / k; j <= r / k; ++j) {
        Arithmetic_Progression new_arithmetic_progression = {
            .a1 = x + y * (j * k - old_l), .k = y, .index = i};
        if (blocks[j].empty()) {
          blocks[j].push_back(new_arithmetic_progression);
        } else {
          blocks[j].push_back(blocks[j].back() + new_arithmetic_progression);
        }
      }
    }
  }
  static auto get_with_arithmetic_progression =
      [&](int j, int index_progression) -> long long {
    return a[j] + blocks[j / k][index_progression].a1 +
           blocks[j / k][index_progression].k * (j - j / k * k);
  };
  for (int i = 0; i < n; ++i) {
    if (answer[i] == INT_MIN) {
      if (blocks[i / k].empty()) {
        answer[i] = -1;
        continue;
      }
      int l = 0, r = static_cast<int>(blocks[i / k].size());
      while (r - l > 1) {
        int m = (l + r) >> 1;
        if (get_with_arithmetic_progression(i, m) < b[i]) {
          l = m;
        } else {
          r = m;
        }
      }
      if (r >= blocks[i / k].size()) {
        r = (int)blocks[i / k].size() - 1;
      }
      long long res = get_with_arithmetic_progression(i, r);
      if (res >= b[i]) {
        answer[i] = blocks[i / k][r].index + 1;
      } else {
        answer[i] = -1;
      }
    }
  }
  for (const int i : answer) cout << i << ' ';
  cout << '\n';
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
  return 0;
}