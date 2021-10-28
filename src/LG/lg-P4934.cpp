#include <cstdio>
#include <functional>
#include <iostream>

const int MAX_N = 2000050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int dp[MAX_N], w[MAX_N];

void create(int u, int v);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    auto low_bit = [](const int &x) -> int { return x & -x; };

    int n = read<int>(), k = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        w[x]++;
    }

    int m = 1 << k;
    for (int i = 0; i < m; i++) {
        for (int j = i; j; j ^= low_bit(j)) {
            dp[i] = std::max(dp[i], dp[i ^ low_bit(j)]);
        }
        if (w[i]) {
            dp[i]++;
            create(dp[i], i);
        }
    }

    std::cout << 1 << '\n' << dp[m - 1] << '\n';
    for (int i = 1; i <= dp[m - 1]; i++) {
        int cnt = 0;
        for (int j = head[i]; j; j = node[j].nxt) {
            cnt++;
        }
        std::cout << cnt << ' ';
        for (int j = head[i]; j; j = node[j].nxt) {
            std::cout << node[j].v << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
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