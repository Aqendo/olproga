#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("/home/ser/olproga/ege/17.txt", "r", stdin);
    int mx = INT_MIN;
    int a;
    while (cin >> a) {
        if (abs(a) % 100 == 17) {
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
        first += 1000 <= a && a <= 9999;
        first += 1000 <= b && b <= 9999;
        first += 1000 <= c && c <= 9999;
        int second = 0;
        second += a % 5 == 0;
        second += b % 5 == 0;
        second += c % 5 == 0;
        if (first == 2 && second && a + b + c > mx) {
            cnt += 1;
            s = max(s, a + b + c);
        }

        a = b;
        b = c;
    }
    cout << cnt << ' ' << s << endl;
}