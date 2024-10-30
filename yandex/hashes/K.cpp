#include "bits/stdc++.h"
%:define int int64_t
using namespace std;

struct Hash {
    vector<long long> po, h;
    long long p, mod;
    Hash(vector<int>& s, long long p_, long long mod_) : po(s.size() + 1), h(s.size() + 1), p(p_), mod(mod_) {
        po[0] = 1;
        for (size_t i = 1; i <= s.size(); ++i) {
            po[i] = (po[i - 1] * p) % mod;
            h[i] = (h[i - 1] * p + s[i - 1] + 100) % mod;
        }
    }
    long long substr(int l, int r) {
        // cout << l << ' ' << r << ' ' << h.size() << endl;
        return ((h[r] - h[l - 1] * po[r - l + 1]) % mod + mod) % mod;
    }
};

bool solve(string from, string to, int already) {
    to += to;
    vector<int> difffrom(from.size() - 1);
    for (int i = 0; i < (int)from.size() - 1; ++i) {
        difffrom[i] = from[i + 1] - from[i];
    }
    vector<int> diffto(to.size() - 1);
    for (int i = 0; i < (int)to.size() - 1; ++i) {
        diffto[i] = to[i + 1] - to[i];
    }
    Hash hfrom(difffrom, 133, 1e9 + 9);
    Hash hto(diffto, 133, 1e9 + 9);
    for (size_t i = 1; i + difffrom.size() - 1 <= diffto.size(); ++i) {
        if (hfrom.substr(1, (int)difffrom.size()) == hto.substr(i, i + difffrom.size() - 1)) {
            cout << "Success\n";
            cout << i - 1 << ' ' << ((already + (int)to[i - 1] - (int)from[0]) % 26 + 26) % 26 << endl;
            exit(0);
            return true;
        }
    }
    return false;
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // %:define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    //     while (true) {
    //         int n = 10;
    //         string s(n, ' ');
    //         int offset = uid(-25, 25);
    //         for (int i = 0; i < n; ++i) {
    //             if (offset <= 0) {
    //                 s[i] = (char)uid((int)'a' - offset, (int)'z');
    //             } else {
    //                 s[i] = (char)uid((int)'a', (int)'z' - offset);
    //             }
    //         }
    //         int len_first = uid(0, n);
    //         string rev = s.substr(len_first) + s.substr(0, len_first);
    //         for (int i = 0; i < offset; ++i) {
    //             for (char& c : rev) {
    //                 c++;
    //             }
    //             solve(s, rev);
    //         }
    //         for (char& c : rev) {
    //             c += offset;
    //         }
    //         if (!solve(s, rev)) {
    //             cout << s << endl << rev << endl;
    //             return 1;
    //         }
    //         return 0;
    //     }
    int n;
    cin >> n;
    string from, to;
    cin >> from >> to;
    for (int offset = -25; offset <= 25; ++offset) {
        string new_from = from;
        for (int i = 0; i < n; ++i) {
            new_from[i] = ((((int)new_from[i] - 'a' + offset) % 26) + 26) % 26 + 'a';
        }
        // cout << offset << endl;
        solve(new_from, to, offset);
    }
    cout << "Impossible" << endl;
}
