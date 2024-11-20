#include "bits/stdc++.h"
using namespace std;
#define int int64_t
string encode_first(string s) {
    cout << 1 << endl;
    string result;
    int prev = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] - '0' >= prev) {
            for (int j = 0; j < (s[i] - '0') - prev; ++j) {
                result += (char)(i + '0');
            }
            prev = s[i] - '0';
        } else {
            int j = 0;
            while ((prev + j++) % 11 != s[i] - '0') {
                result += (char)(i + '0');
            }
            prev = s[i] - '0';
        }
        if (i == (int)s.size() - 1) {
            result += (char)(i + '0');
        }
    }
    cout << result << endl;
    return result;
}
string decode_first(string s) {
    cout << 1 << endl;
    string real;
    int prev = 0;
    int mx = *max_element(s.begin(), s.end()) - '0';
    for (int i = 0; i < mx; ++i) {
        int cnt = count(s.begin(), s.end(), i + '0');
        real += (char)((prev + cnt) % 11 + '0');
        prev = (prev + cnt) % 11;
    }
    int cnt = count(s.begin(), s.end(), mx + '0') - 1;
    real += (char)((prev + cnt) % 11 + '0');
    prev = (prev + cnt) % 11;
    return real;
}

string encode_second(string s) {
    cout << 2 << endl;
    string result;
    int prev = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] - '0' <= prev) {
            for (int j = 0; j < prev - (s[i] - '0'); ++j) {
                result += (char)(i + '0');
            }
            prev = s[i] - '0';
        } else {
            int j = 0;
            while ((prev - j++ + 10) % 10 != s[i] - '0') {
                result += (char)(i + '0');
            }
            prev = s[i] - '0';
        }
        if (i == (int)s.size() - 1) {
            result += (char)(i + '0');
        }
    }]
    return result;
}

string decode_second(string s) {
    string real;
    int prev = 0;
    int mx = *max_element(s.begin(), s.end()) - '0';
    for (int i = 0; i < mx; ++i) {
        int cnt = count(s.begin(), s.end(), i + '0');
        real += (char)(((prev - cnt) % 10 + 10) % 10 + '0');
        prev = ((prev - cnt) % 10 + 10) % 10;
    }
    int cnt = count(s.begin(), s.end(), mx + '0') - 1;
    real += (char)(((prev - cnt) % 10 + 10) % 10 + '0');
    prev = ((prev - cnt) % 10 + 10) % 10;
    return real;
}

string encode_third(string s) {
    reverse(s.begin(), s.end());
    string result;
    for (int i = 0; i < (int)s.size(); ++i) {
        for (int j = 0; j < s[i] - '0'; ++j) {
            result += (char)(i + '0');
        }
    }
    return result;
}
string decode_third(string s) {
    cout << 3 << endl;
    int result = 0;
    int power = 1;
    for (int i = 0; i < 10; ++i) {
        int cnt = count(s.begin(), s.end(), i + '0');
        if (cnt) {
            result += power * cnt;
        }
        power *= 10;
    }
    return to_string(result);
}
bool check(string s) {
    for (char c : s) {
        if (!('0' <= c && c <= '9')) return false;
    }
    return true;
}
string encode(string s) {
    if (s == "0") {
        return "111555566666999999";
    }
    string enc = encode_first(s);
    if (enc.size() <= 50) {
        if (!check(enc)) {
            throw;
        }
        return enc;
    }
    enc = encode_second(s);
    if (enc.size() <= 50) {
        if (!check(enc)) {
            throw;
        }
        return enc;
    }
    enc = encode_third(s);
    if (!check(enc)) {
        throw;
    }
    return enc;
}
string decode(string s) {
    sort(s.begin(), s.end());
    if (s == "111555566666999999") {
        return "0";
    }
    string first = decode_first(s);
    string second = decode_second(s);
    string third = decode_third(s);
    if (encode_first(third).size() > 50 && encode_second(third).size() > 50) {
        return third;
    }
    if (encode_first(second).size() > 50) {
        return second;
    }
    return first;
}
void solve() {
    // for (int i = 0; i <= 1000000; ++i) {
    //     string s = to_string(i);
    //     if (decode(encode(s)) != s) {
    //         cout << s << endl;
    //         return;
    //     }
    // }
    string move;
    cin >> move;
    if (move == "Alice") {
        string s;
        cin >> s;
        cout << decode(encode(s));
        return;
    } else {
        string s;
        cin >> s;
        cout << decode(s);
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}