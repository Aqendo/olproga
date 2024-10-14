// #pragma GCC optimize("trapv")
#include "bits/stdc++.h"

#define int long long
using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
#endif

using Matrix = vector<vector<int>>;

const int MOD = 1e9 + 7;
int power_of_ten(int N) {
    if (N < 10) {
        return 1e1;  // 1 digit
    } else if (N < 100) {
        return 1e2;  // 2 digits
    } else if (N < 1000) {
        return 1e3;  // 3 digits
    } else if (N < 10000) {
        return 1e4;  // 4 digits
    } else if (N < 100000) {
        return 1e5;  // 5 digits
    } else if (N < 1000000) {
        return 1e6;  // 6 digits
    } else if (N < 10000000) {
        return 1e7;  // 7 digits
    } else if (N < 100000000) {
        return 1e8;  // 8 digits
    } else if (N < 1000000000) {
        return 1e9;  // 9 digits
    } else if (N < 10000000000) {
        return 1e10;  // 10 digits
    } else {
        return 1e11;  // 11 digits
    }
}

Matrix mulmod(const Matrix& m1, const Matrix& m2) {
    Matrix res(m1.size(), vector<int>(m2[0].size()));
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            for (int r = 0; r < m1[0].size(); ++r) {
                (res[i][j] += m1[i][r] * m2[r][j] % MOD) %= MOD;
            }
        }
    }
    return res;
}

Matrix get_I(int n, int m) {
    Matrix res(n, vector<int>(m));
    for (int i = 0; i < min(n, m); ++i) {
        res[i][i] = 1;
    }
    return res;
}

Matrix binpow(Matrix m, int power) {
    Matrix result = get_I(m.size(), m[0].size());
    while (power > 0) {
        if (power & 1) {
            result = mulmod(result, m);
        }
        m = mulmod(m, m);
        power >>= 1;
    }
    return result;
}

int powten[14];

void solve() {
    int q, n;
    cin >> q >> n;
    for (int i = 0; i < q; ++i) {
        int x, k;
        cin >> x >> k;
        int coeff = power_of_ten(x);
        Matrix invar = {{coeff, 1}, {0, 1}};
        invar = binpow(invar, k);
        invar = mulmod(invar, {{n}, {x}});
        n = invar[0][0] % MOD;
        cout << n << '\n';
    }
}

signed main() {
    powten[0] = 1;
    for (int i = 1; i < 14; ++i) {
        powten[i] = powten[i - 1] * 10;
    }
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) solve();
}
