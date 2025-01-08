#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int MAXN = 100, MOD = 1e9 + 7;
int dp[MAXN][9][8][7][6][5][4][3][2];

int add(int& a, int b) { return a + b >= MOD ? a += b - MOD : a += b; }
int sub(int a, int b) { return a - b < 0 ? a - b + MOD : a - b; }
int mult(int a, int b) { return 1ll * a * b % MOD; }

bool A[9];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int ai;
        cin >> ai;
        A[ai] = true;
    }
    if (A[1]) {
        dp[0][7][6][5][4][3][2][1][0] = 1;
    }
    if (A[2]) {
        dp[0][7][6][5][4][3][2][0][0] = 1;
    }
    if (A[3]) {
        dp[0][7][6][5][4][3][0][1][0] = 1;
    }
    if (A[4]) {
        dp[0][7][6][5][4][0][2][1][0] = 1;
    }
    if (A[5]) {
        dp[0][7][6][5][0][3][2][1][0] = 1;
    }
    if (A[6]) {
        dp[0][7][6][0][4][3][2][1][0] = 1;
    }
    if (A[7]) {
        dp[0][7][0][5][4][3][2][1][0] = 1;
    }
    if (A[8]) {
        dp[0][0][6][5][4][3][2][1][0] = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        if (A[1]) {
            for (int a2 = 0; a2 <= 1; ++a2) {
                for (int a3 = 0; a3 <= 2; ++a3) {
                    for (int a4 = 0; a4 <= 3; ++a4) {
                        for (int a5 = 0; a5 <= 4; ++a5) {
                            for (int a6 = 0; a6 <= 5; ++a6) {
                                for (int a7 = 0; a7 <= 6; ++a7) {
                                    for (int a8 = 0; a8 <= 7; ++a8) {
                                        add(dp[i + 1][min<int>(a8 + 1, 7)][min<int>(a7 + 1, 6)][min<int>(a6 + 1, 5)][min<int>(a5 + 1, 4)][min<int>(a4 + 1, 3)][min<int>(a3 + 1, 2)][min<int>(a2 + 1, 1)][0], dp[i][a8][a7][a6][a5][a4][a3][a2][0]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (A[2]) {
            for (int a1 = 0; a1 <= 1; ++a1) {
                for (int a3 = 0; a3 <= 3; ++a3) {
                    for (int a4 = 0; a4 <= 4; ++a4) {
                        for (int a5 = 0; a5 <= 5; ++a5) {
                            for (int a6 = 0; a6 <= 6; ++a6) {
                                for (int a7 = 0; a7 <= 7; ++a7) {
                                    for (int a8 = 0; a8 <= 8; ++a8) {
                                        add(dp[i + 1][min<int>(a8 + 1, 7)][min<int>(a7 + 1, 6)][min<int>(a6 + 1, 5)][min<int>(a5 + 1, 4)][min<int>(a4 + 1, 3)][min<int>(a3 + 1, 2)][0][min<int>(a1 + 1, 0)], dp[i][a8][a7][a6][a5][a4][a3][1][a1]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (A[3]) {
            for (int a1 = 0; a1 <= 1; ++a1) {
                for (int a2 = 0; a2 <= 2; ++a2) {
                    for (int a4 = 0; a4 <= 4; ++a4) {
                        for (int a5 = 0; a5 <= 5; ++a5) {
                            for (int a6 = 0; a6 <= 6; ++a6) {
                                for (int a7 = 0; a7 <= 7; ++a7) {
                                    for (int a8 = 0; a8 <= 8; ++a8) {
                                        add(dp[i + 1][min<int>(a8 + 1, 7)][min<int>(a7 + 1, 6)][min<int>(a6 + 1, 5)][min<int>(a5 + 1, 4)][min<int>(a4 + 1, 3)][0][min<int>(a2 + 1, 1)][min<int>(a1 + 1, 0)], dp[i][a8][a7][a6][a5][a4][2][a2][a1]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (A[4]) {
            for (int a1 = 0; a1 <= 1; ++a1) {
                for (int a2 = 0; a2 <= 2; ++a2) {
                    for (int a3 = 0; a3 <= 3; ++a3) {
                        for (int a5 = 0; a5 <= 5; ++a5) {
                            for (int a6 = 0; a6 <= 6; ++a6) {
                                for (int a7 = 0; a7 <= 7; ++a7) {
                                    for (int a8 = 0; a8 <= 8; ++a8) {
                                        add(dp[i + 1][min<int>(a8 + 1, 7)][min<int>(a7 + 1, 6)][min<int>(a6 + 1, 5)][min<int>(a5 + 1, 4)][0][min<int>(a3 + 1, 2)][min<int>(a2 + 1, 1)][min<int>(a1 + 1, 0)], dp[i][a8][a7][a6][a5][3][a3][a2][a1]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (A[5]) {
            for (int a1 = 0; a1 <= 1; ++a1) {
                for (int a2 = 0; a2 <= 2; ++a2) {
                    for (int a3 = 0; a3 <= 3; ++a3) {
                        for (int a4 = 0; a4 <= 4; ++a4) {
                            for (int a6 = 0; a6 <= 6; ++a6) {
                                for (int a7 = 0; a7 <= 7; ++a7) {
                                    for (int a8 = 0; a8 <= 8; ++a8) {
                                        add(dp[i + 1][min<int>(a8 + 1, 7)][min<int>(a7 + 1, 6)][min<int>(a6 + 1, 5)][0][min<int>(a4 + 1, 3)][min<int>(a3 + 1, 2)][min<int>(a2 + 1, 1)][min<int>(a1 + 1, 0)], dp[i][a8][a7][a6][4][a4][a3][a2][a1]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (A[6]) {
            for (int a1 = 0; a1 <= 1; ++a1) {
                for (int a2 = 0; a2 <= 2; ++a2) {
                    for (int a3 = 0; a3 <= 3; ++a3) {
                        for (int a4 = 0; a4 <= 4; ++a4) {
                            for (int a5 = 0; a5 <= 5; ++a5) {
                                for (int a7 = 0; a7 <= 7; ++a7) {
                                    for (int a8 = 0; a8 <= 8; ++a8) {
                                        add(dp[i + 1][min<int>(a8 + 1, 7)][min<int>(a7 + 1, 6)][0][min<int>(a5 + 1, 4)][min<int>(a4 + 1, 3)][min<int>(a3 + 1, 2)][min<int>(a2 + 1, 1)][min<int>(a1 + 1, 0)], dp[i][a8][a7][5][a5][a4][a3][a2][a1]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (A[7]) {
            for (int a1 = 0; a1 <= 1; ++a1) {
                for (int a2 = 0; a2 <= 2; ++a2) {
                    for (int a3 = 0; a3 <= 3; ++a3) {
                        for (int a4 = 0; a4 <= 4; ++a4) {
                            for (int a5 = 0; a5 <= 5; ++a5) {
                                for (int a6 = 0; a6 <= 6; ++a6) {
                                    for (int a8 = 0; a8 <= 8; ++a8) {
                                        add(dp[i + 1][min<int>(a8 + 1, 7)][0][min<int>(a6 + 1, 5)][min<int>(a5 + 1, 4)][min<int>(a4 + 1, 3)][min<int>(a3 + 1, 2)][min<int>(a2 + 1, 1)][min<int>(a1 + 1, 0)], dp[i][a8][6][a6][a5][a4][a3][a2][a1]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (A[8]) {
            for (int a1 = 0; a1 <= 1; ++a1) {
                for (int a2 = 0; a2 <= 2; ++a2) {
                    for (int a3 = 0; a3 <= 3; ++a3) {
                        for (int a4 = 0; a4 <= 4; ++a4) {
                            for (int a5 = 0; a5 <= 5; ++a5) {
                                for (int a6 = 0; a6 <= 6; ++a6) {
                                    for (int a7 = 0; a7 <= 7; ++a7) {
                                        add(dp[i + 1][0][min<int>(a7 + 1, 6)][min<int>(a6 + 1, 5)][min<int>(a5 + 1, 4)][min<int>(a4 + 1, 3)][min<int>(a3 + 1, 2)][min<int>(a2 + 1, 1)][min<int>(a1 + 1, 0)], dp[i][7][a7][a6][a5][a4][a3][a2][a1]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int answer = 0;
    for (int a1 = 0; a1 <= 1; ++a1) {
        for (int a2 = 0; a2 <= 2; ++a2) {
            for (int a3 = 0; a3 <= 3; ++a3) {
                for (int a4 = 0; a4 <= 4; ++a4) {
                    for (int a5 = 0; a5 <= 5; ++a5) {
                        for (int a6 = 0; a6 <= 6; ++a6) {
                            for (int a7 = 0; a7 <= 7; ++a7) {
                                for (int a8 = 0; a8 <= 8; ++a8) {
                                    add(answer, dp[n - 1][a8][a7][a6][a5][a4][a3][a2][a1]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}