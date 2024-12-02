#include "bits/stdc++.h"
using namespace std;
#define int int64_t

int ask(int a, int d) {
    cout << "? " << a << ' ' << d << endl;
    int answer;
    cin >> answer;
    return answer;
}

void solve() {
    int power = 1;
    int answer = 0;
    for (int i = 0; i < 62; ++i) {
        if (power * 2 > 2000000) break;
        if (!ask(power * 2, answer)) {
            answer += power;
        }
        power <<= 1;
    }
    cout << "! " << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
