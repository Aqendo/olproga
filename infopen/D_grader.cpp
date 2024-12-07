#include <bits/stdc++.h>

#include "D.cpp"
int main() {
    int n, t;
    cin >> n >> t;
    vector<int> r(t), c(t), v(t);
    for (int i = 0; i < t; ++i) {
        cin >> r[i];
    }
    for (int i = 0; i < t; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < t; ++i) {
        cin >> v[i];
    }
    cout << solve(n, t, r, c, v) << endl;
}