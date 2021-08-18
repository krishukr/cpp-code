#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 2050;

int q[MAX_N], dis[MAX_N], f[MAX_N], dep[MAX_N];
int ans;

void it(int x);

inline bool cmp(const int x, const int y) { return dep[x] > dep[y]; }

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        dis[i] = 0x3f3f3f3f;
        q[i] = i;
    }
    dis[0] = 0x3f3f3f3f;

    for (int i = 2; i <= n; i++) {
        f[i] = read<int>();

        dep[i] = dep[f[i]] + 1;
        q[i] = i;
    }

    std::sort(q + 1, q + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
        it(q[i]);
    }

    std::cout << ans << '\n';

    return 0;
}

void it(int x) {
    int fa = f[x], gf = f[fa];
    dis[x] = std::min(dis[x], std::min(dis[fa] + 1, dis[gf] + 2));

    if (dis[x] > 2) {
        dis[gf] = 0;
        ans++;
        dis[f[gf]] = std::min(dis[f[gf]], 1);
        dis[f[f[gf]]] = std::min(dis[f[f[gf]]], 2);
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