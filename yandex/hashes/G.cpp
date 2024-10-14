#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
using namespace __gnu_pbds;
using namespace std;
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

template <class K, class V>
using hash_big =
    gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>,
                  linear_probe_fn<>,
                  hash_standard_resize_policy<hash_exponential_size_policy<>,
                                              hash_load_check_resize_trigger<>, true>>;


# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif

struct P {
    int x, y, z, w;
};

void solve() {
    int n;
    cin >> n;
    vector<P> input(n);
    for (int i = 0; i < n; ++i) {
        cin >> input[i].x >> input[i].y >> input[i].z >> input[i].w;
    }
    hash_big<int, int> first;
    first.resize(1e7);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            first[input[i].x + input[j].y]++;
        }
    }
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int need = -input[i].z - input[j].w;
            if (first.find(need) != first.end()) {
                answer += first[need];
            }
        }
    }

    cout << answer << endl;
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
