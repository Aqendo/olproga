#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int OFFSET = 1e14 + 69;
struct Node {
    int lazy;
    int cnt_mn;
    int mn;
    Node *l = nullptr, *r = nullptr;
    void add(Node *&cur, int lx, int rx, int lq, int rq, int toadd) {
        if (!cur) {
            cur = new Node({.lazy = 0, .cnt_mn = rx - lx + 1, .mn = 0});
        }
        if (lq > rq) return;
        if (lq == lx && rq == rx) {
            cur->lazy += toadd;
            cur->mn += toadd;
            return;
        }
        int m = (lx + rx) >> 1;
        add(cur->l, lx, m, lq, min(m, rq), toadd);
        add(cur->r, m + 1, rx, max(m + 1, lq), rq, toadd);
        cur->combine();
    }
    void combine() {
        if (l->mn < r->mn) {
            cnt_mn = l->cnt_mn, mn = l->mn;
        } else if (l->mn > r->mn) {
            cnt_mn = r->cnt_mn, mn = r->mn;
        } else {
            cnt_mn = l->cnt_mn + r->cnt_mn;
            mn -= lazy;
        }
        mn += lazy;
    }
};

const int SZ = 1e15;

Node root({.lazy = 0, .cnt_mn = SZ, .mn = 0});

int get_full() {
    int ans = root.mn ? SZ : SZ - root.cnt_mn;
    return ans;
}

void add(int l, int r, int toadd) {
    static Node *cur = &root;
    cur->add(cur, 0, SZ - 1, l, r, toadd);
}
void add(int l, int r) {
    add(l, r, 1);
}
void del(int l, int r) {
    add(l, r, -1);
}

const int OPEN = -1, CLOSE = 1;

struct Event {
    int x, type, up, down;
};

void solve() {
    int k, n;
    cin >> k >> n;
    pair<int, int> now = {0, 0};
    vector<array<int, 4>> rects(n);
    for (int i = 0; i < n; ++i) {
        char move;
        int d;
        cin >> move >> d;
        if (move == 'N') {
            rects[i] = {
                now.first, now.second, now.first + k, now.second + d + k};
            now.second += d;
        } else if (move == 'S') {
            rects[i] = {
                now.first, now.second - d, now.first + k, now.second + k};
            now.second -= d;
        } else if (move == 'W') {
            rects[i] = {
                now.first - d, now.second, now.first + k, now.second + k};
            now.first -= d;
        } else {
            rects[i] = {
                now.first, now.second, now.first + d + k, now.second + k};
            now.first += d;
        }
    }
    // for (auto [a, b, c, d] : rects) {
    //     cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
    // }
    vector<Event> events(n * 2);
    for (int i = 0; i < n; ++i) {
        events[i << 1] = {
            .x = rects[i][0],
            .type = OPEN,
            .up = OFFSET + rects[i][3],
            .down = OFFSET + rects[i][1]};
        events[i << 1 | 1] = {
            .x = rects[i][2],
            .type = CLOSE,
            .up = OFFSET + rects[i][3],
            .down = OFFSET + rects[i][1]};
    }
    sort(events.begin(), events.end(), [](Event &l, Event &r) {
        if (l.x != r.x)
            return l.x < r.x;
        return l.type < r.type;
    });
    int answer = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (i != 0) {
            answer += get_full() * (events[i].x - events[i - 1].x);
        }
        if (events[i].type == OPEN) {
            add(events[i].down, events[i].up - 1);
        } else {
            del(events[i].down, events[i].up - 1);
        }
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}