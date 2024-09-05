#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

struct Matrix {
    vector<vector<long long>> matrix;

    Matrix(int n, int m) : matrix(n, vector<long long>(m)) {}

    Matrix operator*(Matrix& b) {
        Matrix c(matrix.size(), b.matrix[0].size());
        for (size_t i = 0; i < c.matrix.size(); ++i) {
            for (size_t j = 0; j < c.matrix[0].size(); ++j) {
                for (int r = 0; r < matrix[0].size(); ++r) {
                    c.matrix[i][j] += matrix[i][r] * b.matrix[r][j];
                }
            }
        }
        return c;
    }

    static Matrix get_I(int n, int m) {
        Matrix matr(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matr.matrix[i][j] = i == j;
            }
        }
        return matr;
    }
};

istream& operator>>(istream& in, Matrix& matr) {
    for (size_t i = 0; i < matr.matrix.size(); ++i) {
        for (size_t j = 0; j < matr.matrix[i].size(); ++j) {
            in >> matr.matrix[i][j];
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrix& matr) {
    for (size_t i = 0; i < matr.matrix.size(); ++i) {
        for (size_t j = 0; j < matr.matrix[i].size(); ++j) {
            out << matr.matrix[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

int add(int x, int y, const int MOD) {
    return x + y >= MOD ? x + y - MOD : x + y;
}

Matrix mul(Matrix& a, Matrix& b, const int MOD) {
    int n = a.matrix.size();
    Matrix c(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (int r = 0; r < n; ++r) {
                c.matrix[i][j] =
                    add(c.matrix[i][j], (a.matrix[i][r] * b.matrix[r][j]) % MOD,
                        MOD);
            }
        }
    }
    return c;
}

Matrix binpow(Matrix& a, long long power, const long long MOD) {
    int n = a.matrix.size();
    Matrix res = Matrix::get_I(n, n);
    while (power > 0) {
        if (power & 1) {
            res = mul(res, a, MOD);
        }
        a = mul(a, a, MOD);
        power >>= 1;
    }
    return res;
}

void solve() {
    long long n, m, p;
    cin >> n >> m >> p;
    Matrix matr(n, n);
    cin >> matr;
    if (m == 0) {
        cout << Matrix::get_I(n, n) << '\n';
        return;
    } else {
        cout << binpow(matr, m, p);
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
