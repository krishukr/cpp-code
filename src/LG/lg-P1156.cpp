#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

const int MAX_N = 1050;

struct Node {
    int t;
    int h;
    int f;

    bool operator<(const Node &n) const { return t < n.t; }
} r[MAX_N];

int dp[2][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int d = read<int>(), g = read<int>(), ans = INT_MIN;
    for (int i = 1; i <= g; i++) {
        r[i].t = read<int>();
        r[i].h = read<int>();
        r[i].f = read<int>();
    }
    std::sort(r + 1, r + g + 1);
    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 10;

    for (int i = 1; i <= g; i++) {
        int crt = i & 1, pre = crt ^ 1;
        memset(dp[crt], -0x3f, sizeof(dp[crt]));
        for (int j = d; j >= 0; j--) {
            if (dp[pre][j] < r[i].t - r[i - 1].t) {
                continue;
            }
            if (j + r[i].f >= d) {
                std::cout << r[i].t << '\n';
                exit(0);
            }
            dp[crt][j + r[i].f] =
                std::max(dp[crt][j + r[i].f], dp[pre][j] - r[i].t + r[i - 1].t);
            dp[crt][j] =
                std::max(dp[crt][j], dp[pre][j] + r[i].h - r[i].t + r[i - 1].t);
        }
        ans = std::max(ans, dp[crt][0] + r[i].t);
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
