#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int get_xor(int n) {
    if (n <= 0) return 0;
    int mod = n % 4;
    if (mod == 0)
        return n;
    else if (mod == 1)
        return 1;
    else if (mod == 2)
        return n + 1;
    else
        return 0;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int l, r, i, k;
        cin >> l >> r >> i >> k;
        int result = get_xor(r) ^ get_xor(l - 1);
        int suff = (1ll << i);
        int upper = r >> i;
        int lower = l >> i;
        if (r % suff < k) {
            upper--;
        }
        if (l % suff > k) {
            lower++;
        }
        int added = get_xor(upper) ^ get_xor(lower - 1);
        result = (result ^ (added << i));
        if ((upper - lower) % 2 == 0) {
            result ^= k;
        }
        cout << result << endl;
    }
}