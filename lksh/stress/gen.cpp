#include"../bits/stdc++.h"
using namespace std;
int main() {
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  int n = uniform_int_distribution<int>(1, 1000)(rng);
  int m = uniform_int_distribution<int>(1, 1000)(rng);
  cout << n << ' ' << m << endl;
  for (int i = 0; i < n; ++i) {
    int type = uniform_int_distribution<int>(0, 2)(rng);
    int x = uniform_int_distribution<int>(1, 40000)(rng);
    cout << type << ' ' << x << endl;
  }
}

