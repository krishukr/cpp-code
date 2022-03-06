#include <algorithm>
#include <cstdio>
#include <iostream>

int u[35], v[35], w[35], fa[35];
int ans[1 << 26];

int n, m, tot;

inline void init(int n);

inline int find(int x);

inline void merge(int i, int j);

inline int calc(int x);

int work(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        u[i] = read<int>();
        v[i] = read<int>();
        w[i] = read<int>();
    }

    for (int i = 1; i < (1 << m); i++) {
        if (calc(i) != n - 1) {
            continue;
        } else {
            ans[++tot] = work(i);
        }
    }
    std::sort(ans + 1, ans + tot + 1);

    int q = read<int>();
    while (q--) {
        int x = read<int>(), y = read<int>();
        std::cout << std::upper_bound(ans + 1, ans + tot + 1, y) -
                         std::upper_bound(ans + 1, ans + tot + 1, x - 1)
                  << '\n';
    }

    return 0;
}

inline void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

inline int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

inline void merge(int i, int j) { fa[find(i)] = find(j); }

inline int calc(int x) {
    int res = 0;
    while (x) {
        x &= (x - 1);
        res++;
    }
    return res;
}

int work(int x) {
    init(n);
    int res = 0;
    for (int i = 1; i <= m; i++) {
        if (1 << (i - 1) & x) {
            if (find(u[i]) == find(v[i])) {
                return 0;
            } else {
                merge(u[i], v[i]);
                res += w[i];
            }
        }
    }
    return res;
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