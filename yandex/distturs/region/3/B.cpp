#include "bits/stdc++.h"
%:define int int64_t
using namespace std;

int get_sum(int x) {
    return x * (x + 1) / 2;
}

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int answer = 0;
    for (int B = a; B <= b; ++B) {
        int max_len = (d - c + 1) + (b - a);
        int min_len = (d - c + 1) + (b - B);
        int C_from_max = B + 1;
        if (C_from_max + max_len - 1 <= d) {
            C_from_max = d - max_len + 1;
        }
        int max_cnt = c - C_from_max;
        int C_from_min = B + 1;
        if (C_from_min + min_len - 1 <= d) {
            C_from_min = d - min_len + 1;
        }
        int min_cnt = c - C_from_min;
        int по_хорошему = max_cnt + (d - c + 1);
        int extra = max_len - по_хорошему + 1;
        int delta = extra * (max_cnt + 1) + get_sum(max_cnt) - get_sum(min_cnt);
        answer += delta;
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
