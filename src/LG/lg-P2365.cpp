#include <cstdio>
#include <cstring>
#include <iostream>

#define int long long

const int MAX_N = 5050;

int dp[MAX_N], t[MAX_N], c[MAX_N], q[MAX_N];

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), s = read<int>();

    for (int i = 1; i <= n; i++) {
        t[i] = read<int>(), c[i] = read<int>();

        t[i] += t[i - 1];
        c[i] += c[i - 1];
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    int front = 1, back = 1;

    for (int i = 1; i <= n; i++) {
        while (front < back and
               dp[q[front + 1]] - dp[q[front]] <=
                   (s + t[i]) * (c[q[front + 1]] - c[q[front]])) {
            front++;
        }

        dp[i] =
            dp[q[front]] + t[i] * c[i] + s * c[n] - c[q[front]] * (s + t[i]);

        while (front < back and
               (dp[i] - dp[q[back]]) * (c[q[back]] - c[q[back - 1]]) <=
                   (dp[q[back]] - dp[q[back - 1]]) * (c[i] - c[q[back]])) {
            back--;
        }

        q[++back] = i;
    }

    std::cout << dp[n] << '\n';

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