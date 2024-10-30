#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n;
    cin >> n;
    int l = 1, r = n;
    while (l != r) {
        int m = (1ll * l + r) / 2;
        cout << m << endl;
        int answer;
        cin >> answer;
        if (answer == -1) {
            r = m - 1;
        } else if (answer == 1) {
            l = m + 1;
        } else {
            return;
        }
    }
    cout << l << endl;
}

int main() {
    solve();
}
