#include <algorithm>
#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    string orig, his;
    cin >> orig >> his;
    if (orig[0] != his[0]) {
        cout << "Yes\n";
        return;
    }
    string s = orig + "#" + his;
    vector<int> z_func(s.size());
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); ++i) {
        z_func[i] = min(max(0, r - i), z_func[i - l]);
        while (i + z_func[i] < s.size() && s[i + z_func[i]] == s[z_func[i]]) {
            z_func[i]++;
        }
        if (i + z_func[i] > r) {
            r = i + z_func[i];
            l = i;
        }
    }
    // debug(s);
    // debug(Z);
    int offset = orig.size() + 1;
    int n = his.size();
    int max_current_len = 1;
    int current_index = 0;
    bool already_printed_something = false;
    vector<char> result;
    result.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        // debug(current_index, max_current_len, Z[i + offset], i, offset);
        if (z_func[i + offset] > max_current_len - current_index) {
            if (already_printed_something) result.push_back(' ');
            max_current_len = z_func[i + offset];
            current_index = 0;
        }
        if (current_index == max_current_len) {
            cout << "Yes\n";
            return;
        }
        already_printed_something = true;
        result.push_back(orig[current_index]);
        current_index++;
    }
    cout << "No\n";
    for (char c : result) cout << c;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
