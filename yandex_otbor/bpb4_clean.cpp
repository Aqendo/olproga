#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

struct Node {
    int index, max_offset, open, close;
    string s;
    bool operator<(const Node& n) {
        if (open == 0) {
            return false;
        } else if (n.open == 0) {
            return true;
        }
        if (max_offset != n.max_offset) return max_offset < n.max_offset;
        if (open != n.open) return open > n.open;
        return close < n.close;
    }
};
string to_string(const Node& s) {
    return format("\n(i={} maxoff={} open={} close={} s=\"{}\")", s.index, s.max_offset, s.open, s.close, s.s);
}

void solve() {
    int n;
    cin >> n;
    vector<Node> substrs(n);
    for (int i = 0; i < n; ++i) {
        cin >> substrs[i].s;
        string& s = substrs[i].s;
        int current = 0;
        int mn = 0;
        for (char c : s) {
            if (c == '(') {
                current++;
            } else {
                if (current == 0) {
                    mn--;
                } else {
                    current--;
                }
            }
        }
        substrs[i].index = i;
        substrs[i].max_offset = -mn;
        substrs[i].close = -mn;
        substrs[i].open = current;
    }
    sort(substrs.begin(), substrs.end());
    int total = 0;
    for (auto& [index, node_max_offset, node_open, node_closed, s] : substrs) {
        if (total + node_max_offset < 0) {
            cout << "-1\n";
            return;
        }
        for (char c : s) {
            total += (c == ')' ? -1 : 1);
            if (total < 0) {
                cout << "-1\n";
                return;
            }
        }
    }
    if (total != 0) {
        cout << "-1";
        return;
    }
    for (auto& [index, node_max_offset, node_open, node_closed, s] : substrs) {
        cout << index + 1 << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
