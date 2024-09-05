#include <cassert>
#include "bits/stdc++.h"

using namespace std;

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
    vector<pair<int, int>> index_and_size;
    char parent_symbol;
};

int root = 1;

vector<Node> nodes = {{}, {}};

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

vector<vector<int>> occurences_of_substring_in_string;

void get(string& s) {
    int cur = root;
    for (int i = 0; i < s.size(); ++i) {
        cur = nodes[cur].go[s[i] - 'a'];
        int t = cur;
        while (t) {
            t = nodes[t].super;
            if (!t) break;
            for (auto [index, sz] : nodes[t].index_and_size) {
                occurences_of_substring_in_string[index].push_back(i - sz + 1);
            }
            t = nodes[t].suf;
        }
    }
}

void solve() {
    string t;
    cin >> t;
    int n;
    cin >> n;
    occurences_of_substring_in_string.assign(n, {});
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add_string(s, i);
    }
    build();
    get(t);
    for (int i = 0; i < n; ++i) {
        cout << occurences_of_substring_in_string[i].size() << ' ';
        for (int j : occurences_of_substring_in_string[i]) {
            cout << j + 1 << ' ';
        }
        cout << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}