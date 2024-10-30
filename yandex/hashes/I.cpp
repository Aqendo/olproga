#include "bits/stdc++.h"
using namespace std;
# define int int64_t
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif
vector<vector<int>> g1, g2;
vector<int> used;
vector<int> sizes;
void get_sizes(int x, vector<vector<int>> &g) {
    int answer = 1;
    used[x] = 1;
    for (int u : g[x]) {
        if (!used[u]) {
            get_sizes(u, g);
            answer += sizes[u];
        }
    }
    sizes[x] = answer;
}
int n;
int get_centroid(int x, vector<vector<int>> &g) {
    used[x] = 1;
    for (int u : g[x]) {
        if (!used[u]) {
            if (sizes[u] > n / 2) {
                return get_centroid(u, g);
            }
        }
    }
    return x;
}

vector<int> h;

int timer = 1;

map<multiset<int>, int> hash_by_vector;

int get_hash(int x, vector<vector<int>> &g) {
    used[x] = true;
    multiset<int> children;

    for (int u : g[x]) {
        if (!used[u]) {
            children.insert(get_hash(u, g));
        }
    }
    if (!hash_by_vector.count(children)) {
        hash_by_vector[children] = hash_by_vector.size();
    }
    return hash_by_vector[children];
}


void solve() {
    cin >> n;
    g1.assign(n + 1, {});
    g2.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g1[a].push_back(b);
        g1[b].push_back(a);
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g2[a].push_back(b);
        g2[b].push_back(a);
    }
    sizes.assign(n + 1, {});
    used.assign(n + 1, {});
    get_sizes(1, g1);
    used.assign(n + 1, {});
    int centroid_g1 = get_centroid(1, g1);
    sizes.assign(n + 1, {});
    used.assign(n + 1, {});
    get_sizes(1, g2);
    used.assign(n + 1, {});
    int centroid_g2 = get_centroid(1, g2);
    used.assign(n + 1, {});
    int hash_first = get_hash(centroid_g1, g1);;
    used.assign(n + 1, {});
    h.assign(n + 1, {});
    int hash_second = get_hash(centroid_g2, g2);
    cout << (hash_first == hash_second ? "YES" : "NO");
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
