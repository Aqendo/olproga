#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int result = 0;
        result += (a >= c && b > d || a > c && b >= d) * 2;
        result += (a > d && b >= c || a >= d && b > c) * 2;
        cout << result << '\n';
    }
}
