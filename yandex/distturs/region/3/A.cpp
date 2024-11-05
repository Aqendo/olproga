#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    if (n % 2 == 0 && m % 2 == 0) {
        cout << "2\n";
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < m / 2; ++j) {
                cout << "1 2 ";
            }
            cout << '\n';
            for (int j = 0; j < m / 2; ++j) {
                cout << "2 1 ";
            }
            cout << '\n';
        }
    } else {
        cout << 3 << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << (i + j + (i == n - 1 && i % 3 == 0) + (j == m - 1 && j % 3 == 0)) % 3 + 1 << ' ';
            }
            cout << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}