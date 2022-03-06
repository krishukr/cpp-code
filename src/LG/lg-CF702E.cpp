#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll min[MAX_N][35], dp[MAX_N][35], son[MAX_N][35];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), k = read<ll>();
    for (int i = 0; i < n; i++) {
        son[i][0] = read<ll>();
    }
    for (int i = 0; i < n; i++) {
        min[i][0] = dp[i][0] = read<ll>();
    }

    for (int j = 1; j <= 34; j++) {
        for (int i = 0; i < n; i++) {
            son[i][j] = son[son[i][j - 1]][j - 1];
            dp[i][j] = dp[i][j - 1] + dp[son[i][j - 1]][j - 1];
            min[i][j] = std::min(min[i][j - 1], min[son[i][j - 1]][j - 1]);
        }
    }

    for (int i = 0; i < n; i++) {
        ll ans = 0, crt = 1e11;
        ll kk = k, x = i;
        for (int j = 34; j >= 0; j--) {
            if ((1ll << j) <= kk) {
                ans += dp[x][j];
                crt = std::min(crt, min[x][j]);
                x = son[x][j];
                kk -= (1ll << j);
            }
        }
        std::cout << ans << ' ' << crt << '\n';
    }

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}