#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("/home/ser/olproga/input.txt", "r", stdin);
    int mx = INT_MIN;
    int a;
    while (cin >> a) {
        if (abs(a) % 100 == 13) {
            mx = max(mx, a);
        }
    }
    cin.clear();
    freopen("/home/ser/olproga/input.txt", "r", stdin);
    int b, c;
    cin >> a >> b;
    int cnt = 0;
    int s = 0;
    while (cin >> c) {
        int first = 0;
        first += 100 <= abs(a) && abs(a) <= 999;
        first += 100 <= abs(b) && abs(b) <= 999;
        first += 100 <= abs(c) && abs(c) <= 999;
        if (first == 2 && a + b + c <= mx) {
            cnt += 1;
            s = max(s, a + b + c);
        }
        a = b;
        b = c;
    }
    cout << cnt << ' ' << s << endl;
}