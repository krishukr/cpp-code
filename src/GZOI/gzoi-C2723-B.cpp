#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MAX_M = 25;

int nxt[MAX_M];
int f[MAX_N][MAX_M], g[MAX_M][MAX_M];

void init(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    ll n, m, MOD;
    std::cin >> n >> m >> MOD;
    std::string s;
    std::cin >> s;
    init(s);

    nxt[0] = 0;
    for (int i = 0; i < m; i++) {
        for (char j = '0'; j <= '9'; j++) {
            int k = i;
            while (s[k] != j and k > 0) {
                k = nxt[k];
            }
            if (s[k] == j) {
                k++;
            }
            if (k < m) {
                g[i][k]++;
            }
        }
    }

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                f[i][j] += f[i - 1][k] * g[k][j] % MOD;
                f[i][j] %= MOD;
            }
        }
    }

    ll ans{};
    for (int i = 0; i < m; i++) {
        ans += f[n][i];
        ans %= MOD;
    }
    std::cout << ans << '\n';

    return 0;
}

void init(std::string s) {
    int i = 0, j;
    nxt[0] = j = -1;
    while (i < s.length()) {
        if (j == -1 or s[i] == s[j]) {
            nxt[++i] = ++j;
        } else {
            j = nxt[j];
        }
    }
}