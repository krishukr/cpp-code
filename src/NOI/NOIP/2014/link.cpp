#include <cstdio>
#include <iostream>

constexpr int MAX_N = 400000;
constexpr int MOD = 10007;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], w[MAX_N];
int cnt, ans, mm;

void create(int u, int v);

void it(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    for (int i = 1; i <= n; i++) {
        it(i);
    }

    std::cout << mm << ' ' << (ans * 2) % MOD << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void it(int x) {
    int res = 0, t1 = 0, t2 = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;

        if (w[v] > t1) {
            t2 = t1;
            t1 = w[v];
        } else if (w[v] > t2) {
            t2 = w[v];
        }

        ans += res * w[v];
        ans %= MOD;
        res += w[v];
        res %= MOD;
    }

    mm = std::max(mm, t1 * t2);
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