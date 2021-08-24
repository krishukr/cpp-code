#include <cstdio>
#include <iostream>

const int MAX_N = 100;

int p[MAX_N], w[MAX_N];
int ans = 0x3f3f3f3f, n;

void dfs(int x, int ac, int su, int cl, int l, int r);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>();
    int m = read<int>(), sum = 0;

    for (int i = 1; i <= n; i++) {
        p[i] = read<int>();
        w[i] = read<int>();

        sum += w[i];
    }
    dfs(m, 0, sum - w[m], 1, m, m);

    std::cout << ans << '\n';

    return 0;
}

void dfs(int x, int ac, int su, int cl, int l, int r) {
    if (ac >= ans) {
        return;
    }
    if (cl == n) {
        ans = ac;
        return;
    }

    if (l - 1) {
        dfs(l - 1, ac + (p[x] - p[l - 1]) * su, su - w[l - 1], cl + 1, l - 1,
            r);
    }
    if (r < n) {
        dfs(r + 1, ac + (p[r + 1] - p[x]) * su, su - w[r + 1], cl + 1, l,
            r + 1);
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