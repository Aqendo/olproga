#include "bits/stdc++.h"
using namespace std;
int already[1000300];
int ask(int x) {
    if (already[x]) return already[x];
    int now;
    cout << "? " << x << endl;
    cin >> now;
    already[x] = now;
    return now;
}

void solve() {
    int n;
    cin >> n;
    int l = 1, r = n;
    while (l != r) {
        int m = (1ll * l + r) >> 1;
        int now = ask(m);
        int post_now = -69;
        if (m != n) {
            post_now = ask(m + 1);
        }
        if (now == post_now) {
            if (m % 2 != 0) {
                l = m + 1;
            } else {
                r = m;
            }
        } else {
            if (m % 2 == 0) {
                l = m + 1;
            } else {
                r = m;
            }
        }
    }
    int answer = ask(l);
    cout << "! " << answer << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
