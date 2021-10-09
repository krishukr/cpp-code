#include <cstdio>
#include <iostream>

#define int long long

const int MAX_N = 50050;

int a[MAX_N], q[MAX_N], dp[MAX_N];
int n, l;

inline int x(int i);
inline int y(int i);
inline int s(int i, int j);

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), l = read<int>() + 1;

    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        a[i] += a[i - 1] + 1;
    }

    int h = 1, e = 1;

    for (int i = 1; i <= n; i++) {
        while (h < e and s(q[h], q[h + 1]) <= 2 * a[i]) {
            h++;
        }
        dp[i] = dp[q[h]] + (a[i] - a[q[h]] - l) * (a[i] - a[q[h]] - l);
        while (h < e and s(q[e - 1], i) <= s(q[e], q[e - 1])) {
            e--;
        }
        q[++e] = i;
    }

    std::cout << dp[n] << '\n';

    return 0;
}

inline int x(int i) { return a[i]; }
inline int y(int i) { return dp[i] + (a[i] + l) * (a[i] + l); }
inline int s(int i, int j) { return (y(i) - y(j)) / (x(i) - x(j)); }

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