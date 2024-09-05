#include "bits/stdc++.h"

using namespace std;
#define int int64_t
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

const int ALPHABET_SIZE = 26;

struct Node {
    array<int, ALPHABET_SIZE> nxt;
    bool term;
    array<int, ALPHABET_SIZE> go;
    int suf, super, parent;
    char parent_symbol;
    int cnt = 0;
};

string to_string(const Node& n) {
    string res = "(" + to_string(char(n.parent_symbol + 'a')) +
                 ", cnt=" + to_string(n.cnt) + ")";
    return res;
}

int root = 1;

vector<Node> nodes = {{}, {}};

vector<int> string_to_node;

void add_string(string& s, int index) {
    int cur = root;
    for (int i = 0; i < s.size(); ++i) {
        if (!nodes[cur].nxt[s[i] - 'a']) {
            nodes.push_back({});
            nodes[cur].nxt[s[i] - 'a'] = (int)nodes.size() - 1;
            nodes[nodes[cur].nxt[s[i] - 'a']].parent = cur;
        }
        int c = s[i] - 'a';
        cur = nodes[cur].nxt[c];
        nodes[cur].parent_symbol = c;
    }
    nodes[cur].term = true;
    string_to_node[index] = cur;
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

void get(string& s) {
    int cur = root;
    for (int i = 0; i < s.size(); ++i) {
        cur = nodes[cur].go[s[i] - 'a'];
        int t = cur;
        t = nodes[t].super;
        nodes[t].cnt++;
    }
}

vector<vector<int>> g;
vector<int> answer;

vector<int8_t> used;

int dfs(int x) {
    used[x] = true;
    int ans = 0;
    for (int u : g[x]) {
        if (!used[u]) {
            ans += dfs(u);
        }
    }
    answer[x] = ans + nodes[x].cnt;
    return answer[x];
}

void solve() {
    int n;
    cin >> n;
    string_to_node.assign(n, {});
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add_string(s, i);
    }
    string t;
    cin >> t;
    g.assign(nodes.size() + 1, {});
    answer.assign(nodes.size() + 1, {});
    build();
    for (int i = 1; i < nodes.size(); ++i) {
        g[nodes[i].suf].push_back(i);
    }
    used.assign(g.size() + 1, {});
    get(t);
    for (int i = 0; i < nodes.size(); ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    vector<int> answer_output(n);
    for (int i = 0; i < n; ++i) {
        cout << answer[string_to_node[i]] << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
