#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main() {
    int n = uniform_int_distribution<int>(1,40)(rng);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        char move = "+?"[uniform_int_distribution<int>(0,1)(rng)];
        cout << move << ' ';
        if (move == '+') {
            cout << uniform_int_distribution<int>(0,1000000000)(rng) << '\n';
        } else {
            int first = uniform_int_distribution<int>(0,1000000000)(rng);
            cout << first << ' ' << uniform_int_distribution<int>(first, 1000000000)(rng) << '\n';
        }
    }
}
