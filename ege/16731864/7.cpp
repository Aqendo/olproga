#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("/home/ser/olproga/ege/17.txt", "r", stdin);
    int mn = INT_MAX;
    int a;
    while (cin >> a) {
        int del = abs(a) % 100;
        if (10 <= del && del <= 99 && del % 11 == 0) {
            mn = min(mn, a);
        }
    }
    cin.clear();
    freopen("/home/ser/olproga/ege/17.txt", "r", stdin);
    cin >> a;
    int b;
    int cnt = 0;
    int s = 0;
    while (cin >> b) {
        int first = 0;
        int last = abs(a) % 10;
        int prelast = abs(b) % 100 / 10;
        if (last == prelast) {
            first += 1;
        }
        last = abs(b) % 10;
        prelast = abs(a) % 100 / 10;
        if (last == prelast) {
            first += 1;
        }
        int second = 0;
        second += a % 13 == 0;
        second += b % 13 == 0;
        if (first && second == 1 && (a * a) + (b * b) <= mn * mn) {
            cnt += 1;
            s = max(s, (a * a) + (b * b));
        }
        a = b;
    }
    cout << cnt << ' ' << s << endl;
}