#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Q {
    int x;
    int y;
    int z;
    int i;
} a[MAX_N], q[MAX_N];

int dp[MAX_N];
bool ans[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i].x = read<int>();
        a[i].y = read<int>();
        a[i].z = read<int>();
        a[i].i = i;
    }
    std::sort(a + 1, a + n + 1,
              [](const Q &a, const Q &b) -> bool { return a.y < b.y; });

    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        q[i].x = read<int>();
        q[i].y = read<int>();
        q[i].z = read<int>();
        q[i].i = i;
    }
    std::sort(q + 1, q + m + 1,
              [](const Q &a, const Q &b) -> bool { return a.x < b.x; });

    int j = 1;
    dp[0] = 0x3f3f3f3f;
    for (int i = 1; i <= m; i++) {
        for (; j <= n and a[j].y <= q[i].x; j++) {
            for (int k = 100050; k >= a[j].x; k--) {
                dp[k] = std::max(dp[k], std::min(dp[k - a[j].x], a[j].z));
            }
        }
        if (dp[q[i].y] > q[i].x + q[i].z) {
            ans[q[i].i] = true;
        }
    }

    for (int i = 1; i <= m; i++) {
        if (ans[i]) {
            std::cout << "TAK\n";
        } else {
            std::cout << "NIE\n";
        }
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