#include <bits/stdc++.h>

#define fi first
#define se second

#define pb push_back
#define sz(x) (int)x.size()

#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define rf(i, a, b) for (int i = (a); i >= (b); --i)
#define fe(x, a) for (auto& x : a)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e5 + 1;

int a[N];

struct node {
    int val;
    int pos;

    void combine(node& l, node r) {
        if (l.val > r.val) {
            val = l.val;
            pos = l.pos;
        } else {
            val = r.val;
            pos = r.pos;
        }
    }
};

struct {
    node t[4 * N];

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v].val = a[tl];
            t[v].pos = tl;
            return;
        }

        int tm = (tl + tr) >> 1;

        build(v << 1, tl, tm);
        build(v << 1 | 1, tm + 1, tr);

        t[v].combine(t[v << 1], t[v << 1 | 1]);
    }
    node get(int v, int tl, int tr, int l, int r, int x = -1) {
        if (l > r) {
            node br;
            br.val = -1;
            return br;
        }

        if (tl == tr && t[v].pos == x) {
            node br;
            br.val = -1;
            br.pos = -1;
            return br;
        }
        if (tl == l && tr == r && t[v].pos != x) {
            return t[v];
        }

        int tm = (tl + tr) >> 1;

        node g1 = get(v << 1, tl, tm, l, min(tm, r), x);
        node g2 = get(v << 1 | 1, tm + 1, tr, max(tm + 1, l), r, x);

        return g1.val > g2.val ? g1 : g2;
    }
} T;

int solve(int p, int k, int n) {
    if (k == 1) {
        return 1;
    }

    int ans = 0;

    if (p + k - 1 <= n) {
        node cur = T.get(1, 1, n, p, p + k - 1);
        node sec = T.get(1, 1, n, p, p + k - 1, cur.pos);

        int br = 1e9 + 52;
        if (p + k <= n) {
            br = a[p + k];
        }

        if (br > cur.val) {
            if (cur.pos != p) {
                if (sec.val == a[p] || sec.pos < cur.pos) {
                    ans++;
                }

                ans += (p + k - 1) - cur.pos;
            } else {
                ans += k - 1;
            }
        } else {
            if (sec.pos < cur.pos && sec.val < a[p + k]) {
                //                if (sec.val == a[p] && a[p] < a[p + k]) {
                ans++;
            }
        }
    }
    if (p - k + 1 >= 1) {
        node cur = T.get(1, 1, n, p - k + 1, p);
        node sec = T.get(1, 1, n, p - k + 1, p, cur.pos);

        int br = 1e9 + 52;
        if (p - k >= 1) {
            br = a[p - k];
        }

        if (br > cur.val) {
            if (cur.pos != p) {
                if (sec.val == a[p] || sec.pos > cur.pos) {
                    ans++;
                }

                ans += cur.pos - (p - k + 1);
            } else {
                ans += k - 1;
            }
        } else {
            if (sec.pos > cur.pos && sec.val < a[p - k]) {
                //                if (sec.val == a[p] && a[p] < a[p - k]) {
                ans++;
            }
        }
    }

    return ans;
}

int brut(int n, int k, int p) {
    if (k == 1) {
        return 1;
    }

    int ans = 0;
    fr(i, 1, n) {
        int prev = i - 1, next = i + 1;

        int cnt = 1;
        while (cnt < k) {
            if (prev >= 1 && next <= n && a[prev] < a[next]) {
                cnt++;
                if (prev == p) {
                    if (k == cnt) {
                        ans++;
                        break;
                    } else {
                        break;
                    }
                }
                prev--;

            } else if (prev >= 1 && next <= n && a[prev] > a[next]) {
                cnt++;
                if (next == p) {
                    if (k == cnt) {
                        ans++;
                        break;
                    } else {
                        break;
                    }
                }
                next++;
            } else if (prev >= 1) {
                cnt++;
                if (prev == p) {
                    if (k == cnt) {
                        ans++;
                        break;
                    } else {
                        break;
                    }
                }
                prev--;
            } else if (next <= n) {
                cnt++;
                if (next == p) {
                    if (k == cnt) {
                        ans++;
                        break;
                    } else {
                        break;
                    }
                }
                next++;
            } else {
                break;
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    srand(time(0));

    int t = 1000;
    while (t--) {
        int n, q;
        n = rand() % 10;
        q = rand() % 1000;
        //        cin >> n >> q;

        fr(i, 1, n) {
            a[i] = i;
            //            cin >> a[i];
        }

        int ff = 1000;
        while (ff--) {
            int u = rand() % n + 1;
            int v = rand() % n + 1;

            swap(a[u], a[v]);
        }

        T.build(1, 1, n);

        cout << n << " " << q << endl;
        fr(i, 1, n) {
            cout << a[i] << " ";
        }
        cout << endl;
        while (q--) {
            int p, k;
            p = rand() % n + 1;
            k = rand() % n + 1;
            // cin >> p >> k;
            if (brut(n, k, p) != solve(p, k, n)) {
                cout << p << "#" << k << endl;
                cout << brut(n, k, p) << " " << solve(p, k, n) << endl;
                cout << endl;
            }
        }
    }
#else
    int n, q;
    cin >> n >> q;

    fr(i, 1, n) {
        cin >> a[i];
    }

    T.build(1, 1, n);

    while (q--) {
        int p, k;
        cin >> p >> k;

        //            cout << brut(n, k, p) << endl;
        cout << solve(p, k, n) << endl;
    }
#endif

    return 0;
}
