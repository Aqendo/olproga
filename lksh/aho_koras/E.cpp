#include <bits/stdc++.h>

using namespace std;

# ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

const int BIT_COUNT = 32;

struct Node {
    Node* go[2];
    short cnt = 0;
};

Node root;

void add_number(int n) {
    Node* cur = &root;
    for (int i = 0; i < BIT_COUNT; ++i) {
        int bit = ((n << i) & (1 << (BIT_COUNT - 1))) != 0;
        if (!cur->go[bit]) {
            cur->go[bit] = new Node();
        }
        cur = cur->go[bit];
    }
    cur->cnt++;
}

void remove_number(int n) {
    Node* cur = &root;
    int index = -1;
    vector<pair<Node*, int>> nodes;
    for (int i = 0; i < BIT_COUNT; ++i) {
        int bit = ((n << i) & (1 << (BIT_COUNT - 1))) != 0;
        cur = cur->go[bit];
        nodes.emplace_back(cur, bit);
        index++;
    }
    cur->cnt--;
    if (cur->cnt == 0) {
        int ind = (int)nodes.size() - 1;
        do {
            delete nodes[ind].first;
            nodes[ind - 1].first->go[nodes[ind].second] = nullptr;
            ind--;
        } while (!nodes[ind].first->go[!nodes[ind + 1].second]);
    }
}

int get_max(int n) {
    Node* cur = &root;
    Node* revert = nullptr;
    int i_revert = -1;
    int ans_revert = -1;
    int ans = 0;
    for (int i = 0; i < BIT_COUNT; ++i) {
        int bit = ((n << i) & (1 << (BIT_COUNT - 1))) == 0;
        if (cur->go[false] && cur->go[true]) {
            ans_revert = ans;
            i_revert = i;
            revert = cur;
        }
        if (!cur->go[bit]) {
            if (!cur->go[!bit]) {
                return ans;
            }
            cur = cur->go[!bit];
            ans = (ans << 1) + !bit;
        } else {
            cur = cur->go[bit];
            ans = (ans << 1) + bit;
        }
    }
    if (ans == n && cur->cnt >= 1) {
        assert(i_revert != -1);
        assert(revert);
        ans = ans_revert;
        cur = revert;

        int bit = ((n << i_revert) & (1 << (BIT_COUNT - 1))) == 0;
        cur = cur->go[!bit];
        ans = (ans << 1) + !bit;

        for (int i = i_revert + 1; i < BIT_COUNT; ++i) {
            bit = n >> i & 1;
            if (!cur->go[bit]) {
                if (!cur->go[!bit]) {
                    return ans;
                }
                cur = cur->go[!bit];
                ans = (ans << 1) + !bit;
            } else {
                cur = cur->go[bit];
                ans = (ans << 1) + bit;
            }
        }
    }
    if (cur->cnt == 0) {
        return -1;
    }
    return ans;
}

void solve() {
    int q;
    cin >> q;
    add_number(0);
    while (q--) {
        char move;
        cin >> move;
        int x;
        cin >> x;
        if (move == '+') {
            add_number(x);
        } else if (move == '-') {
            remove_number(x);
        } else {
            cout << (x ^ get_max(x)) << '\n';
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}
