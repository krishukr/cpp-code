#include <cstring>
#include <iostream>

const int MAX_N = 500005;

int nxt[MAX_N], dp[MAX_N], head[MAX_N];

void init(std::string s);

bool check(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    std::string t;
    std::cin >> t;
    if (check(t)) {
        return 0;
    }
    init(t);
    for (int i = 2; i <= t.length(); i++) {
        dp[i] = i;
        if (head[dp[nxt[i]]] >= i - nxt[i]) {
            dp[i] = dp[nxt[i]];
        }
        head[dp[i]] = i;
    }
    std::cout << dp[t.length()] << '\n';

    return 0;
}

bool check(std::string s) {
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] != s[i + 1]) {
            return false;
        }
    }
    std::cout << 1 << '\n';
    return true;
}

void init(std::string s) {
    int i = 0, j;
    nxt[0] = j = -1;
    dp[1] = 1;
    while (i < s.length()) {
        if (j == -1 or s[i] == s[j]) {
            nxt[++i] = ++j;
        } else {
            j = nxt[j];
        }
    }
}