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

vector<int> solve(vector<string>& strings) {
    int n = strings.size();
    vector<Node> substrs(n);
    for (int i = 0; i < n; ++i) {
        substrs[i].s = strings[i];
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
            // cout << "-1\n";
            return {-1};
        }
        for (char c : s) {
            total += (c == ')' ? -1 : 1);
            if (total < 0) {
                // cout << "-1\n";
                return {-1};
            }
        }
    }
    if (total != 0) {
        // cout << "-1";
        return {-1};
    }
    vector<int> answer;
    for (auto& [index, node_max_offset, node_open, node_closed, s] : substrs) {
        answer.push_back(index);
    }
    return answer;
}
#define uid(x, y) uniform_int_distribution(x, y)(rng)
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        int n = uid(1, 5);
        string s;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            char move = "()"[uid(0, 1)];
            if (move == ')') {
                if (total == 0) {
                    s.push_back('(');
                    total++;
                } else {
                    s.push_back(')');
                    total--;
                }
            } else {
                s.push_back('(');
                total++;
            }
        }
        while (total != 0) {
            char c = "()"[uid(0, 1)];
            total += (c == ')' ? -1 : 1);
            s.push_back(c);
        }
        vector<string> strs = {""};
        for (char c : s) {
            if (uid(1, 10) <= 2 && !strs.back().empty()) strs.push_back("");
            strs.back() += c;
        }
        shuffle(strs.begin(), strs.end(), rng);
        vector<int> answer = solve(strs);
        if (answer.size() == 1 && answer.front() == -1 && s.size() < 15) {
            cout << s << '\n';
            cout << strs.size() << '\n';
            for (string& ss : strs) {
                cout << ss << '\n';
            }
            return 0;
        }
    }
}
