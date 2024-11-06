#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("/home/ser/olproga/ege/17.txt", "r", stdin);
    int mx = INT_MIN;
    int a;
    while (cin >> a) {
        if (abs(a) % 100 == 13) {
            mx = max(mx, a);
        }
    }
    cin.clear();
    freopen("/home/ser/olproga/ege/17.txt", "r", stdin);
    cin >> a;
    int b, c;
    cin >> b;
    int cnt = 0;
    int s = 0;
    while (cin >> c) {
        int first = 0;
        first += 100 <= a && a <= 999;
        first += 100 <= b && b <= 999;
        first += 100 <= c && c <= 999;
        if (first == 2 && a + b + c <= mx) {
            cnt++;
            s = max(s, a + b + c);
        }

        a = b;
        b = c;
    }
    cout << cnt << ' ' << s << endl;
}