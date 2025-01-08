#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
    array<int, ALPHABET_SIZE> nxt;
    bool term;
    array<int, ALPHABET_SIZE> go;
    int suf, super, parent;
    vector<pair<int, int>> index_and_size;
    char parent_symbol;
};

int root = 1;
const int MAXNODES = 6100;
int timer_nodes = 2;
Node nodes[MAXNODES];

void add_string(string& s, int index) {
    int cur = root;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (!nodes[cur].nxt[s[i] - 'a']) {
            nodes[cur].nxt[s[i] - 'a'] = timer_nodes++;
            nodes[nodes[cur].nxt[s[i] - 'a']].parent = cur;
        }
        int c = s[i] - 'a';
        cur = nodes[cur].nxt[c];
        nodes[cur].parent_symbol = c;
    }
    nodes[cur].term = true;
    nodes[cur].index_and_size.emplace_back(index, s.size());
}

void build() {
    nodes[root].parent = root;
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (nodes[nodes[cur].parent].suf) {
            nodes[cur].suf = nodes[nodes[nodes[cur].parent].suf]
                                 .go[nodes[cur].parent_symbol];
        } else {
            nodes[cur].suf = root;
        }
        if (cur == root) {
            nodes[cur].suf = 0;
        }
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (nodes[cur].nxt[i]) {
                nodes[cur].go[i] = nodes[cur].nxt[i];
            } else {
                if (!nodes[cur].suf) {
                    nodes[cur].go[i] = root;
                } else {
                    nodes[cur].go[i] = nodes[nodes[cur].suf].go[i];
                }
            }
        }
        if (nodes[cur].term) {
            nodes[cur].super = cur;
        } else if (cur != root) {
            nodes[cur].super = nodes[nodes[cur].suf].super;
        }
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (nodes[cur].nxt[i]) {
                q.push(nodes[cur].nxt[i]);
            }
        }
    }
}
struct DSU {
    vector<int> sizes, parent;
    void init(int n) {
        sizes.assign(n + 1, 1);
        parent.assign(n + 1, {});
        iota(parent.begin(), parent.end(), 0);
    }
    int getp(int x) {
        if (parent[x] == x) return x;
        return parent[x] = getp(parent[x]);
    }
    bool unite(int a, int b) {
        a = getp(a);
        b = getp(b);
        if (a == b) return false;
        if (sizes[a] > sizes[b]) swap(a, b);
        sizes[b] += sizes[a];
        parent[a] = b;
        return true;
    }
};
const int MAXN = 5e5 + 27;
int change[MAXN];
vector<vector<int>> occurences_of_substring_in_string;
vector<string> sounds;
DSU dsu;
struct Hash {
    int size;
    int xr;
    int sm;
    uint64_t hs;
    const bool operator==(const Hash& l) const {
        return size == l.size && xr == l.xr && hs == l.hs && sm == l.sm;
    }
};
Hash dp[6001];
const int P = 2351;
void get(string& s) {
    int cur = root;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (i != 0) {
            dp[i] = dp[i - 1];
        }
        int el = dsu.getp(s[i] - 'a' + 1);
        dp[i].size++;
        dp[i].xr ^= change[el];
        dp[i].sm += change[el];
        dp[i].hs = dp[i].hs * P + change[el];
        // dp[i].push_back(s[i] - 'a' + 1);
        // cout << "in index: " << i << endl;
        cur = nodes[cur].go[s[i] - 'a'];
        int t = cur;
        while (t) {
            t = nodes[t].super;
            if (!t) break;
            int mx = 1;
            for (auto [index, sz] : nodes[t].index_and_size) {
                // cout << i << ' ' << index << ' ' << sz << endl;
                if (i - sz >= 0) {
                    if (sz > mx) {
                        dp[i] = dp[i - sz];
                        el = dsu.getp(index);
                        dp[i].size++;
                        dp[i].xr ^= change[el];
                        dp[i].sm += change[el];
                        dp[i].hs = dp[i].hs * P + change[el];
                        mx = max(mx, sz);
                        // dp[i].push_back(index);
                    }
                } else {
                    if (sz > mx) {
                        mx = max(mx, sz);
                        dp[i] = {
                            .size = 1,
                            .xr = change[dsu.getp(index)],
                            .sm = change[dsu.getp(index)],
                            .hs = (uint64_t)change[dsu.getp(index)]};
                    }

                    // dp[i] = {index};
                }
            }
            t = nodes[t].suf;
        }
    }
}

void solve() {
    mt19937 rng(42);
    auto uid = uniform_int_distribution<int>(10000, (int)1e9);
    string t;
    cin >> t;
    reverse(t.begin(), t.end());
    int n, k;
    cin >> n >> k;
    sounds.assign(27, {});
    for (int i = 1; i <= 26; ++i) {
        sounds[i] = (char)(i - 1 + 'a');
    }
    for (int i = 0; i < n; ++i) {
        string snd;
        cin >> snd;
        reverse(snd.begin(), snd.end());
        sounds.push_back(snd);
        add_string(snd, sounds.size() - 1);
    }
    build();
    dsu.init(sounds.size());
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        dsu.unite(x, y);
    }
    for (int i = 1; i < (int)sounds.size(); ++i) {
        int ii = dsu.getp(i);
        if (!change[ii]) {
            change[ii] = uid(rng);
        }
    }
    get(t);
    // for (int from = 0; from < t.size(); ++from) {
    //     for (int from2 = 0; from2 < t.size(); ++from2) {
    //         cout << from << ' ' << from2 << ' ';
    //         if (dp[0][(int)t.size() - 1 - from] == dp[0][(int)t.size() - 1 - from2]) {
    //             cout << "Yes\n";
    //         } else {
    //             cout << "No\n";
    //         }
    //     }
    // }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--, c--, d--;
        if (dp[(int)t.size() - 1 - a] == dp[(int)t.size() - 1 - c]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) solve();
}