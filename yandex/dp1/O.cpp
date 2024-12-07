%:ifndef SEREGA
%:pragma GCC optimize("Ofast,unroll-loops")
%:include "bits/allocator.h"
%:pragma GCC target("avx2")
%:endif
%:include "bits/stdc++.h"
%:define int int64_t
using namespace std;
%:ifdef SEREGA
auto __fr = freopen("input.txt", "r", stdin);
%:endif
int prev_[6250001];
void solve() {
    int n, w;
    cin >> n >> w;
    bitset<6250001> bs, bbs, diff;
    bs |= 1;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int t = a[i];
        bbs = bs;
        bs |= bs << t;
        diff = bs ^ bbs;
        for (int index = diff._Find_first(); index < (int)diff.size(); index = diff._Find_next(index)) {
            prev_[index] = i;
        }
    }
    if (!bs[w]) {
        cout << "NO\n";
        return;
    }
    int now = w;
    vector<int> answer;
    while (now != 0) {
        answer.push_back(prev_[now]);
        now -= a[prev_[now]];
    }
    cout << "YES\n";
    cout << answer.size() << '\n';
    for (int i = (int)answer.size() - 1; i >= 0; --i) {
        cout << answer[i] + 1 << ' ';
    }
    cout << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}