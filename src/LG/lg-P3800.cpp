#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 5050;

struct Q {
    int x;
    int y;
    int z;
} q[MAX_N];

int dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), k = read<int>(), t = read<int>();
    for (int i = 1; i <= k; i++) {
        q[i].x = read<int>();
        q[i].y = read<int>();
        q[i].z = read<int>();
    }
    std::sort(q + 1, q + k + 1,
              [](const Q &a, const Q &b) -> bool { return a.x < b.x; });

    for (int i = 1; i <= k; i++) {
        dp[i] = q[i].z;
        for (int j = 1; j < i; j++) {
            if (std::abs(q[i].y - q[j].y) <= t * std::abs(q[i].x - q[j].x)) {
                dp[i] = std::max(dp[i], dp[j] + q[i].z);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= k; i++) {
        ans = std::max(ans, dp[i]);
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