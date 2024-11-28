#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int solve1(int n, const vector<int>& a) {
    vector<int> b = a;
    sort(b.begin(), b.end());
    map<int, int> pos_a, pos_b;
    for (int i = 0; i < n; ++i) {
        pos_a[a[i]] = i;
        pos_b[b[i]] = i;
    }
    int answer = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (pos_a[b[i]] == i) continue;
        vector<int> chain = {pos_a[b[i]]};
        vector<bool> was(n, false);
        was[pos_a[b[i]]] = true;
        while (true) {
            int new_ = pos_b[a[chain.back()]];
            if (was[new_]) break;
            chain.push_back(new_);
            was[new_] = true;
        }
        answer += chain.size() * 2 + 1;
        for (int j : chain) {
            pos_a[a[j]] = pos_b[a[j]];
        }
    }
    return answer;
}

int solve2(int n, const vector<int>& a) {
    vector<pair<int, int>> sa(n);
    for (int i = 0; i < n; i++) {
        sa[i] = {a[i], i};
    }
    sort(sa.begin(), sa.end());
    int ans = 0;
    map<int, int> id;
    for (int i = 0; i < n; i++) {
        id[sa[i].first] = i;
    }
    bool flag = false;
    set<int> indsnot;
    for (int i = 0; i < n; i++) {
        if (a[i] != sa[i].first) {
            indsnot.insert(i);
        }
    }
    while (!indsnot.empty()) {
        int st;
        set<int> us;
        st = *indsnot.begin();
        for (int i = 0; i < n; i++) {
            us.insert(st);
            st = id[a[st]];
            if (us.find(st) != us.end()) break;
        }
        ans += 1;
        ans += us.size() * 2;
        for (int x : us) {
            indsnot.erase(x);
        }
    }
    return ans;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(time(NULL));
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    int index = 0;
    while (true) {
        if (++index % 20 == 0) {
            cout << index << endl;
        }
        int n = uid(1, 10000);
        vector<int> a(n);
        iota(a.begin(), a.end(), 1);
        shuffle(a.begin(), a.end(), rng);
        if (solve1(n, a) != solve2(n, a)) {
            cout << n << endl;
            for (int i : a) cout << i << ' ';
            cout << endl;
            return 0;
        }
    }
}