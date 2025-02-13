#include <bits/stdc++.h>
using namespace std;
#define int int64_t

struct Node {
    int mx, mn;
};
struct {
    vector<Node> tree;
    void init(const vector<int> &a, int n) {
        tree.assign(2 * n - 1, {INT_MIN, INT_MAX});
        build(a, 0, 0, n - 1);
    }
    void build(const vector<int> &a, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {a[lx] + lx, a[lx] + lx};
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x + 1, lx, m);
        build(a, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    Node combine(const auto &l, const auto &r) {
        return {
            max(l.mx, r.mx),
            min(l.mn, r.mn)};
    }
    pair<int, int> get(int x, int lx, int rx, int l, int r, int leq) {
        if (l > r) return {-2, 0};
        if (l == lx && r == rx) {
            if (lx == rx) {
                if (tree[x].mx <= leq) return {lx, 0};
                return {-1, 1};
            }
            int m = (lx + rx) >> 1;
            if (tree[x + 1].mx <= leq) {
                if (tree[x + 2 * (m - lx + 1)].mx <= leq) {
                    return {rx, 0};
                }
                if (tree[x + 2 * (m - lx + 1)].mn <= leq) {
                    return get(x + 2 * (m - lx + 1), m + 1, rx, max(l, m + 1), r, leq);
                }
                return {m, 0};
            } else if (tree[x + 1].mn <= leq) {
                return get(x + 1, lx, m, l, min(m, r), leq);
            }
            return {-1, 1};
        }
        int m = (lx + rx) >> 1;
        pair<int, int> s1 = get(x + 1, lx, m, l, min(m, r), leq);
        if (s1.second > 0) return s1;
        pair<int, int> s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, leq);
        return {max(s1.first, s2.first), s2.second};
    }
} seg;
vector<int> solve_slow(const vector<int> &a, const vector<pair<int, int>> &qs) {
    int n = a.size();
    int q = qs.size();
    vector<int> answers(qs.size());
    for (int i_ = 0; i_ < q; ++i_) {
        auto [l, x] = qs[i_];
        int answer = 0;
        for (int i = l - 1; i < n; ++i) {
            if (x >= a[i]) {
                answer++;
                x--;
            } else
                break;
        }
        answers[i_] = answer;
    }
    return answers;
}
vector<int> solve_fast(const vector<int> &a, const vector<pair<int, int>> &qs) {
    int n = a.size();
    seg.init(a, n);
    int q = qs.size();
    vector<int> answers(q);
    for (int i = 0; i < q; ++i) {
        auto [l, x] = qs[i];
        auto [res, was] = seg.get(0, 0, n - 1, l - 1, n - 1, x + l - 1);
        // cout << res << '\n';
        if (res == -1) {
            answers[i] = 0;
            continue;
        }
        answers[i] = res - (l - 1) + 1;
    }
    return answers;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    while (true) {
        int n = uid(1, 20);
        int q = uid(1, 100);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = uid(1, 100);
        }
        vector<pair<int, int>> qs(q);
        for (int i = 0; i < q; ++i) {
            qs[i] = {uid(1, n), uid(1, 1000)};
        }
        vector<int> slow = solve_slow(a, qs);
        vector<int> fast = solve_fast(a, qs);

        if (slow != fast) {
            cout << n << endl;
            for (int i : a) cout << i << ' ';
            cout << endl;
            cout << q << endl;
            for (auto [u, j] : qs) cout << u << ' ' << j << '\n';
            for (int i : slow) cout << i << ' ';
            cout << endl;
            for (int i : fast) cout << i << ' ';
            cout << endl;
            return 0;
        }
    }
}
