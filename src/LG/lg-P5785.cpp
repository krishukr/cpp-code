#include <cstdio>
#include <cstring>
#include <iostream>

#define int long long

const int MAX_N = 300050;

int dp[MAX_N], t[MAX_N], c[MAX_N], q[MAX_N];
int front = 1, back = 1, n, s;

int b(int x);

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), s = read<int>();

    for (int i = 1; i <= n; i++) {
        t[i] = read<int>(), c[i] = read<int>();

        t[i] += t[i - 1];
        c[i] += c[i - 1];
    }

    memset(dp, 0x7f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int j = b(t[i]);

        dp[i] = dp[j] + t[i] * c[i] + s * c[n] - c[j] * (s + t[i]);

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

int b(int x) {
    int l = front, r = back, res = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if ((dp[q[mid + 1]] - c[q[mid + 1]] * s - dp[q[mid]] + c[q[mid]] * s) >
            x * (c[q[mid + 1]] - c[q[mid]])) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (res == -1) {
        return q[back];
    } else {
        return q[res];
    }
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