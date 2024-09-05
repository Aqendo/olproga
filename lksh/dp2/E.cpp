#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

const int MOD = 1e9 + 7;

int add(int x, int y) {
    return x + y >= MOD ? x + y - MOD : x + y;
}

struct Matrix {
    vector<vector<long long>> matrix;

    Matrix(int n, int m) : matrix(n, vector<long long>(m)) {}

    Matrix(vector<vector<long long>>& a) : matrix(a) {}

    Matrix operator*(Matrix& b) {
        Matrix c(matrix.size(), b.matrix[0].size());
        for (size_t i = 0; i < c.matrix.size(); ++i) {
            for (size_t j = 0; j < c.matrix[0].size(); ++j) {
                for (int r = 0; r < matrix[0].size(); ++r) {
                    c.matrix[i][j] = add(c.matrix[i][j],
                                         matrix[i][r] * b.matrix[r][j] % MOD);
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

Matrix mul(Matrix& a, Matrix& b) {
    int n = a.matrix.size();
    Matrix c(n, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (int r = 0; r < n; ++r) {
                c.matrix[i][j] = add(c.matrix[i][j],
                                     (a.matrix[i][r] * b.matrix[r][j]) % MOD);
            }
        }
    }
    return c;
}

Matrix binpow(Matrix& a, long long power) {
    int n = a.matrix.size();
    Matrix res = Matrix::get_I(n, n);
    while (power > 0) {
        if (power & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        power >>= 1;
    }
    return res;
}

void solve() {
    long long a, b, c, d, e, n;
    cin >> a >> b >> c >> d >> e >> n;
    if (n == 1 || n == 2) {
        cout << 1 << '\n';
        return;
    }
    vector<vector<long long>> matr_vector = {{a, b, c, d, e},
                                             {1, 0, 0, 0, 0},
                                             {0, 0, 2, 0, 0},
                                             {0, 0, 0, 1, 1},
                                             {0, 0, 0, 0, 1}};
    Matrix matr(matr_vector);
    vector<vector<long long>> base_vector = {{1}, {1}, {8}, {3}, {1}};
    Matrix base(base_vector);
    Matrix res = binpow(matr, n - 2);
    cout << (res * base).matrix[0][0] << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
