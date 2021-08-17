#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int b;
    int e;
    int w;
    int nxt;
} node[MAX_N];

int head[MAX_N], dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), r = read<int>();

    for (int i = 1; i <= m; i++) {
        node[i].b = read<int>();
        node[i].e = read<int>();
        node[i].w = read<int>();
        node[i].nxt = head[node[i].e];
        head[node[i].e] = i;
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        for (int j = head[i]; j; j = node[j].nxt) {
            int b = node[j].b, w = node[j].w;
            dp[i] = std::max(dp[i], dp[std::max(0, b - r)] + w);
        }
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