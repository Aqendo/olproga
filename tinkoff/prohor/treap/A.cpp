#include <bits/stdc++.h>
using namespace std;
#define int int64_t
mt19937 rng(42);
struct Node {
    int key, prior, sum;
    Node *l, *r;
    Node(int _key) : key(_key), prior(rng()), sum(_key) {}
};
struct Treap {
    Node* root;
    int sum(Node* p) { return p ? p->sum : 0; }
    void upd(Node* p) { p->sum = sum(p->l) + sum(p->r) + p->key; }
    pair<Node*, Node*> split(Node* p, int x) {
        if (!p) return {nullptr, nullptr};
        if (p->key > x) {
            pair<Node*, Node*> left = split(p->l, x);
            p->l = left.second;
            upd(p);
            return {left.first, p};
        } else {
            pair<Node*, Node*> right = split(p->r, x);
            p->r = right.first;
            upd(p);
            return {p, right.second};
        }
    }
    void print(Node* p) {
        if (!p) return;
        print(p->l);
        cout << '(' << p->key << ") ";
        print(p->r);
    }
    void print() {
        print(root);
        cout << endl;
    }
    Node* merge(Node* l, Node* r) {
        if (!l) return r;
        if (!r) return l;
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            upd(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            upd(r);
            return r;
        }
    }
    bool exists(Node* v, int64_t x) {
        if (!v) return false;
        if (v->key == x) return true;
        if (v->key < x) return exists(v->r, x);
        return exists(v->l, x);
    }
    bool exists(int x) { return exists(root, x); }
    void add_node(int x) {
        auto [garbage_, pref] = split(root, x);
        Node* new_ = new Node(x);
        root = merge(garbage_, merge(new_, pref));
    }
    int get_sum(int l, int r) {
        auto [garbage_, pref] = split(root, l - 1);
        auto [segment, garbage_2] = split(pref, r);
        int answer = sum(segment);
        root = merge(garbage_, merge(segment, garbage_2));
        return answer;
    }
};
//

Treap treap;
const int MOD = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    int last_res = -1;
    for (int i = 0; i < n; ++i) {
        char move;
        cin >> move;
        if (move == '+') {
            int t;
            cin >> t;
            int to_add = 0;
            if (last_res != -1) {
                cout << "adding " << (t + last_res) % MOD << endl;
                to_add = (t + last_res) % MOD;
            } else {
                cout << "adding " << t << endl;
                to_add = t;
            }
            if (!treap.exists(to_add)) {
                treap.add_node(to_add);
            }
            treap.print();
            last_res = -1;
        } else {
            int l, r;
            cin >> l >> r;
            int answer = treap.get_sum(l, r);
            last_res = answer;
            cout << answer << '\n';
        }
    }
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}