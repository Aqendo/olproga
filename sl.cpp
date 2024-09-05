#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define OPTIMIZETHISSHIT ios::sync_with_stdio(false); cin.tie(nullptr);
#define int long long

#define endl '\n'
#define fi first
#define se second

#define pb push_back
#define eb emplace_back
// #define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define icin(x) int x; cin >> x

using namespace std;
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

class Solve {
    int length = 0;
    int mod = 1e9 + 7;


    int module(int x) {
        return (x % mod + mod) % mod;
    }

    vector<int> get_kth(int A, int k) {
        vector<int> Ax;
        int copyA = A;
        while (copyA > 0) {
            Ax.pb(copyA % k);
            copyA /= k;
        }
        reverse(all(Ax));
        return Ax;
    }

    int solve(int A, int kk, vector<int> a) {
        int n = a.size() - 1;

        vector<int> Ax = get_kth(A, kk);

        length = Ax.size();

        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++) s[i] = s[i - 1] + (a[i] == -1);

        vector<int> k(length + 1);
        k[0] = 1;
        for (int i = 1; i <= length; i++) k[i] = k[i - 1] * kk % mod;

        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j >= max(i - length + 1, (int)1); j--) {
                if (a[j] == 0) {
                    continue;
                }
                int count_of_var = 0;
                if (i - j + 1 == length) {
                    bool valid = true;
                    for (int l = j; l <= i; l++) {
                        if (a[l] != -1) {
                            if (a[l] > Ax[l - j]) {
                                valid = false;
                                break;
                            } else if (a[l] < Ax[l - j]) {
                                count_of_var = module(count_of_var + k[s[i] - s[l]]);
                                valid = false;
                                break;
                            }
                        } else {
                            if (l == j) {
                                count_of_var = module(count_of_var + (Ax[l - j] - 1) * k[s[i] - s[l]]);
                            } else {
                                count_of_var = module(count_of_var + Ax[l - j] * k[s[i] - s[l]]);
                            }
                        }
                    }
                    if (valid) count_of_var += 1;
                } else {
                    if (a[j] == -1) {
                        count_of_var = module(count_of_var + (kk - 1) * k[s[i] - s[j]]);
                    } else if (a[j] != 0) {
                        count_of_var = module(count_of_var + k[s[i] - s[j]]);
                    }
                }
                dp[i] = module(dp[i] + count_of_var * dp[j - 1]);
            }
        }
        return module(dp[n]);
    }

 public:
    int sol(int A, int k, const vector<int>& a) {
        return solve(A, k, a);
    }
};



// #define STRESS
signed main() {
    OPTIMIZETHISSHIT
#ifdef STRESS

#else
    int n, A, kk;
    cin >> n >> A >> kk;

    vector<int> a(n + 1);
    auto mlg = Solve();
    for (int i = 1; i <= n; i++) cin >> a[i];
    cout << mlg.sol(A, kk, a) << endl;
#endif
    return 0;
}
