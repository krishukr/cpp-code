#include <climits>
#include <iostream>

const int MAX_N = 100050;

int num[MAX_N], dp[MAX_N];

inline int read();

int main() {
    std::ios::sync_with_stdio(false);
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);

    int n = read(), ans = INT_MIN, tmp = INT_MIN, crt = INT_MIN;
    for (int i = 1; i <= n; i++) {
        num[i] = read();
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = std::max(dp[i - 1] + num[i], num[i]);
    }
    for (int i = n; i > 1; i--) {
        tmp = std::max(tmp + num[i], num[i]);
        crt = std::max(crt, tmp);
        ans = std::max(ans, crt + dp[i - 1]);
    }

    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

inline int read() {
    int x = 0, f = 1, ch = getchar();
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