#include <bits/stdc++.h>
using namespace std;

%:define set(x, y) ((((int64_t)x) << 32) + y)
%:define fi(c) ((int)(c >> 32))
%:define se(c) ((int)(c & ~0u))

const int MAXN = 1'000'000;
const int64_t INF = set(INT_MAX, INT_MAX);

int64_t eulers[2 * MAXN];
int tin[MAXN];
int edgeTo[MAXN], lastInd[MAXN], prevInd[MAXN];
int64_t dfs[2 * MAXN];

int timer_edgeto = 0;
int timer = 0;
int tdfs = 0;
int sz_blocks;
int MAX_LOG = 17;

int64_t min(int64_t a, int64_t b) { return a < b ? a : b; }

void spinit(vector<int64_t> &arr) {
    MAX_LOG = __lg(arr.size());
    for (int i = 0; i < (int)arr.size(); ++i) {
        dfs[i] = arr[i];
    }
    for (int l = 1; l <= MAX_LOG; ++l) {
        for (int i = 0; i < (int)arr.size(); ++i) {
            dfs[l * sz_blocks + i] = dfs[(l - 1) * sz_blocks + i];
            if (i + (1ll << (l - 1)) < (int)arr.size()) {
                dfs[l * sz_blocks + i] = min(dfs[l * sz_blocks + i], dfs[(l - 1) * sz_blocks + i + (1ll << (l - 1))]);
            }
        }
    }
}
int64_t spget(int l, int r) {
    int LOG = __lg(r - l + 1);
    return min(dfs[LOG * sz_blocks + l], dfs[LOG * sz_blocks + r - (1l << LOG) + 1]);
}
int cnstnt;
int get(int l, int r) {
    l = tin[l], r = tin[r];
    if (l > r) swap(l, r);
    int64_t answer = INF;
    for (; l < r && l % cnstnt != 0; ++l) {
        answer = min(answer, eulers[l]);
    }
    for (; l < r && (r + 1) % cnstnt != 0; r--) {
        answer = min(answer, eulers[r]);
    }
    if (l == r) {
        answer = min(answer, eulers[l]);
        return se(answer);
    }
    int64_t temp = spget(l / cnstnt, r / cnstnt);
    answer = min(answer, temp);
    return se(answer);
}
void solve() {
    int n, m;
    cin >> n >> m;
    memset(prevInd, -1, sizeof(prevInd));
    memset(lastInd, -1, sizeof(lastInd));
    memset(tin, -1, sizeof(tin));
    for (int i = 1; i < n; ++i) {
        int t;
        cin >> t;
        edgeTo[timer_edgeto] = i;
        prevInd[timer_edgeto] = lastInd[t];
        lastInd[t] = timer_edgeto;
        timer_edgeto++;
    }
    int64_t a1, a2, x, y, z, answer = 0;
    cin >> a1 >> a2 >> x >> y >> z;
    /* dfs start */
    dfs[tdfs++] = set(0, 0);
    // (h; v)
    while (tdfs != 0) {
        long long v = se(dfs[tdfs - 1]), h = fi(dfs[tdfs - 1]);
        tdfs--;
        if (tin[v] != -1) {
            eulers[timer] = set((h + 1), v);
            timer++;
            continue;
        }

        eulers[timer] = set((h + 1), v);
        tin[v] = timer++;
        int cur = lastInd[v];
        while (cur != -1) {
            dfs[tdfs++] = set(h, v);
            dfs[tdfs++] = set((h + 1), edgeTo[cur]);
            cur = prevInd[cur];
        }
    }
    /* dfs end */
    int lg_ = cnstnt = __lg(timer) + 1;
    sz_blocks = timer / lg_ + 1;
    vector<int64_t> blocks(sz_blocks, INF);
    for (int i = 0; i < timer; ++i) {
        blocks[i / lg_] = min(blocks[i / lg_], eulers[i]);
    }
    spinit(blocks);
    answer += get(a1, a2);
    int lastans = answer;
    for (int i = 0; i < m - 1; ++i) {
        int a3 = ((x * a1 + y * a2 + z) % n + lastans) % n;
        int a4 = (x * a2 + y * a3 + z) % n;
        lastans = get(a3, a4);
        answer += lastans;
        a1 = a3, a2 = a4;
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
