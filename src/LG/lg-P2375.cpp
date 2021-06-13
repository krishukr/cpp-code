#include <cstring>
#include <iostream>

const int MOD = 1000000007;
const int MAX_N = 1000010;

int nxt[MAX_N], num[MAX_N];

void init(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        memset(nxt, 0, sizeof(nxt));
        long long ans = 1;
        int j = 0;
        std::string s;
        std::cin >> s;
        init(s);
        for (int i = 1; i < s.length(); i++) {
            while (s[i] != s[j] and j) {
                j = nxt[j];
            }
            if (s[i] == s[j]) {
                j++;
            }
            while ((j << 1) > i + 1) {
                j = nxt[j];
            }
            ans *= (num[j] + 1);
            ans %= MOD;
        }
        std::cout << ans << '\n';
    }

    return 0;
}

void init(std::string s) {
    int i = 0, j;
    nxt[0] = j = -1;
    num[0] = 0;
    num[1] = 1;
    while (i < s.length()) {
        if (j == -1 or s[i] == s[j]) {
            nxt[++i] = ++j;
            num[i] = num[j] + 1;
        } else {
            j = nxt[j];
        }
    }
}