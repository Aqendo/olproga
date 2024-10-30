#include "bits/stdc++.h"
using namespace std;

bool is_composite[1000010];

void solve() {
    int a, b;
    cin >> a >> b;
    for (int i = 2; i <= b; ++i) {
        if (!is_composite[i]) {
            if (a <= i) {
                cout << i << ' ';
            }
        }
        for (int j = i; (long long)j * i <= b; ++j) {
            is_composite[(long long)j * i] = true;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
