#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 30050;

int a[MAX_N], dp[MAX_N];

template <typename T>
T read();

int main() {
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        memset(dp, -63, sizeof(dp));
        dp[0] = 0;

        int n = read<int>(), res = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = read<int>();
        }
        for (int i = 1; i <= n; i++) {
            for (int j = a[i]; j <= 30000; j++) {
                dp[j] = std::max(dp[j], dp[j - a[i]] + 1);
            }
        }

        for (int i = 1; i <= n; i++) {
            if (dp[a[i]] == 1) {
                res++;
            }
        }
        std::cout << res << '\n';
    }

    fclose(stdin);
    fclose(stdout);
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