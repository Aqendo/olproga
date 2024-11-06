#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("/home/ser/olproga/ege/17.txt", "r", stdin);
    vector<int> a;
    int x;
    while (cin >> x) {
        a.push_back(x);
    }
    int n = a.size();
    int cnt = 0;
    int mx_pair = INT_MIN;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if ((a[i] + a[j]) % 9 == 0) {
                cnt++;
                mx_pair = max(mx_pair, a[i] + a[j]);
            }
        }
    }
    cout << cnt << ' ' << mx_pair << endl;
}