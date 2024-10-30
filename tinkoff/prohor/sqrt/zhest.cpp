#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << " = " << x << endl;
const int SQR = 1;
struct Node {
    vector<int> els;
    int mn = INT_MAX;
    int8_t is_reversed = false;
};

vector<Node> korn;
int OP_COUNT = 0;
template <typename T>
void print(vector<vector<T>>& vec) {
    cout << '[';
    for (int i = 0; i < (int)vec.size(); ++i) {
        cout << '[';
        if (vec[i].empty()) cout << ']';
        for (int j = 0; j < (int)vec[i].size(); ++j) {
            cout << vec[i][j];
            if (j == (int)vec[i].size() - 1) {
                cout << ']';
            } else {
                cout << ", ";
            }
        }
        if (i == (int)vec.size() - 1) {
            cout << ']';
        } else {
            cout << ", ";
        }
    }
    cout << endl;
}
pair<int, int> find_block(int ind) {
    // debug("start find block");
    // debug(ind);
    // print(korn);
    int index_so_far = 0;
    for (int i = 0; i < (int)korn.size(); ++i) {
        if (index_so_far + (int)korn[i].els.size() > ind) {
            // debug(i);
            // debug(ind - index_so_far);
            return {i, ind - index_so_far};
        }
        index_so_far += korn[i].els.size();
    }
    assert(false);
    return {0, 0};
}
int n, m;

void rebuild() {
    vector<int> arr;
    arr.reserve(n);
    for (int i = 0; i < (int)korn.size(); ++i) {
        for (int j = 0; j < (int)korn[i].els.size(); ++j) {
            if (!korn[i].is_reversed) {
                arr.push_back(korn[i].els[j]);
            } else {
                arr.push_back(korn[i].els[(int)korn[i].els.size() - 1 - j]);
            }
        }
    }

    korn.assign(n / SQR + 1, {{}, INT_MAX, false});
    for (int i = 0; i < n; ++i) {
        korn[i / SQR].els.push_back(arr[i]);
        korn[i / SQR].mn = min(korn[i / SQR].mn, arr[i]);
    }
}

void revert(int lindex, int rindex) {
    OP_COUNT++;
    if (OP_COUNT > SQR) {
        OP_COUNT = 0;
        rebuild();
    }
    // cout << "REVERT [" << lindex << ";" << rindex << "]" << endl;
    pair<int, int> from_block = find_block(lindex);
    pair<int, int> to_block = find_block(rindex);
    if (korn[from_block.first].is_reversed) {
        int l = 0, r = (int)korn[from_block.first].els.size() - 1;
        while (l < r) {
            swap(korn[from_block.first].els[l++], korn[from_block.first].els[r--]);
        }
        korn[from_block.first].is_reversed = false;
    }
    if (korn[to_block.first].is_reversed) {
        int l = 0, r = (int)korn[to_block.first].els.size() - 1;
        while (l < r) {
            swap(korn[to_block.first].els[l++], korn[to_block.first].els[r--]);
        }
        korn[to_block.first].is_reversed = false;
    }
    // split left side
    // debug(korn.size());
    // debug(from_block.first);
    // debug(from_block.second);

    // print(korn);
    korn.insert(korn.begin() + from_block.first + 1, Node{{}, INT_MAX, false});
    // print(korn);
    // debug(korn.size());
    for (int i = (int)korn[from_block.first].els.size() - 1; i >= from_block.second; --i) {
        // debug(korn.size());
        // debug(from_block.first);
        // debug(korn[from_block.first].size());
        // print(korn);
        int what_to_push = korn[from_block.first].els.back();
        korn[from_block.first + 1].els.push_back(what_to_push);
        korn[from_block.first + 1].mn = min(korn[from_block.first + 1].mn, what_to_push);
        korn[from_block.first].els.pop_back();
    }
    korn[from_block.first].mn = INT_MAX;
    for (int i : korn[from_block.first].els) {
        korn[from_block.first].mn = min(korn[from_block.first].mn, i);
    }
    reverse(korn[from_block.first + 1].els.begin(), korn[from_block.first + 1].els.end());
    to_block.first++;
    // cout << "after left split" << endl;
    // print(korn);
    // split right side
    korn.insert(korn.begin() + to_block.first + 1, Node{{}, INT_MAX, false});

    for (int i = (int)korn[to_block.first].els.size() - 1; i > to_block.second; --i) {
        korn[to_block.first + 1].els.push_back(korn[to_block.first].els.back());
        korn[to_block.first + 1].mn = min(korn[to_block.first + 1].mn, korn[to_block.first].els.back());
        korn[to_block.first].els.pop_back();
    }
    korn[to_block.first].mn = INT_MAX;
    for (int i : korn[to_block.first].els) {
        korn[to_block.first].mn = min(korn[to_block.first].mn, i);
    }
    reverse(korn[to_block.first + 1].els.begin(), korn[to_block.first + 1].els.end());
    int from = from_block.first + 1, to = to_block.first;
    while (from < to) {
        swap(korn[from], korn[to]);
        korn[from].is_reversed = !korn[from].is_reversed;
        korn[to].is_reversed = !korn[to].is_reversed;
        from++;
        to--;
    }
}

int get_min(int l, int r) {
    pair<int, int> from_block = find_block(l);
    pair<int, int> to_block = find_block(r);
    int mn = INT_MAX;
    for (int i = from_block.second; i < (int)korn[from_block.first].els.size(); ++i) {
        if (!korn[from_block.first].is_reversed) {
            mn = min(mn, korn[from_block.first].els[i]);
        } else {
            mn = min(mn, korn[from_block.first].els[(int)korn[from_block.first].els.size() - 1 - i]);
        }
    }
    int from = from_block.first + 1;
    for (int i = 0; i <= (int)to_block.second; ++i) {
        if (!korn[to_block.first].is_reversed) {
            mn = min(mn, korn[to_block.first].els[i]);
        } else {
            mn = min(mn, korn[to_block.first].els[(int)korn[to_block.first].els.size() - 1 - i]);
        }
    }
    int to = to_block.first - 1;
    while (from < to) {
        mn = min({mn, korn[from].mn, korn[to].mn});
        from++;
        to--;
    }
    return mn;
}

void solve() {
    cin >> n >> m;
    korn.assign(n / SQR + 1, Node{{}, INT_MAX, false});
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        korn[i / SQR].els.push_back(t);
        korn[i / SQR].mn = min(korn[i / SQR].mn, t);
    }
    while (m--) {
        int move;
        cin >> move;
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        if (r - l <= SQR + 2) {
            if (move == 1) {
                pair<int, int> from_block = find_block(l);
                pair<int, int> to_block = find_block(r);
                // print(korn);
                // debug(from_block.first);
                // debug(from_block.second);
                // debug(to_block.first);
                // debug(to_block.second);
                while (from_block <= to_block) {
                    int* ell;
                    if (!korn[from_block.first].is_reversed) {
                        // cout << "1[" << from_block.first << "]["
                        // << from_block.second << "]" << endl;
                        ell = &korn[from_block.first].els[from_block.second];
                    } else {
                        // cout << "2[" << from_block.first <<
                        // "][" << (int)korn[from_block.first
                        // ].size() - 1 - from_block.second << "]" << endl;
                        ell = &korn[from_block.first].els[(int)korn[from_block.first].els.size() - 1 - from_block.second];
                    }
                    int* elr;
                    if (!korn[to_block.first].is_reversed) {
                        // cout << "3[" << to_block.first <<
                        // "][" << to_block.second << "]" << endl;
                        elr = &korn[to_block.first].els[to_block.second];
                    } else {
                        // cout << "4[" << to_block.first << "][" << (int)korn[t
                        // o_block.first].size() - 1 - to_block.second << "]" << endl;
                        elr = &korn[to_block.first].els[(int)korn[to_block.first].els.size() - 1 - to_block.second];
                    }
                    swap(*ell, *elr);
                    if (from_block == to_block) break;
                    from_block.second++;
                    if (from_block.second == (int)korn[from_block.first].els.size()) {
                        from_block.first++;
                        while (from_block.first < (int)korn.size() && korn[from_block.first].els.empty()) from_block.first++;
                        if (from_block.first == (int)korn.size()) break;
                        from_block.second = 0;
                    }
                    if (from_block == to_block) break;
                    to_block.second--;
                    if (to_block.second == -1) {
                        to_block.first--;
                        while (to_block.first >= 0 && korn[to_block.first].els.empty()) to_block.first--;
                        if (to_block.first == -1) break;
                        to_block.second = (int)korn[to_block.first].els.size() - 1;
                    }
                }
                for (int i = 0; i < n; ++i) {
                    cout << get_min(i, i) << ' ';
                }
                cout << '\n';
            } else {
                int mn = INT_MAX;
                pair<int, int> from_block = find_block(l);
                pair<int, int> to_block = find_block(r);
                // debug(from_block.first);
                // debug(from_block.second);
                // debug(to_block.first);
                // debug(to_block.second);
                while (from_block <= to_block) {
                    int* ell;
                    if (!korn[from_block.first].is_reversed) {
                        ell = &korn[from_block.first].els[from_block.second];
                    } else {
                        ell = &korn[from_block.first].els[(int)korn[from_block.first].els.size() - 1 - from_block.second];
                    }
                    int* elr;
                    if (!korn[to_block.first].is_reversed) {
                        elr = &korn[to_block.first].els[to_block.second];
                    } else {
                        elr = &korn[to_block.first].els[(int)korn[to_block.first].els.size() - 1 - to_block.second];
                    }
                    mn = min({mn, *ell, *elr});
                    // cout << *ell << ' ' << *elr << endl;
                    if (from_block == to_block) break;
                    from_block.second++;
                    if (from_block.second == (int)korn[from_block.first].els.size()) {
                        from_block.first++;
                        while (from_block.first < (int)korn.size() && korn[from_block.first].els.empty()) from_block.first++;
                        if (from_block.first == (int)korn.size()) break;
                        from_block.second = 0;
                    }
                    if (from_block == to_block) break;
                    to_block.second--;
                    if (to_block.second == -1) {
                        to_block.first--;
                        while (to_block.first >= 0 && korn[to_block.first].els.empty()) to_block.first--;
                        if (to_block.first == -1) break;
                        to_block.second = (int)korn[to_block.first].els.size() - 1;
                    }
                }
                cout << mn << '\n';
            }
            continue;
        }
        if (move == 1) {
            revert(l, r);
            for (int i = 0; i < n; ++i) {
                cout << get_min(i, i) << ' ';
            }
            cout << '\n';
        } else {
            cout << get_min(l, r) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}