#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
int main() {
	string s, tmpl;
	int n = uid(1, 15);
	int n_tmpl = uid(1, 15);
	s.reserve(n); tmpl.reserve(n_tmpl);
	for (int i = 0; i < n; ++i) {
		s.push_back('A' + uid(0, 23));
	}
	for (int i = 0; i < n_tmpl; ++i) {
		int move = uid(1, 3);
		if (move == 1) {
			tmpl.push_back('A' + uid(0, 23));
		} else if (move == 2) {
			tmpl.push_back('*');
		} else {
			tmpl.push_back('?');
		}
	}
	cout << s << '\n' << tmpl << endl;
}
