#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int answer[1000001];
vector<int> goodprimes = {5, 13, 17, 29, 37, 41, 53, 61, 73, 89, 97, 101, 109, 113, 137, 149, 157, 173, 181, 193, 197, 229, 233, 241, 257, 269, 277, 281, 293, 313, 317, 337, 349, 353, 373, 389, 397, 401, 409, 421, 433, 449, 457, 461, 509, 521, 541, 557, 577, 569, 593, 601, 613, 617, 641, 673, 653, 661, 701, 677, 709, 769, 733, 757, 773, 761, 809, 797, 829, 857, 877, 821, 853, 881, 997, 937, 941, 929, 953, 1021, 1013, 1009, 977, 1061, 1093, 1069, 1097, 1033, 1109, 1049, 1117, 1153, 1213, 1129, 1181, 1201, 1277, 1229, 1249};
void solve() {
    for (int i = 2; i <= 1'000'000; i += 2) {
        bool good = false;
        for (int j : goodprimes) {
            if (i % j == 0) {
                good = true;
                break;
            }
        }
        if (good) continue;
        
    }
    // freopen("/home/ser/olproga/lol/result_full.txt", "r", stdin);
    // memset(answer, -1, sizeof(answer));
    // map<int, int> cnt;
    // map<int, int> last;
    // for (int i = 0; i < 945890; ++i) {
    //     int a, b;
    //     cin >> a >> b;
    //     cnt[b] += 1;
    //     last[b] = a;
    //     answer[a] = b;
    // }
    // int ans = 0;
    // int timer = 0;
    // vector<pair<int, int>> cnt_(cnt.begin(), cnt.end());
    // sort(cnt_.begin(), cnt_.end(), [](auto &l, auto &r) {
    //     return l.second > r.second;
    // });
    // vector<int> someprimes;
    // for (auto [u, b] : cnt_) {
    //     timer++;
    //     if (timer == 101) break;
    //     someprimes.push_back(u);
    // }
    // for (int i : someprimes) {
    //     cout << i << endl;
    // }
    // return;
    // int t = 0;
    // for (int i = 2; i <= 1000000; i += 2) {
    //     t++;
    //     if (answer[i] < 0) {
    //         cout << "-" << abs(answer[i]) << ',';
    //     } else {
    //         cout << answer[i] << ",";
    //     }
    // }
    // cerr << t << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}