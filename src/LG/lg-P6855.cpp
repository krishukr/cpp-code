#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 2050;

ll a[MAX_N][MAX_N], dp1[MAX_N][MAX_N], dp2[MAX_N][MAX_N], u[MAX_N][MAX_N],
    d[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = read<int>();
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp1[i][j] = std::max(dp1[i][j - 1], dp1[i - 1][j]) + a[i][j];
        }
    }
    for (int i = n; i > 0; i--) {
        for (int j = m; j > 0; j--) {
            dp2[i][j] = std::max(dp2[i][j + 1], dp2[i + 1][j]) + a[i][j];
        }
    }

    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            u[i][j] = std::max(u[i][j - 1], dp1[i][j - 1] + dp2[i + 1][j - 1]);
            d[i][j] = std::max(d[i - 1][j], dp1[i - 1][j] + dp2[i - 1][j + 1]);

            ans = std::min(ans,
                           std::max(std::max(u[i][j], d[i][j]),
                                    dp1[i][j] + dp2[i][j] - a[i][j] - a[i][j]));
        }
    }

    std::cout << ans << '\n';

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