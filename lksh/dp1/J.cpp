#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

const int BIT_COUNT = 32;
const int MAX_LEN_ARRAY = 1 << (BIT_COUNT / 2 + 1);

vector<int> lg_(MAX_LEN_ARRAY);

struct Element {
    long long weight, cost, mask;
};

struct Sparse {
    vector<vector<pair<int, long long>>> sparse;

    Sparse(vector<Element>& arr)
        : sparse(lg_[arr.size()] + 1,
                 vector<pair<int, long long>>(arr.size())) {
        for (int i = 0; i < arr.size(); ++i) {
            sparse[0][i] = {i, arr[i].cost};
        }
        for (int power = 1; power <= lg_[arr.size()]; ++power) {
            for (int i = 0; i < arr.size(); ++i) {
                int index = i + (1 << (power - 1));
                sparse[power][i] = sparse[power - 1][i];
                if (index < arr.size() &&
                    sparse[power][i].second < sparse[power - 1][index].second) {
                    sparse[power][i] = sparse[power - 1][index];
                }
            }
        }
    }

    pair<int, long long> get_max(int l, int r) {
        long long lg = lg_[r - l + 1];
        pair<int, long long> res = sparse[lg][l];
        int index = r - (1 << lg) + 1;
        if (index < sparse[0].size() && res.second < sparse[lg][index].second) {
            res = sparse[lg][index];
        }
        return res;
    }
};

string to_string(const Element& el) {
    string s = "(" + to_string(el.weight) + "; " + to_string(el.cost) + ")";
    return s;
}

void solve() {
    int n;
    long long l, r;
    cin >> n >> l >> r;

    vector<Element> first(n / 2);
    vector<Element> second(n - n / 2);

    for (int i = 0; i < n / 2; ++i) {
        cin >> first[i].weight >> first[i].cost;
    }
    for (int i = 0; i < n - n / 2; ++i) {
        cin >> second[i].weight >> second[i].cost;
    }

    vector<Element> possible_first;
    vector<Element> possible_second;

    for (int mask = 0; mask < 1 << (n / 2); ++mask) {
        long long sum_weight = 0;
        long long sum_cost = 0;
        for (int bit = 0; bit < BIT_COUNT; ++bit) {
            if (mask >> bit & 1) {
                sum_weight += first[bit].weight;
                sum_cost += first[bit].cost;
            }
        }
        possible_first.push_back({sum_weight, sum_cost, mask});
    }

    for (int mask = 0; mask < 1 << (n - n / 2); ++mask) {
        long long sum_weight = 0;
        long long sum_cost = 0;
        for (int bit = 0; bit < BIT_COUNT; ++bit) {
            if (mask >> bit & 1) {
                sum_weight += second[bit].weight;
                sum_cost += second[bit].cost;
            }
        }
        possible_second.push_back({sum_weight, sum_cost, mask});
    }

    auto cmp = [](auto& p1, auto& p2) {
        if (p1.weight != p2.weight) return p1.weight < p2.weight;
        return p1.cost < p2.cost;
    };

    sort(possible_first.begin(), possible_first.end(), cmp);
    sort(possible_second.begin(), possible_second.end(), cmp);

    Sparse second_sparse(possible_second);
    long long mx = 0;
    pair<long long, long long> index_first_and_index_second;

    for (auto& [weight, cost, mask] : possible_first) {
        int index_second =
            upper_bound(possible_second.begin(), possible_second.end(),
                        Element{r - weight, LLONG_MAX}, cmp) -
            possible_second.begin() - 1;

        int index_first =
            lower_bound(possible_second.begin(), possible_second.end(),
                        Element{l - weight, LLONG_MIN}, cmp) -
            possible_second.begin();

        if (index_first <= index_second) {
            pair<int, long long> result =
                second_sparse.get_max(index_first, index_second);
            if (result.second + cost > mx) {
                mx = result.second + cost;
                index_first_and_index_second = {
                    mask, possible_second[result.first].mask};
            }
        }
    }
    vector<int> answer;
    long long resulting_weight = 0;
    for (int bit = 0; bit < BIT_COUNT; ++bit) {
        if (index_first_and_index_second.first >> bit & 1) {
            answer.push_back(bit + 1);
            resulting_weight += first[bit].weight;
        }
    }
    for (int bit = 0; bit < BIT_COUNT; ++bit) {
        if (index_first_and_index_second.second >> bit & 1) {
            answer.push_back(n / 2 + bit + 1);
            resulting_weight += second[bit].weight;
        }
    }
    if (l <= resulting_weight && resulting_weight <= r) {
        cout << answer.size() << '\n';
        for (int i : answer) {
            cout << i << ' ';
        }
    } else {
        cout << "0\n";
    }
}

signed main() {
    lg_[1] = 0;
    for (int i = 2; i < MAX_LEN_ARRAY; ++i) {
        lg_[i] = lg_[i >> 1] + 1;
    }
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
