#include "bits/stdc++.h"
using namespace std;

long long gcd(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long g = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

void solve() {
    long long a, b, c;
    cin >> a >> b >> c;
    if (c % gcd(a, b) != 0) {
        cout << "Impossible\n";
        return;
    }
    long long x, y;
    long long g = gcd(a, b, x, y);
    // cout << g << endl;
    // cout << x << ' ' << y << endl;
    int answer_x = x * c / g;
    int answer_y = y * c / g;
    if (answer_x >= 0) {
        int t = 0;
        while (--t) {
            if (answer_x + t * b / g < 0) {
                answer_x = answer_x + (t + 1) * b / g;
                answer_y = answer_y - (t + 1) * a / g;
                break;
            }
        }
    } else {
        int t = 0;
        while (++t) {
            if (answer_x + t * b / g >= 0) {
                answer_x = answer_x + t * b / g;
                answer_y = answer_y - t * a / g;
                break;
            }
        }
    }

    cout << answer_x << ' ' << answer_y << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
