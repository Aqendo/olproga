#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<vector<int>> gT;
int timer = 0;
map<string, int> code;
vector<string> reverse_code;
vector<int> answer;
string result;
vector<vector<int>> indicies;
void euler(int v, int first = true) {
    if (!first) {
        answer.push_back(indicies[v].back());
        indicies[v].pop_back();
        result += reverse_code[v].back();
    }
    while (!g[v].empty()) {
        int u = g[v].back();  // берем любое ребро
        g[v].pop_back();      // удаляем его
        euler(u, false);      // запускаемся от противоположного конца
    }  // выписываем текущую вершину
}
pair<string, vector<int>> solve(int n, int k, vector<string>& strs) {
    g.assign(n + 1, {});
    gT.assign(n + 1, {});
    indicies.assign(n + 1, {});
    code.clear();
    reverse_code.clear();
    answer.clear();
    result.clear();
    for (int i = 0; i < n - k + 1; ++i) {
        string s = strs[i];
        string pref = s.substr(0, k - 1);
        string suff = s.substr(1, k - 1);
        int index = 0;
        if (!code.contains(pref)) {
            code[pref] = timer++;
            reverse_code.push_back(pref);
        }
        if (!code.contains(suff)) {
            index = code[suff] = timer++;
            reverse_code.push_back(suff);
        } else {
            index = code[suff];
        }
        indicies[index].push_back(i);
        g[code[pref]].push_back(index);
        gT[index].push_back(code[pref]);
    }
    // на 1 больше выходит - начало, на 1 больше входит - конец
    // for (auto& [u, w] : code) {
    //     cout << u << ' ' << g[w].size() << ' ' << gT[w].size() << '\n';
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
        result += reverse_code[left_more];
        euler(left_more);
    } else {
        result += reverse_code[0];
        euler(0);
    }
    return {result, answer};
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chro)
}