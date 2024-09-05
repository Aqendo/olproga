#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

int index_ = 0;
int n;

struct Node {
    int number;
    Node *l, *r;
};

vector<int> on_enter, before_right, number_to_order_in_before_right;

vector<Node> nodes;

void dfs(int l, int r) {
    // printf("[%lld..%lld]\n", l, r);
    if (l >= r) return;
    int number = on_enter[index_];
    if (index_ == n - 1) return;
    index_++;
    int next_number = on_enter[index_];
    // printf("got numbers %lld->%lld\n", number, next_number);
    if (number_to_order_in_before_right[next_number] < number_to_order_in_before_right[number]) {
        // printf("this is a left child\n");
        nodes[number].l = &nodes[next_number];
        dfs(l, number_to_order_in_before_right[number] - 1);
        if (index_ == n - 1) return;
        index_++;
        next_number = on_enter[index_];
        // printf("went out of dfs at [%lld, %lld] and have an edge %lld->%lld\n", l, r, number, next_number);
        if (number_to_order_in_before_right[next_number] > r) {
            // printf("this is not the right child\n");
            index_--;
            return;
        }
        // printf("this is the right child\n");
        nodes[number].r = &nodes[next_number];
        dfs(number_to_order_in_before_right[number] + 1, r);
    } else {
        // printf("this is a right child\n");
        nodes[number].r = &nodes[next_number];
        dfs(number_to_order_in_before_right[number] + 1, r);
    }
}

vector<int> our_on_enter, our_before_right;

void dfs_check(Node* cur) {
    if (!cur) return;
    our_on_enter.push_back(cur->number);
    dfs_check(cur->l);
    our_before_right.push_back(cur->number);
    dfs_check(cur->r);
}

void solve() {
    cin >> n;
    on_enter.assign(n, {});
    before_right.assign(n, {});
    nodes.assign(n + 1, {});
    our_on_enter.reserve(n);
    our_before_right.reserve(n);
    for (int i = 0; i <= n; ++i) {
        nodes[i].number = i;
    }
    number_to_order_in_before_right.assign(n + 1, {});
    for (int i = 0; i < n; ++i) {
        cin >> on_enter[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> before_right[i];
        number_to_order_in_before_right[before_right[i]] = i;
    }
    if (on_enter[0] != 1) {
        cout << "-1\n";
        return;
    }
    dfs(0, n - 1);
    dfs_check(&nodes[1]);
    if (our_on_enter != on_enter || our_before_right != before_right) {
        cout << "-1\n";
        return;
    }
    for (int i = 1; i <= n; ++i) {
        cout << (nodes[i].l ? nodes[i].l->number : 0) << ' ' << (nodes[i].r ? nodes[i].r->number : 0) << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
