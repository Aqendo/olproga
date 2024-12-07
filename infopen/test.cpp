#include <bits/stdc++.h>

using namespace std;
int main() {
    vector<int> a = {3, 4, 5, 6, 7, 8};
    int k = 9;
    auto it = lower_bound(a.begin(), a.end(), k);
    cout << it - a.begin() << endl;
}