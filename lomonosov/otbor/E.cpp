#include <bits/stdc++.h>
using namespace std;
#define int int64_t
void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<int>> grid(n + 1, vector<int>(m + 1));
    vector<vector<int>> pref(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + grid[i][j];
        }
    }
    auto get = [&pref](int x1, int y1, int x2, int y2) { return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1]; };
    vector<int> wesa = {-(int)1e18};
    wesa.reserve(2500000);
    for (int ifrom = 1; ifrom <= n; ++ifrom) {
        for (int jfrom = 1; jfrom <= m; ++jfrom) {
            for (int ito = ifrom; ito <= n; ++ito) {
                for (int jto = jfrom; jto <= m; ++jto) {
                    wesa.push_back(get(ifrom, jfrom, ito, jto));
                }
            }
        }
    }
    wesa.push_back((int)1e18);
    cerr << 1 << endl;
    stable_sort(wesa.begin(), wesa.end());
    cerr << 2 << endl;
    int answer = 0;
    for (int i = 1; i < (int)wesa.size() - 1; ++i) {
        if (wesa[i] > b) break;
        int l = 0, r = (int)wesa.size() - 1;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (wesa[mid] + wesa[i] < a) {
                l = mid;
            } else {
                r = mid;
            }
        }
        int lower = r;
        l = 0, r = (int)wesa.size() - 1;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (wesa[mid] + wesa[i] <= b) {
                l = mid;
            } else {
                r = mid;
            }
        }
        int preupper = l;
        if (lower > preupper) continue;
        int total = preupper - lower + 1;
        if (lower <= i && i <= preupper) {
            total--;
        }
        answer += total;
    }
    cout << answer / 2 << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}