#include <bits/stdc++.h>
#define int int64_t
using namespace std;
void solve() {
    int x;
    cin >> x;
    vector<pair<bool, int>> road(x + 4, {true, -234});
    int w, h;
    cin >> w >> h;
    int n;
    cin >> n;
    vector<int> when_start(n);
    for (int i = 0; i < n; ++i) {
        int width;
        cin >> x >> width;
        when_start[i] = x;
        for (int j = x + 1; j < x + width; ++j) {
            road[j] = {false, i};
        }
    }
    // if from w
    int move = 1;
    set<int> answer1;
    for (int i = 0; i <= x + 3;) {
        move ^= 1;
        int start = i, end = move ? i + w : i + h;
        if (!road[start].first) {
            answer1.insert(when_start[road[start].second]);
        }
        if (!road[end].first) {
            answer1.insert(when_start[road[end].second]);
        }
        i += move ? w : h;
    }
    move = 0;
    set<int> answer2;
    for (int i = 0; i <= x + 3;) {
        move ^= 1;
        int start = i, end = move ? i + w : i + h;
        if (!road[start].first) {
            answer2.insert(when_start[road[start].second]);
        }
        if (!road[end].first) {
            answer2.insert(when_start[road[end].second]);
        }
        i += move ? w : h;
    }
    if (answer1.size() < answer2.size()) {
        cout << answer1.size() << endl;
        for (int i : answer1) {
            cout << i << '\n';
        }
    } else if (answer2.size() < answer1.size()) {
        cout << answer2.size() << endl;
        for (int i : answer2) {
            cout << i << '\n';
        }
    } else {
        int sum1 = 0;
        int sum2 = 0;
        for (int i : answer1) {
            sum1 += i;
        }
        for (int i : answer2) {
            sum2 += i;
        }
        if (sum1 < sum2) {
            cout << answer1.size() << endl;
            for (int i : answer1) {
                cout << i << '\n';
            }
        } else {
            cout << answer2.size() << endl;
            for (int i : answer2) {
                cout << i << '\n';
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}