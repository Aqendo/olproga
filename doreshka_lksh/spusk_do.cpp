#include "bits/stdc++.h"

#define int long long
using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
#endif

struct Segtree {
    vector<int> tree;
    int n;
    Segtree(vector<int>& a) : tree(4 * a.size()), n(a.size()) { build(a, 1, 0, n - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = gcd(tree[x << 1], tree[x << 1 | 1]);
    }
    void set(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            set(x << 1, lx, m, i, v);
        } else {
            set(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = gcd(tree[x << 1], tree[x << 1 | 1]);
    }
    pair<int, int> get(int x, int lx, int rx, int k, int l, int r, int already) {
        // printf("stepping into [%lld, %lld], searching for [%lld, %lld]\n", lx, rx, l, r);
        if (l > r) return {-1, 0};
        if (lx == l && rx == r && gcd(tree[x], already) > k) {
            return {-1, gcd(tree[x], already)};
        }
        if (lx == rx) {
            return {lx, gcd(tree[x], already)};
        }
        pair<int, int> answer;
        int m = (lx + rx) >> 1;
        // printf("stepping into left child at [%lld, %lld]\n", lx, rx);
        auto first = get(x << 1, lx, m, k, l, min(m, r), already);
        // printf("stepping out of left child at [%lld, %lld] with gcd in it equals to %lld\n", lx, rx, first.second);
        if (first.second != 0 && gcd(already, first.second) <= k) {
            // printf("seems gcd(already, first.second) <= k at left child\n");
            answer = first;
        } else {
            // printf("stepping into right child at [%lld, %lld]\n", lx, rx);
            answer = get(x << 1 | 1, m + 1, rx, k, max(m + 1, l), r, gcd(already, first.second));
        }
        return answer;
    }
};

vector<int> solve_fast(vector<int>& a, const vector<array<int, 3>>& queries) {
    int n = a.size();
    Segtree seg(a);
    int q = queries.size();
    vector<int> answers;
    for (int i = 0; i < q; ++i) {
        int move = queries[i][0];
        if (move == 1) {
            int index = queries[i][1], x = queries[i][2];
            index--;
            seg.set(1, 0, n - 1, index, x);
        } else {
            int k = queries[i][1], from = queries[i][2];
            from--;
            pair<int, int> answer = seg.get(1, 0, n - 1, k, from, n - 1, 0);
            if (answer.first == -1) {
                answers.push_back(-1);
            } else {
                answers.push_back(answer.first - from + 1);
            }
        }
    }
    return answers;
}
vector<int> solve_slow(vector<int>& a, const vector<array<int, 3>>& queries) {
    vector<int> arr = a;
    int n = a.size();
    int q = queries.size();
    vector<int> answers;
    for (int i = 0; i < q; ++i) {
        int move = queries[i][0];
        if (move == 1) {
            int index = queries[i][1], x = queries[i][2];
            index--;
            arr[index] = x;
        } else {
            int k = queries[i][1], from = queries[i][2];
            from--;
            int result = arr[from];
            if (result <= k) {
                answers.push_back(1);
                continue;
            }
            bool is_done = false;
            for (int j = from + 1; j < n; ++j) {
                result = gcd(result, arr[j]);
                if (result <= k) {
                    answers.push_back(j - from + 1);
                    is_done = true;
                    break;
                }
            }
            if (!is_done) {
                answers.push_back(-1);
            }
        }
    }
    return answers;
}
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
signed main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        int n = uid(1, 10);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = uid(1, 1000);
        }
        int q = uid(1, 10);
        vector<array<int, 3>> queries(q);
        for (int i = 0; i < q; ++i) {
            auto& [move, first, second] = queries[i];
            move = uid(1, 2);
            if (move == 1) {
                first = uid(1, n);
                second = uid(1, 1000);
            } else {
                first = uid(1, 1000);
                second = uid(1, n);
            }
        }
        vector<int> answers_fast = solve_fast(a, queries);
        vector<int> answers_slow = solve_slow(a, queries);
        if (!answers_fast.empty() && answers_fast[0] >= 4) {
            cout << n << '\n';
            for (int i : a) cout << i << ' ';
            cout << '\n';
            cout << q << '\n';
            for (auto [move, first, second] : queries) {
                cout << move << ' ' << first << ' ' << second << '\n';
            }
            debug(answers_fast);
            debug(answers_slow);
            return 0;
        }
        if (answers_fast != answers_slow) {
            cout << n << '\n';
            for (int i : a) cout << i << ' ';
            cout << '\n';
            cout << q << '\n';
            for (auto [move, first, second] : queries) {
                cout << move << ' ' << first << ' ' << second << '\n';
            }
            debug(answers_fast);
            debug(answers_slow);
            return 0;
        }
    }
}
