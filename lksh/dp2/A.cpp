#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

struct Matrix {
    vector<vector<int>> matrix;

    Matrix(int n, int m) : matrix(n, vector<int>(m)) {}

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

void solve() {
    int p, q, r;
    cin >> p >> q >> r;
    Matrix a(p, q), b(q, r);
    cin >> a >> b;
    Matrix c = a * b;
    cout << c << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
