#include "bits/stdc++.h"
#define int int64_t
using namespace std;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  deque<int> chests_open, chests_locked;
  deque<int> keys;
  for (int i = 0; i < n; ++i) {
    int type, x;
    cin >> type >> x;
    if (type == 2) {
      keys.push_back(x);
    } else {
      if (type == 0) {
        chests_open.push_back(x);
      } else {
        chests_locked.push_back(x);
      }
    }
  }
  sort(keys.rbegin(), keys.rend());
  sort(chests_locked.rbegin(), chests_locked.rend());
  sort(chests_open.rbegin(), chests_open.rend());
  deque<pair<int, int>> answer;
  while (!chests_open.empty() && m--) {
    answer.emplace_back(0, chests_open.front());
    chests_open.pop_front();
  }
  int amount_keys_now = 0;
  while (m > 0) {
    if (amount_keys_now == 0) {
      if (keys.empty()) break;
      m--;
      answer.emplace_front(2, keys.front());
      amount_keys_now = keys.front();
      keys.pop_front();
      continue;
    }
    if (chests_locked.empty()) break;
    amount_keys_now--;
    m--;
    answer.emplace_front(1, chests_locked.front());
    chests_locked.pop_front();
    if (m == 0) break;
  }
  for (int i = (int) answer.size() - 1; i >= 0; --i) {
    if (answer[i].first != 0) continue;
    if (chests_locked.empty()) break;
    if (amount_keys_now > 0) {
      if (answer[i].second < chests_locked.front()) {
        answer[i] = {1, chests_locked.front()};
        chests_locked.pop_front();
        amount_keys_now--;
        continue;
      }
      continue;
    }
    if (keys.empty()) break;
    if (i > 0 && answer[i].first == 0 && answer[i - 1].first == 0) {
      if (answer[i - 1].second + answer[i].second < chests_locked.front()) {
        answer[i] = {2, keys.front()};
        answer[i - 1] = {1, chests_locked.front()};
        amount_keys_now = keys.front() - 1;
        keys.pop_front();
        chests_locked.pop_front();
      }
    }
  }
  int ans = 0;
  for (auto [type, x] : answer) {
    if (type != 2) {
      ans += x;
    }
  }
  cout << ans << endl;
  return 0;
}


