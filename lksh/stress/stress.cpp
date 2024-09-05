#include "../bits/stdc++.h"
#define int int64_t
using namespace std;
struct SegPee {
  vector<int> pref;
  deque<int> els;
  int cnt_deleted = 0;
  int sum_deleted = 0;
  SegPee(deque<int> &els) : els(els) {
    pref.assign(els.size() + 1, {});
    for (int i = 1; i <= (int) els.size(); ++i) {
      pref[i] = pref[i - 1] + els[i - 1];
    }
  }
  void del() {
    sum_deleted += els[cnt_deleted++];
  }
  int get(int l) {
    return pref[l + cnt_deleted] - sum_deleted;
  }
};
struct FastSolve {
  int solve(int n, int m, vector<pair<int, int>> &inp) {
    deque<int> chests_open, chests_locked;
    deque<int> keys;
    for (int i = 0; i < n; ++i) {
      auto [type, x] = inp[i];
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
    deque<int> answer;
    int sum = 0;
    while (!chests_open.empty() && m--) {
      answer.push_back(chests_open.front());
      sum += chests_open.front();
      chests_open.pop_front();
    }
    m = max(m, int(0));
    sort(answer.begin(), answer.end());
    SegPee pee(answer), lockd(chests_locked);
    int ans = sum;
    for (int i = 1; i <= min((int) answer.size() + m - 1, (int) chests_locked.size()); ++i) {
      int keys_amount = 0;
      int keys_pairs_count = 0;
      for (int j : keys) {
        if (keys_amount >= i) break;
        keys_amount += j;
        keys_pairs_count++;
        if (keys_amount >= i) break;
      }
      if (keys_amount < i) continue;
      int sum_worth_of_ones = lockd.get(i);
      int how_many_zeroes_extra = max<int>(0, i - m + keys_pairs_count);
      int sum_extra_zeroes = pee.get(how_many_zeroes_extra);
      ans = max(ans, sum + sum_worth_of_ones - sum_extra_zeroes);
    }
    return ans;
  }
};
struct SlowSolve {
  int solve(int n, int m, vector<pair<int, int>> &inp) {
    deque<int> chests_open, chests_locked;
    deque<int> keys;
    for (int i = 0; i < n; ++i) {
      auto [type, x] = inp[i];
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
    return ans;
  }
};
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (true) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n = uniform_int_distribution<int>(1, 10000)(rng);
    int m = uniform_int_distribution<int>(1, 10000)(rng);

    vector<pair<int, int>> inp(n);
    for (int i = 0; i < n; ++i) {
      int type = uniform_int_distribution<int>(0, 2)(rng);
      int x = uniform_int_distribution<int>(1, 200000)(rng);
      inp[i] = {type, x};
    }
    FastSolve fast;
    int fastAns = fast.solve(n, m, inp);
    SlowSolve slow;
    int slowAns = slow.solve(n, m, inp);
    if (fastAns < slowAns) {
      cout << n << ' ' << m << '\n';
      for (auto [u, v] : inp) {
        cout << u << ' ' << v << '\n';
      }
      cout << fastAns << ' ' << slowAns;
      return 0;
    }
  }

  return 0;
}

