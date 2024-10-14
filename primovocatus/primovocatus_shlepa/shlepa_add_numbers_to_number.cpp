#include "bits/stdc++.h"

#define int long long
using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
#endif

using Matrix = vector<vector<int>>;

const int MOD = 1e9 + 7;

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

int powten[14];

vector<int> solve_fast(int n, const vector<pair<int, int>>& qs) {
    int q = qs.size();
    vector<int> answer(q);
    for (int i = 0; i < q; ++i) {
        auto [x, k] = qs[i];
        int coeff = powten[(int)(floor(log10(x))) + 1];
        Matrix invar = {{coeff, 1}, {0, 1}};
        invar = binpow(invar, k);
        invar = mulmod(invar, {{n}, {x}});
        n = invar[0][0] % MOD;
        answer[i] = n;
    }
    return answer;
}

vector<int> solve_slow(int n, const vector<pair<int, int>>& qs) {
    int q = qs.size();
    vector<int> answer(q);
    for (int i = 0; i < q; ++i) {
        auto [x, k] = qs[i];
        int coeff = power_of_ten(x);
        for (int j = 0; j < k; ++j) {
            n *= coeff;
            n += x;
            n %= MOD;
        }
        answer[i] = n;
    }
    return answer;
}
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
signed main() {
    powten[0] = 1;
    for (int i = 1; i < 14; ++i) {
        powten[i] = powten[i - 1] * 10;
    }
    int count = 0;
    do {
        cout << count++ << '\n';
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        int q = uid(1, 100000);
        int n = uid(1, 1000000000);
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; ++i) {
            queries[i].first = uid(1, 1000000000);
            queries[i].second = uid(1, 30);
        }
        vector<int> answer_fast = solve_fast(n, queries);
        vector<int> answer_slow = solve_slow(n, queries);
        if (answer_fast != answer_slow) {
            cout << q << ' ' << n << '\n';
            for (auto [x, k] : queries) {
                cout << x << ' ' << k << '\n';
            }
            break;
        }

    } while (true);
}
