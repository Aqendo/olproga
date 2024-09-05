#include "bits/stdc++.h"

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int money = 0, apple = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if (money + b * apple < -70) {
            if (money < 0 && apple > -5) {
                cout << "S" << endl;
                money += b;
                apple--;
            } else {
                cout << "B" << endl;
                money -= b;
                apple++;
            }
            continue;
        }
        if (a >= b && apple < 5) {
            cout << "B" << endl;
            apple++;
            money -= b;
        } else if (a <= b) {
            cout << "S" << endl;
            apple--;
            money += b;
        } else {
            if (apple < 5) {
                cout << "B" << endl;
                apple++;
                money -= b;
            } else if (apple == 5) {
                cout << "S" << endl;
                apple--;
                money += b;
            } else {
                cout << "X" << endl;
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    solve();
}