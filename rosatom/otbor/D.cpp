#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<vector<int>> gT;
int timer = 0;
map<string, int> code;
vector<pair<int, string>> reverse_code;
vector<int> answer;
string result;
int forbidden = -1;
vector<vector<int>> indicies;
void euler(int v, int remain = 1) {
    // cerr << v << ' ' << reverse_code[v].second << endl;

    while (!g[v].empty()) {
        int u = *g[v].rbegin();
        g[v].pop_back();
        // cerr << v << "->" << u << endl;
        euler(u, remain - 1);  // запускаемся от противоположного конца
    }
    if (remain <= 0) {
        // if (indicies[v].back() == forbidden) indicies[v].pop_back();
        answer.push_back(indicies[v].back());
        indicies[v].pop_back();
        result += reverse_code[v].second.back();
    }
    // выписываем текущую вершину
}
pair<string, vector<int>> solve(int n, int k, vector<string>& presegs) {
    g.assign(n + 1, {});
    gT.assign(n + 1, {});
    timer = 0;
    answer.clear();
    result.clear();
    reverse_code.clear();
    code.clear();
    indicies.assign(n + 1, {});
    for (int i = 0; i < n - k + 1; ++i) {
        string& s = presegs[i];
        string pref = s.substr(0, k - 1);
        string suff = s.substr(1, k - 1);
        int index = 0;
        if (!code.contains(pref)) {
            code[pref] = timer++;
            reverse_code.push_back({i, pref});
        }
        if (!code.contains(suff)) {
            index = code[suff] = timer++;
            reverse_code.push_back({i, suff});
        } else {
            index = code[suff];
        }
        indicies[index].push_back(i);
        // cerr << pref << "->" << suff << endl;
        // cerr << code[pref] << ' ' << index << endl;
        g[code[pref]].push_back(index);
        gT[index].push_back(code[pref]);
    }
    // на 1 больше выходит - начало, на 1 больше входит - конец
    // for (int i = 0; i < timer; ++i) {
    //     cout << reverse_code[i].second << ' ' << g[i].size() << ' ' << gT[i].size() << '\n';
    // }
    // for (int i = 0; i < timer; ++i) {
    //     for (int j : g[i]) {
    //         cout << i << ' ' << j << endl;
    //     }
    // }
    int left_more = -1, right_more = -1;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() > gT[i].size()) {
            left_more = i;
        } else if (g[i].size() < gT[i].size()) {
            right_more = i;
        }
    }
    if (left_more != -1 && right_more != -1) {
        // cout << left_more << '\n';
        forbidden = reverse_code[left_more].first;
        // answer.push_back(reverse_code[left_more].first);
        // cout << presegs[reverse_code[left_more].first];
        euler(left_more);
        string prefix = presegs[answer.back()].substr(0, k - 1);
        reverse(prefix.begin(), prefix.end());
        result += prefix;
        reverse(result.begin(), result.end());
    } else {
        // answer.push_back(reverse_code[0].first);
        forbidden = reverse_code[0].first;
        // cout << presegs[reverse_code[0].first];
        euler(0);
        string prefix = presegs[answer.back()].substr(0, k - 1);
        reverse(prefix.begin(), prefix.end());
        result += prefix;
        reverse(result.begin(), result.end());
    }
    reverse(answer.begin(), answer.end());
    return {result, answer};
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    while (true) {
        int n = uid(2, 15);
        int k = uid(2, n);
        string s;
        s.reserve(n);
        for (int i = 0; i < n; ++i) {
            s.push_back((char)(uid(0, 24) + 'a'));
        }
        // cout << n << ' ' << k << endl << s << endl;
        vector<string> presegs(n - k + 1);
        for (int i = 0; i < n - k + 1; ++i) {
            presegs[i] = s.substr(i, k);
        }
        shuffle(presegs.begin(), presegs.end(), rng);
        // for (string& ss : presegs) {
        // cout << ss << endl;
        // }
        pair<string, vector<int>> answer_ = solve(n, k, presegs);
        string result_ = presegs[answer_.second[0]];
        for (int i = 1; i < answer_.second.size(); ++i) {
            int index = (int)result_.size() - 1 - k + 2;
            if (result_.substr(index, k - 1) != presegs[answer_.second[i]].substr(0, k - 1)) {
                cout << n << ' ' << k << endl;
                for (string& ss : presegs) {
                    cout << ss << '\n';
                }
                cout << s << '\n';
                cout << answer_.first << endl;
                for (int ii : answer_.second) {
                    cout << ii << ' ';
                }
                cout << endl;
                return 0;
            }
            result_ += presegs[answer_.second[i]].back();
        }
    }
}