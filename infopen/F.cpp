#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
    array<int, ALPHABET_SIZE> nxt;
    bool term;
    array<int, ALPHABET_SIZE> go;
    int suf, super, parent;
    vector<pair<int, int>> size_and_index;
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
    nodes[cur].size_and_index.emplace_back(s.size(), index);
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
    uint64_t hs;
    const bool operator==(const Hash& l) const {
        return size == l.size && xr == l.xr && hs == l.hs;
    }
};
Hash dp[6001];
const int P = 2351;
vector<vector<pair<int, int>>> occ_all;
vector<pair<int, int>> occ_all_mx;

void get_precalc(string& s) {
    int cur = root;
    for (int i = 0; i < (int)s.size(); ++i) {
        cur = nodes[cur].go[s[i] - 'a'];
        int t = cur;
        while (t) {
            t = nodes[t].super;
            if (!t) break;
            for (auto [sz, index] : nodes[t].size_and_index) {
                occ_all[i - sz + 1].emplace_back(sz, index);
                occ_all_mx[i - sz + 1] = max(occ_all_mx[i - sz + 1], occ_all[i - sz + 1].back());
            }
            t = nodes[t].suf;
        }
    }
}
Hash get(string& s, int starting_from = 0, int r = 0) {
    Hash res = {0, 0, 0};
    int i = starting_from;
    int sz = 0;
    while (sz < r - starting_from + 1) {
        // cout << "\nI: " << i << endl;
        // cout << occ_all_mx[i].first << ' ' << occ_all_mx[i].second << endl;
        // cout << sz << ' ' << starting_from << ' ' << r << ' ' << i << " not good" << endl;
        // cout << occ_all_mx[i].first << endl;
        if (occ_all_mx[i].first == -1) {
            int el = dsu.getp(s[i] - 'a' + 1);
            // cout << el << ' ';
            res.size++;
            res.xr ^= change[el];
            res.hs = res.hs * P + change[el];
            i += 1;
            sz += 1;
            // cout << "good1" << endl;
            continue;
        }
        if (sz + occ_all_mx[i].first <= r - starting_from + 1) {
            int el = dsu.getp(occ_all_mx[i].second);
            // cout << el << ' ';
            res.size++;
            res.xr ^= change[el];
            res.hs = res.hs * P + change[el];
            sz += occ_all_mx[i].first;
            i += occ_all_mx[i].first;
            // cout << "good2" << endl;
            continue;
        }
        pair<int, int> mx = {-1, -1};
        for (auto& l : occ_all[i]) {
            // cout << "EXTRA: " << l.first << ' ' << l.second << endl;
            if (sz + l.first <= r - starting_from + 1) {
                mx = max(mx, l);
            }
        }
        if (mx.first != -1) {
            int el = dsu.getp(mx.second);
            // cout << el << ' ';
            res.size++;
            res.xr ^= change[el];
            res.hs = res.hs * P + change[el];
            i += mx.first;
            sz += mx.first;
            // cout << "good3" << endl;
            continue;
        }
        int el = dsu.getp(s[i] - 'a' + 1);
        // cout << el << ' ';
        res.size++;
        res.xr ^= change[el];
        res.hs = res.hs * P + change[el];
        i += 1;
        sz += 1;
        // cout << "good4" << endl;
    }
    // cout << endl;
    return res;
}

void solve() {
    mt19937 rng(42);
    auto uid = uniform_int_distribution<int>(10000, (int)1e9);
    string t;
    cin >> t;
    int n, k;
    cin >> n >> k;
    sounds.assign(27, {});
    occ_all.assign(t.size(), {});
    occ_all_mx.assign(t.size(), {-1, -1});
    for (int i = 1; i <= 26; ++i) {
        sounds[i] = (char)(i - 1 + 'a');
    }
    for (int i = 0; i < n; ++i) {
        string snd;
        cin >> snd;
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
    get_precalc(t);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--, c--, d--;
        Hash ans1 = get(t, a, b);
        Hash ans2 = get(t, c, d);
        if (ans1 == ans2) {
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