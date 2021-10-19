#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 105;

struct Que {
    int a;
    int b;

    inline bool operator<(const Que &q) const {
        return b > q.b or (b == q.b and a > q.b);
    }
} q[MAX_N];

int dp[MAX_N][MAX_N * MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), s1 = 0, s2 = 0;

    for (int i = 1; i <= n; i++) {
        q[i].a = read<int>();
        s1 += q[i].a;
    }
    for (int i = 1; i <= n; i++) {
        q[i].b = read<int>();
        s2 += q[i].b;
    }

    std::sort(q + 1, q + n + 1);
    int t = s1, cnt = 0;
    while (t > 0) {
        t -= q[++cnt].b;
    }
    std::cout << cnt << ' ';

    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = s2; j >= q[i].b; j--) {
            for (int k = 1; k <= cnt; k++) {
                dp[k][j] = std::max(dp[k][j], dp[k - 1][j - q[i].b] + q[i].a);
            }
        }
    }

    int ans = 0;
    for (int i = s1; i <= s2; i++) {
        ans = std::max(ans, dp[cnt][i]);
    }
    std::cout << s1 - ans << '\n';

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