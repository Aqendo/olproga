#include <bits/stdc++.h>

using namespace std;

const int64_t INF = 1e18;
struct Node {
    int64_t mn;
    int64_t cnt;
};
struct Segtree {
    vector<Node> tree;
    vector<int64_t> mop;
    Segtree(int64_t n) : tree(4 * n, {0, 1}), mop(4 * n, 0) { build(1, 0, n - 1); }
    void build(int64_t x, int64_t lx, int64_t rx) {
        if (lx == rx) {
            return;
        }
        int64_t m = (lx + rx) >> 1;
        build(x << 1, lx, m);
        build(x << 1 | 1, m + 1, rx);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1], x, lx, rx);
    }
    Node combine(Node l, Node r, int64_t x, int64_t lx, int64_t rx) {
        l.mn += mop[x << 1];
        r.mn += mop[x << 1 | 1];
        if (l.mn == r.mn) {
            return {l.mn, l.cnt + r.cnt};
        }
        if (l.mn < r.mn) {
            return l;
        }
        return r;
    }
    Node combine_get(Node l, Node r) {
        if (l.mn == r.mn) {
            return {l.mn, l.cnt + r.cnt};
        }
        if (l.mn < r.mn) {
            return l;
        }
        return r;
    }
    void push(int64_t x, int64_t lx, int64_t rx) {
        if (lx == rx) {
            tree[x].mn += mop[x];
            mop[x] = 0;
            return;
        }
        mop[x << 1] += mop[x];
        mop[x << 1 | 1] += mop[x];
        mop[x] = 0;
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1], x, lx, rx);
    }
    void add(int64_t x, int64_t lx, int64_t rx, int64_t l, int64_t r, int64_t to_add) {
        push(x, lx, rx);
        if (l == lx && r == rx) {
            mop[x] += to_add;
            return;
        }
        if (l > r) return;
        int64_t m = (lx + rx) >> 1;
        add(x << 1, lx, m, l, min(r, m), to_add);
        add(x << 1 | 1, m + 1, rx, max(m + 1, l), r, to_add);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1], x, lx, rx);
    }
    Node get(int64_t x, int64_t lx, int64_t rx, int64_t l, int64_t r) {
        push(x, lx, rx);
        if (l > r) {
            return {INF, 0};
        }
        if (l == lx && r == rx) {
            return {tree[x].mn + mop[x], tree[x].cnt};
        }
        int64_t m = (lx + rx) >> 1;
        Node g1 = get(x << 1, lx, m, l, min(r, m));
        Node g2 = get(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        return combine_get(g1, g2);
    }
};
struct Rectangle {
    int64_t sx, sy, ex, ey, index;
};
enum ACTION { OPEN = 1, CLOSE };
struct Event {
    int64_t index;
    int64_t action;
    int64_t x;
};
void solve() {
    int64_t n;
    cin >> n;
    Rectangle rects[n];
    Segtree seg(50005);
    vector<Event> events(n * 2 + 1);
    int64_t index = 1;
    for (int64_t i = 0; i < n; ++i) {
        cin >> rects[i].sx >> rects[i].sy >> rects[i].ex >> rects[i].ey;
        rects[i].index = i;
        events[index++] = {i, OPEN, rects[i].sx};
        events[index++] = {i, CLOSE, rects[i].ex};
    }
    sort(events.begin() + 1, events.end(), [](Event& ev1, Event& ev2) {
        if (ev1.x != ev2.x) return ev1.x < ev2.x;
        return ev1.action < ev2.action;
    });
    events[0] = events[1];
    int64_t ans = 0;
    for (size_t i = 1; i < events.size(); ++i) {
        Event& event = events[i];
        int64_t diff = event.x - events[i - 1].x;
        Node mnn = seg.get(1, 0, 50004, 0, 50004);
        if (mnn.mn == 0) {
            ans += (50005 - mnn.cnt) * diff;
        } else {
            ans += 50005 * diff;
        }
        if (event.action == OPEN) {
            seg.add(1, 0, 50004, rects[event.index].sy, rects[event.index].ey - 1, 1);
        } else {
            seg.add(1, 0, 50004, rects[event.index].sy, rects[event.index].ey - 1, -1);
        }
    }
    cout << ans << '\n';
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}