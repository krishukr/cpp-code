#include <cstdio>
#include <iostream>

const int MAX_N = 10050;

bool vis[MAX_N];
int fa[MAX_N];

int find(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), u = read<int>(), p = read<int>();
    int ans1 = 0, ans2 = 0;

    for (int i = 1; i <= m; i++) {
        fa[i] = u;
    }
    fa[m] = 10001;

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        fa[x] = y;
    }

    for (int i = 1; i <= p; i++) {
        int x = read<int>();
        vis[x] = true;
        fa[x] = x;
    }

    for (int i = 1; i <= m; i++) {
        if (find(i) == u) {
            ans1++;
        } else if (vis[find(i)]) {
            ans2++;
        }
    }

    std::cout << ans1 - 1 << ' ' << ans2 << '\n';

    return 0;
}

int find(int x) {
    while (fa[x] != x) {
        x = fa[x];
    }
    return x;
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