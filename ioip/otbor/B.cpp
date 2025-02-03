#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int count_ = 0;
int ask(int dx, int dy) {
    if (count_ == 100) {
        assert(false);
    }
    count_++;
    cout << "? " << dx << ' ' << dy << endl;
    cout.flush();
    int answer = 1;
    cin >> answer;
    return answer;
}
void answer(int x, int y) {
    cout << "! " << x << ' ' << y << endl;
    int result;
    cin >> result;
    return;
}
pair<int, int> get() {
    int left = ask(-1, 0);
    int right = ask(2, 0);
    int one = ask(-1, 0);
    if (one == 1) {
        return {0, 0};
    }
    if (right - one == 1 && one - left == 1) {
        return {one - 1, 0};
    }
    if (left - one == 1 && one - right == 1) {
        return {-(one - 1), 0};
    }

    int up = ask(0, 1);
    int down = ask(0, -2);
    one = ask(0, 1);
    if (up - one == 1 && one - down == 1) {
        return {0, one - 1};
    }
    if (down - one == 1 && one - up == 1) {
        return {0, -(one - 1)};
    }
    return {-6969696969, -1};
}
void solve() {
    count_ = 0;
    ask(-10, 0);
    for (int i = 1; i <= 100; ++i) {
        auto [a, b] = get();
        if (a != -6969696969) {
            answer(a, b);
            return;
        }
        ask(1, 0);
    }
    assert(false);
}

signed main() {
    int t = 1;
    cin >> t;
    while (t--) solve();
}
