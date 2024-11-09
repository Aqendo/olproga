#include "bits/stdc++.h"
#define int int64_t
using namespace std;

void solve() {
    int x, y, k, l;
    cin >> x >> y >> k >> l;
    if (x > y) swap(x, y);
    int lowest_in = 0;
    if (x <= 0) {
        lowest_in = -(abs(x) / k * k);
    } else {
        lowest_in = (x + k - 1) / k * k;
    }
    int highest_in = 0;
    if (y > 0) {
        highest_in = y / k * k;
    } else {
        highest_in = -((-y + k - 1) / k * k);
    }
    if (lowest_in > highest_in) {
        swap(lowest_in, highest_in);
        if (x == y) {
            if (highest_in - l <= x) {
                cout << 0 << endl;
            } else {
                cout << 1 << endl;
            }
            return;
        }
        y = min(y, highest_in - l);
        x = max(x, lowest_in + l);
        if (x > y) {
            cout << 0 << endl;
            return;
        }
        cout << max<int>(0, (y - x + 2 * l - 1) / (2 * l)) << endl;
        return;
    }
    bool is_same = x == y;
    x = max(x, lowest_in - k + l);
    y = min(y, highest_in + k - l);
    if (!is_same && x >= y) {
        cout << 0 << endl;
        return;
    }
    if (x > y) {
        cout << 0 << endl;
        return;
    }
    long long answer = 0;
    // cout << lowest_in << ' ' << highest_in << endl;
    if (lowest_in != highest_in) {
        answer += (highest_in / k - lowest_in / k) * ((k - 1) / (2 * l));
    }
    if (lowest_in - l > x) {
        answer += (lowest_in - l - x + 2 * l - 1) / (2 * l);
    }
    if (highest_in + l < y) {
        answer += (y - highest_in - l + 2 * l - 1) / (2 * l);
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
