#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
using namespace std;
using namespace __gnu_pbds;

template <typename K, typename V>
using hash_table = gp_hash_table<K, V>;

struct Segtree {
    int size;
    vector<int> tree;
    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign((size << 1) - 1, 0);
    }

    void build(vector<int>& arr, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < arr.size()) {
                tree[x] = arr[lx];
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(arr, (x << 1) + 1, lx, m);
        build(arr, (x << 1) + 2, m, rx);
        tree[x] = tree[(x << 1) + 1] + tree[(x << 1) + 2];
    }
    void build(vector<int>& arr) {
        init(arr.size());
        build(arr, 0, 0, size);
    }
    void add(int x, int i, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x]++;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i < m) {
            add((x << 1) + 1, i, lx, m);
        } else {
            add((x << 1) + 2, i, m, rx);
        }
        tree[x] = tree[x * 2 + 1] + tree[x * 2 + 2];
    }
    void add(int i) { add(0, i, 0, size); }
    void substract(int x, int i, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x]--;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i < m) {
            substract((x << 1) + 1, i, lx, m);
        } else {
            substract((x << 1) + 2, i, m, rx);
        }
        tree[x] = tree[x * 2 + 1] + tree[x * 2 + 2];
    }
    void substract(int i) { substract(0, i, 0, size); }
    int sum(int x, int l, int r, int lx, int rx) {
        if (l <= lx && rx <= r) return tree[x];
        if (l >= rx || r <= lx) return 0;
        int m = (lx + rx) >> 1;
        int s1 = sum((x << 1) + 1, l, r, lx, m);
        int s2 = sum((x << 1) + 2, l, r, m, rx);
        return s1 + s2;
    }
    int sum(int l, int r) { return sum(0, l, r, 0, size); }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) cin >> i;
    hash_table<int, int> numbers;
    int cnt = 0;
    vector<int> arrSorted = arr;
    sort(arrSorted.begin(), arrSorted.end());
    for (int& i : arrSorted) {
        if (numbers[i] == 0) {
            numbers[i] = ++cnt;
        }
    }
    for (int& i : arr) {
        i = numbers[i] - 1;
    }
    vector<int> countNumbers(cnt);
    for (int& i : arr) {
        countNumbers[i]++;
    }
    Segtree stL, stR;
    stL.init(cnt);
    stR.build(countNumbers);
    long long ans = 0;
    for (int i : arr) {
        int countL = 0;
        if (i > 0) {
            countL = stL.sum(i + 1, stL.size);
        }
        stL.add(i);

        stR.substract(i);
        // maybe check for i < size or sth
        int countR = stR.sum(0, i);
        ans += countL * countR;
    }
    cout << ans << endl;
    return 0;
}