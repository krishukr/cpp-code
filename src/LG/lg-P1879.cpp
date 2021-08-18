#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_L = 12;
const int MAX_N = 15;
const long long MOD = 100000000;

int mp[1 << MAX_L];
long long ans[MAX_N][1 << MAX_L];
int n, m;

int dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x = read<int>();

            mp[i] <<= 1;
            mp[i] |= x;
        }
    }

    std::cout << dfs(1, 0) << '\n';

    return 0;
}

int dfs(int x, int f) {
    if (ans[x][f]) {
        return ans[x][f];
    }
    if (x > n) {
        return 1;
    }

    bool vis[1 << MAX_L];
    memset(vis, 0, sizeof(vis));

    for (int i = 0; i < 1 << m; i++) {
        if (i & (i * 2) or i & f) {
            continue;
        }
        int tmp = i & mp[x];

        if (vis[tmp]) {
            continue;
        }
        ans[x][f] += dfs(x + 1, tmp);
        ans[x][f] %= MOD;
        vis[tmp] = true;
    }

    return ans[x][f];
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