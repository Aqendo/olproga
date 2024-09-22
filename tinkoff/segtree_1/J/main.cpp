#include "bits/stdc++.h"
using namespace std;
#define int long long
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

#ifndef SEREGA
#define printf(...)
#define debug(...)
#endif

const int offset = 1e9 + 12;
struct Event {
    // 0 - close, 1 - open
    int event_type;
    int x_coord;
    int y_start, y_end;
};
string to_string(const Event& ev) {
    return "(x=" + to_string(ev.x_coord - offset) + "; [" + to_string(ev.y_start - offset) + ".." + to_string(ev.y_end - offset) + "])";
}
bool operator<(const Event& l, const Event& r) {
    if (l.x_coord != r.x_coord) return l.x_coord < r.x_coord;
    return l.event_type > r.event_type;
}

struct Node {
    int mn;
    int cnt;
    int adder;
    Node *l = nullptr, *r = nullptr;
};

struct Segtree {
    Node root;
    int n;

    Segtree(int n_) : n(n_) { root = {.mn = 0, .cnt = n_, .adder = 0}; }
    void combine(Node*& tree) {
        if (tree->l->mn < tree->r->mn) {
            tree->cnt = tree->l->cnt;
            tree->mn = tree->l->mn;
            return;
        } else if (tree->l->mn > tree->r->mn) {
            tree->cnt = tree->r->cnt;
            tree->mn = tree->r->mn;
            return;
        }
        tree->mn = tree->l->mn;
        tree->cnt = tree->l->cnt + tree->r->cnt;
    }
    void add(Node*& tree, int lx, int rx, int l, int r, int v) {
        if (!tree) {
            tree = new Node({
                .mn = 0,
                .cnt = rx - lx + 1,
            });
        }
        if (l > r) return;
        if (lx == l && rx == r) {
            tree->adder += v;
            tree->mn += v;
            return;
        }
        int m = (lx + rx) >> 1;
        add(tree->l, lx, m, l, min(m, r), v);
        add(tree->r, m + 1, rx, max(m + 1, l), r, v);
        // debug(tree->x * 2, "and", tree->x * 2 + 1, "should be created");
        combine(tree);

        tree->mn += tree->adder;
    }
};
void solve() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0 << '\n';
        return;
    }
    vector<Event> events;
    events.reserve(n * 2);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += offset;
        x2 += offset;
        y1 += offset;
        y2 += offset;
        events.push_back({.event_type = 1, .x_coord = x1, .y_start = y1, .y_end = y2});
        events.push_back({.event_type = 0, .x_coord = x2, .y_start = y1, .y_end = y2});
    }
    sort(events.begin(), events.end());
    Segtree seg(2e9 + 100);
    Node* iter = &seg.root;
    seg.add(iter, 0, seg.n - 1, events[0].y_start + 1, events[0].y_end, 1);
    int answer = 0;
    for (int i = 1; i < events.size(); ++i) {
        int times = events[i].x_coord - events[i - 1].x_coord;
        int delta = (seg.root.mn == 0 ? (2e9 + 100 - seg.root.cnt) : 0);
        // debug("times=", times, " delta=", delta);
        // debug(events[i]);
        delta *= times;
        // debug(delta);
        answer += delta;
        if (events[i].event_type == 0) {
            // close
            // debugp("closed");
            seg.add(iter, 0, seg.n - 1, events[i].y_start + 1, events[i].y_end, -1);
        } else {
            seg.add(iter, 0, seg.n - 1, events[i].y_start + 1, events[i].y_end, 1);
        }
        // debug();
    }
    cout << answer << '\n';
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}