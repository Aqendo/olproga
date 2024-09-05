#include <bits/stdc++.h>
// #define int int64_t
using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif
struct Hash {
    const int MOD = 1e9 + 7;
    const int p = 113;
    static const int MAXN = 200000 + 42;

    int binpow(int n, int pow) {
        int ans = 1;
        while (pow) {
            if (pow & 1) {
                ans = mult(ans, n);
            }
            n = mult(n, n);
            pow >>= 1;
        }
        return ans;
    }

    int sub(int a, int b) const { return a < b ? a - b + MOD : a - b; }

    int add(int a, int b) { return a + b >= MOD ? a + b - MOD : a + b; }

    int mult(int a, int b) const { return (a + 0ll) * b % MOD; }

    int powP[MAXN];
    int hsh[MAXN];

    void precalcPowers() {
        powP[0] = 1;
        for (int i = 1; i < MAXN; ++i) {
            powP[i] = mult(powP[i - 1], p);
        }
    }

    string s;

    void getHash() {
        hsh[0] = 0;
        //    for (int i = 0; i < s.size(); ++i) {
        //      hsh[i + 1] = (mult(hsh[i], p) + s[i]) % MOD;
        //    }
        for (int i = 0; i < s.size(); ++i) {
            hsh[i + 1] = add(mult(hsh[i], p), s[i]);
        }
    }

    int substr(int l, int r) {
        //    return mult(sub(hsh[r], hsh[l - 1]), binpow(powP[l - 1], MOD - 2));
        // hsh[n] = s[0] * p[n]
        return sub(hsh[r], mult(hsh[l - 1], powP[r - l + 1]));
    }

    Hash(string& s) : s(s) {
        precalcPowers();
        getHash();
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    string baked = "#";
    for (char i : s) {
        baked += i;
        baked += '#';
    }
    // cout << baked << endl;
    Hash straight(baked);
    reverse(baked.begin(), baked.end());
    Hash reverse(baked);
    auto f = [&](int i, int size) -> bool {
        int lStraight = i + 1;
        int rStraight = i + size;
        int centerReverse = (int)baked.size() - i - 1;
        int lReverse = centerReverse + 1;
        int rReverse = centerReverse + size;
        return straight.substr(lStraight, rStraight) ==
               reverse.substr(lReverse, rReverse);
    };
    long long answer = 0;
    for (int i = 0; i < baked.size(); ++i) {
        int l = 1, r = min(i + 1, (int)baked.size() - i) + 1;
        int r_old = r;
        // cout << l << ' ' << r << endl;
        while (r - l > 1) {
            int m = (r + l) >> 1;
            if (m == r_old) break;
            if (f(i, m)) {
                l = m;
            } else {
                r = m;
            }
        }
        answer += l;
        cout << l << ' ';
    }
    cout << endl;
    cout << answer << endl;
    cout << (answer - s.length() - 1) / 2 << endl;
    cout << (answer - s.length() - 1) / 2 - (int)s.size() << endl;

    return 0;
}