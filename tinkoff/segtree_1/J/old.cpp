#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#define pb push_back
#define all(x) (x).begin(), (x).end()

using namespace std;
using vi = vector<int>;

const int open = 0;
const int close = 1;

struct Event {
    int x, y1, y2, type;  // type 0 - РѕС‚РєСЂС‹С‚РёРµ, 1 - Р·Р°РєСЂС‹С‚РёРµ
};

int Pow2Up(int x) {
    int p = 1;
    while (x > p) {
        p <<= 1;
    }
    return p;
}

inline int lc(int x) {
    return x << 1;
}

inline int rc(int x) {
    return x << 1 | 1;
}

class SegmentTree {
   private:
    vi coef;
    vi extra;
    vi nZorig;  // РґР»РёРЅР° РїРѕРєСЂС‹С‚РѕР№ С‡Р°СЃС‚Рё С‚РµРєСѓС‰РµРіРѕ РѕС‚СЂРµР·РєР° РґРѕ РїСЂРёРјРµРЅРµРЅРёСЏ extra
    vi len;     // РґР»РёРЅР° РѕС‚СЂРµР·РєР°

    void up(int l, int r, int v, int tl, int tr) {
        if (l > r) return;
        if (l == tl && r == tr) {
            extra[v]++;
            return;
        }
        int tm = (tl + tr) >> 1;
        up(l, min(r, tm), lc(v), tl, tm);
        up(max(l, tm + 1), r, rc(v), tm + 1, tr);
        nZorig[v] = (extra[lc(v)] > 0 ? len[lc(v)] : nZorig[lc(v)]) + (extra[rc(v)] > 0 ? len[rc(v)] : nZorig[rc(v)]);
        return;
    }

    void down(int l, int r, int v, int tl, int tr) {
        if (l > r) return;
        if (l == tl && r == tr && extra[v] > 0) {
            extra[v]--;
            return;
        }
        int tm = (tl + tr) >> 1;
        down(l, min(r, tm), lc(v), tl, tm);
        down(max(l, tm + 1), r, rc(v), tm + 1, tr);
        nZorig[v] = (extra[lc(v)] > 0 ? len[lc(v)] : nZorig[lc(v)]) + (extra[rc(v)] > 0 ? len[rc(v)] : nZorig[rc(v)]);
        return;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            len[v] = coef[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build(lc(v), tl, tm);
        build(rc(v), tm + 1, tr);
        len[v] = len[lc(v)] + len[rc(v)];
        return;
    }

   public:
    SegmentTree(const vi& ys) : coef((int)ys.size() - 1), extra(Pow2Up((int)coef.size()) << 1), nZorig(extra.size()), len(extra.size()) {
        for (int i = 0; i + 1 < ys.size(); i++) {
            coef[i] = ys[i + 1] - ys[i];
        }
        build(1, 0, (int)coef.size() - 1);
    }

    void up(int l, int r) {  // [l, r] - РѕС‚СЂРµР·РєРё
        up(l, r, 1, 0, (int)coef.size() - 1);
    }

    void down(int l, int r) {  // [l, r] - РѕС‚СЂРµР·РєРё
        down(l, r, 1, 0, (int)coef.size() - 1);
    }

    int getnZ() {
        if (extra[1] > 0) return len[1];
        return nZorig[1];
    }
};

int main() {
    int nR;
    cin >> nR;
    vector<Event> events;
    vi ys;
    for (int r = 0; r < nR; r++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 == y2 || x1 == x2) continue;
        events.pb({x1, y1, y2, open});
        events.pb({x2, y1, y2, close});
        ys.pb(y1);
        ys.pb(y2);
    }
    if (events.empty()) {
        cout << 0;
        return 0;
    }
    sort(all(ys));
    ys.erase(unique(all(ys)), ys.end());
    sort(all(events), [](const Event& l, const Event& r) {
        if (l.x != r.x) return l.x < r.x;
        return l.type < r.type;
    });
    SegmentTree ST(ys);
    int prevX = events[0].x;
    long long ans = 0;
    for (Event e : events) {
        if (e.x != prevX) {
            ans += 1LL * (e.x - prevX) * ST.getnZ();
        }
        int y1 = lower_bound(all(ys), e.y1) - ys.begin();
        int y2 = lower_bound(all(ys), e.y2) - ys.begin() - 1;
        if (e.type == open) {
            ST.up(y1, y2);
            // cout << "up: x = " << e.x << " y1 = " << e.y1 << " y2 = " << e.y2 << " nZ = " << ST.getnZ() << "\n";
        } else {
            assert(e.type == close);
            ST.down(y1, y2);
			// cout << "down: x = " << e.x << " y1 = " << e.y1 << " y2 = " << e.y2 << " nZ = " << ST.getnZ() << "\n";
        }
        prevX = e.x;
    }
    cout << ans;
	return 0;
}