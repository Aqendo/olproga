# pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;
# ifdef SEREGA
auto __freopn = freopen("input.txt", "r", stdin);
# endif
# define debug(x) cout << #x << " = " << x << endl;
int SQR = 500;
const int UP_TO = 1e9 + 10;
const int REB_C = 5e5 / SQR * 2;
const int GET = 1, SET = 2, REVERSE = 3;
struct Sorted {
    bool is_sorted = false;
    vector<int> numbers;
    Sorted() = default;
    void rebase(const vector<int>& arr) {
        numbers = arr;
        is_sorted = false;
    }
    int get(int r) {
        if (!is_sorted) {
            sort(numbers.begin(), numbers.end());
            is_sorted = true;
        }
        auto it = upper_bound(numbers.begin(), numbers.end(), r);
        if (it == numbers.begin()) return 0;
        it--;
        return it - numbers.begin() + 1;
    }
};
struct Node {
    vector<int> els;
    int all_set_to = -1;
    Sorted sorted;
    int8_t is_reversed = false;
};
vector<Node> korn;
void apply_addition(int i) {
    if (korn[i].all_set_to == -1) return;
    for (int j = 0; j < (int)korn[i].els.size(); ++j) {
        korn[i].els[j] = korn[i].all_set_to;
    }
    korn[i].all_set_to = -1;
    korn[i].sorted.rebase(korn[i].els);
}
void recheck_block(int i) {
    apply_addition(i);
    korn[i].sorted = Sorted();
    korn[i].sorted.rebase(korn[i].els);
}
int OP_COUNT = 0;
void print_node(const Node& vec) {
    cout << '[';
    if (vec.els.empty()) cout << ']';
    if (vec.all_set_to == -1) {
        for (int j = 0; j < (int)vec.els.size(); ++j) {
            cout << (!vec.is_reversed ? vec.els[j] : vec.els[(int)vec.els.size() - 1 - j]);
            if (j == (int)vec.els.size() - 1) {
                cout << ']';
            } else {
                cout << ", ";
            }
        }
    } else {
        for (int j = 0; j < (int)vec.els.size(); ++j) {
            cout << vec.all_set_to;
            if (j == (int)vec.els.size() - 1) {
                cout << ']';
            } else {
                cout << ", ";
            }
        }
    }
}
void print(vector<Node>& vec) {
    cout << '[';
    for (int i = 0; i < (int)vec.size(); ++i) {
        print_node(vec[i]);
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
            if (korn[i].all_set_to == -1) {
                if (!korn[i].is_reversed) {
                    arr.push_back(korn[i].els[j]);
                } else {
                    arr.push_back(korn[i].els[(int)korn[i].els.size() - 1 - j]);
                }
            } else {
                arr.push_back(korn[i].all_set_to);
            }
        }
    }

    korn.assign(n / SQR + 1, {});
    for (int i = 0; i < n; ++i) {
        int t = arr[i];
        korn[i / SQR].els.push_back(t);
    }
    for (int i = 0; i < (int)korn.size(); ++i) {
        korn[i].sorted.rebase(korn[i].els);
    }
}

void revert(int lindex, int rindex) {
    if (REB_C <= (int)korn.size()) {
        rebuild();
    }
    // cout << "REVERT [" << lindex << ";" << rindex << "]" << endl;
    pair<int, int> from_block = find_block(lindex);
    pair<int, int> to_block = find_block(rindex);
    apply_addition(from_block.first);
    apply_addition(to_block.first);
    // debug(from_block.first);
    // debug(from_block.second);
    // debug(to_block.first);
    // debug(to_block.second);

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
    // cout << "reverting\n";
    // print(korn);
    korn.insert(korn.begin() + from_block.first + 1, Node{});
    // print(korn);
    // debug(korn.size());
    for (int i = (int)korn[from_block.first].els.size() - 1; i >= from_block.second; --i) {
        // debug(korn.size());
        // debug(from_block.first);
        // debug(korn[from_block.first].size());
        // print(korn);
        int what_to_push = korn[from_block.first].els.back();
        korn[from_block.first + 1].els.push_back(what_to_push);
        korn[from_block.first].els.pop_back();
    }
    recheck_block(from_block.first);
    recheck_block(from_block.first + 1);
    reverse(korn[from_block.first + 1].els.begin(), korn[from_block.first + 1].els.end());
    to_block.first++;
    // cout << "after left split" << endl;
    // print(korn);
    // split right side
    korn.insert(korn.begin() + to_block.first + 1, Node{});

    for (int i = (int)korn[to_block.first].els.size() - 1; i > to_block.second; --i) {
        korn[to_block.first + 1].els.push_back(korn[to_block.first].els.back());
        korn[to_block.first].els.pop_back();
    }
    recheck_block(to_block.first);
    recheck_block(to_block.first + 1);
    reverse(korn[to_block.first + 1].els.begin(), korn[to_block.first + 1].els.end());
    // print(korn);
    int from = from_block.first + 1, to = to_block.first;
    // debug(from);
    // debug(to);
    while (from < to) {
        swap(korn[from], korn[to]);
        korn[from].is_reversed = !korn[from].is_reversed;
        korn[to].is_reversed = !korn[to].is_reversed;
        from++;
        to--;
    }
    if (from == to) {
        korn[from].is_reversed = !korn[from].is_reversed;
    }
}

int get(int l, int r, int x) {
    if (REB_C <= (int)korn.size()) {
        rebuild();
    }
    // print(korn);
    pair<int, int> from_block = find_block(l);
    pair<int, int> to_block = find_block(r);
    apply_addition(from_block.first);
    apply_addition(to_block.first);
    // print(korn);
    // cout << from_block.first << ' ' << from_block.second << '\n';
    // cout << to_block.first << ' ' << to_block.second << '\n';

    int sum = 0;
    for (int i = from_block.second; i < (int)korn[from_block.first].els.size(); ++i) {
        if (korn[from_block.first].all_set_to == -1) {
            if (!korn[from_block.first].is_reversed) {
                sum += korn[from_block.first].els[i] >= x;
            } else {
                sum += korn[from_block.first].els[(int)korn[from_block.first].els.size() - 1 - i] >= x;
            }
        } else {
            sum += korn[from_block.first].all_set_to >= x;
        }
    }
    int from = from_block.first + 1;
    for (int i = 0; i <= (int)to_block.second; ++i) {
        if (korn[to_block.first].all_set_to == -1) {
            if (!korn[to_block.first].is_reversed) {
                sum += korn[to_block.first].els[i] >= x;
            } else {
                sum += korn[to_block.first].els[(int)korn[to_block.first].els.size() - 1 - i] >= x;
            }
        } else {
            sum += korn[to_block.first].all_set_to >= x;
        }
    }
    int to = to_block.first - 1;
    while (from <= to) {
        // cout << "mins: " << korn[from].mn << ' ' << korn[to].mn << '\n';
        if (from != to) {
            int delta_from;
            if (korn[from].all_set_to == -1) {
                delta_from = (int)korn[from].els.size() - korn[from].sorted.get(x - 1);
            } else {
                delta_from = (int)korn[from].els.size() * (int)(korn[from].all_set_to >= x);
            }
            // cout << "ind = " << from << ", in ";
            // print_node(korn[from]);
            // cout << " we have >=" << x << " in " << delta_from << '\n';
            sum += delta_from;

            int delta_to;
            if (korn[to].all_set_to == -1) {
                delta_to = (int)korn[to].els.size() - korn[to].sorted.get(x - 1);
            } else {
                delta_to = (int)korn[to].els.size() * (int)(korn[to].all_set_to >= x);
            }
            // cout << "ind = " << to << ", in ";
            // print_node(korn[to]);
            // cout << " we have >=" << x << " in " << delta_to << '\n';
            sum += delta_to;
        } else {
            int delta_from;
            if (korn[from].all_set_to == -1) {
                delta_from = (int)korn[from].els.size() - korn[from].sorted.get(x - 1);
            } else {
                delta_from = (int)korn[from].els.size() * (int)(korn[from].all_set_to >= x);
            }
            // cout << "ind = " << from << ", in ";
            // print_node(korn[from]);
            // cout << " we have >=" << x << " in " << delta_from << '\n';
            sum += delta_from;
        }
        from++;
        to--;
    }
    return sum;
}

void set_(int l, int r, int x) {
    if (REB_C <= (int)korn.size()) {
        rebuild();
    }
    pair<int, int> from_block = find_block(l);
    pair<int, int> to_block = find_block(r);
    apply_addition(from_block.first);
    apply_addition(to_block.first);
    // print(korn);
    // cout << from_block.first << ' ' << from_block.second << '\n';
    // cout << to_block.first << ' ' << to_block.second << '\n';

    for (int i = from_block.second; i < (int)korn[from_block.first].els.size(); ++i) {
        if (!korn[from_block.first].is_reversed) {
            // cout << "was = " << korn[from_block.first].els[i] << '\n';
            korn[from_block.first].els[i] = x;
        } else {
            // cout << "was = " << korn[from_block.first].els[(int)korn[from_block.first].els.size() - 1 - i] << '\n';
            korn[from_block.first].els[(int)korn[from_block.first].els.size() - 1 - i] = x;
        }
    }
    korn[from_block.first].sorted.rebase(korn[from_block.first].els);
    int from = from_block.first + 1;
    for (int i = 0; i <= (int)to_block.second; ++i) {
        if (!korn[to_block.first].is_reversed) {
            // cout << "was = " << korn[to_block.first].els[i] << '\n';
            korn[to_block.first].els[i] = x;
        } else {
            // cout << "was = " << korn[to_block.first].els[(int)korn[to_block.first].els.size() - 1 - i] << '\n';
            korn[to_block.first].els[(int)korn[to_block.first].els.size() - 1 - i] = x;
        }
    }
    korn[to_block.first].sorted.rebase(korn[to_block.first].els);
    int to = to_block.first - 1;
    while (from <= to) {
        // cout << "mins: " << korn[from].mn << ' ' << korn[to].mn << '\n';
        if (from != to) {
            korn[from].sorted = Sorted();
            korn[to].sorted = Sorted();
            korn[from].all_set_to = x;
            korn[to].all_set_to = x;
        } else {
            korn[from].sorted = Sorted();
            korn[from].all_set_to = x;
        }
        from++;
        to--;
    }
    // print(korn);
}

vector<int> input;
vector<array<int, 4>> queries;
vector<int> answers;
void solve() {
    korn.assign(n / SQR + 1, Node{});
    for (int i = 0; i < n; ++i) {
        int t = input[i];
        korn[i / SQR].els.push_back(t);
    }
    for (int i = 0; i < (int)korn.size(); ++i) {
        korn[i].sorted.rebase(korn[i].els);
    }
    for (int jj = 0; jj < m; ++jj) {
        auto [move, l, r, x] = queries[jj];
        l--;
        r--;
        if (r - l <= SQR + 2) {
            if (move == REVERSE) {
                pair<int, int> from_block = find_block(l);
                pair<int, int> to_block = find_block(r);
                int from_block_old = from_block.first;
                int to_block_old = to_block.first;
                for (int i = from_block_old; i <= to_block_old; ++i) {
                    apply_addition(i);
                }
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
                for (int block = from_block_old; block <= to_block_old; ++block) {
                    recheck_block(block);
                }
                // for (int i = 0; i < n; ++i) {
                //     cout << get_min(i, i) << ' ';
                // }
                // cout << '\n';
            } else if (move == GET) {
                int sum = 0;
                pair<int, int> from_block = find_block(l);
                pair<int, int> to_block = find_block(r);
                for (int block = from_block.first; block <= to_block.first; ++block) {
                    apply_addition(block);
                }
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
                    if (ell != elr) {
                        sum += *ell >= x;
                        sum += *elr >= x;
                    } else {
                        sum += *ell >= x;
                    }

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
                answers.push_back(sum);
            } else if (move == SET) {
                pair<int, int> from_block = find_block(l);
                pair<int, int> to_block = find_block(r);
                int from_block_old = from_block.first;
                int to_block_old = to_block.first;
                for (int block = from_block_old; block <= to_block_old; ++block) {
                    apply_addition(block);
                }
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
                    *ell = x;
                    *elr = x;
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
                for (int block = from_block_old; block <= to_block_old; ++block) {
                    recheck_block(block);
                }
            }
            continue;
        }
        if (move == REVERSE) {
            revert(l, r);
            // for (int i = 0; i < n; ++i) {
            //     cout << get_min(i, i) << ' ';
            // }
            // cout << '\n';
        } else if (move == GET) {
            answers.push_back(get(l, r, x));
            // cout << get_min(l, r) << '\n';
        } else if (move == SET) {
            set_(l, r, x);
        }
    }
}

vector<int> get_slow() {
    vector<int> arr = input;
    vector<int> res;
    for (int i = 0; i < m; ++i) {
        auto [move, l, r, x] = queries[i];
        l--;
        r--;
        if (move == REVERSE) {
            while (l < r) {
                swap(arr[l++], arr[r--]);
            }
        } else if (move == SET) {
            for (int j = l; j <= r; ++j) {
                arr[j] = x;
            }
        } else if (move == GET) {
            int result = 0;
            for (int j = l; j <= r; ++j) {
                result += arr[j] >= x;
            }
            res.push_back(result);
        }
    }
    return res;
}

vector<string> from_index = {"", "get", "set", "reverse"};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    SQR = (int)sqrt(n);
    input.assign(n, {});
    for (int i = 0; i < n; ++i) {
        cin >> input[i];
    }
    cin >> m;
    queries.assign(m, {});
    for (int i = 0; i < m; ++i) {
        string type;
        cin >> type;
        if (type == "get") {
            queries[i][0] = GET;
            cin >> queries[i][1] >> queries[i][2] >> queries[i][3];
        } else if (type == "set") {
            queries[i][0] = SET;
            cin >> queries[i][1] >> queries[i][2] >> queries[i][3];
        } else {
            queries[i][0] = REVERSE;
            cin >> queries[i][1] >> queries[i][2];
        }
    }
    // for (int i = 0; i < m; ++i) {
    //     cout << queries[i][0] << ' ' << queries[i][1] << ' ' << queries[i][2] << ' ' << queries[i][3] << '\n';
    // }
    answers.reserve(m);
    solve();
    for (int i : answers) {
        cout << i << '\n';
    }
}
