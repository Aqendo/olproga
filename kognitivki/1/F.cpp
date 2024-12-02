#include "bits/stdc++.h"
using namespace std;
#define int int64_t

int ask(int a, int d) {
    cout << "? " << a << ' ' << d << endl;
    int answer;
    cin >> answer;
    return answer;
}

void solve() {
    vector<int> is_odd(2000001);
    is_odd[1] = true;
    vector<int> primes;
    set<int> dels;
    int first_mod = 1 << 8;
    for (int i = 2; i <= 2000000; ++i) {
        if (!is_odd[i]) {
            primes.push_back(i);
            dels.insert(i % first_mod);
            for (int j = i * i; j <= 2000000; j += i) {
                is_odd[j] = true;
            }
        }
    }
    int the_one = -1;
    for (int i : dels) {
        if (ask(first_mod, i)) {
            the_one = i;
            break;
        }
    }
    assert(the_one != -1);
    int second_mod = 2e6;
    for (int i : primes) {
        if (i % first_mod == the_one) {
            if (ask(second_mod, i)) {
                cout << "! " << i << endl;
                return;
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
