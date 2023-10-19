#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;

int fa[MAX_N], w[MAX_N];
int p;

int find(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, i;
    read(n, m, p);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (i = 1; i <= m; i++) {
        int l, r, k;
        read(l, r, k);
        const auto fl = find(l - 1), fr = find(r),
                   v = (w[r] - w[l - 1] + p) % p;
        if (fl != fr) {
            fa[fl] = fr;
            w[fl] = (v - k + p) % p;
        } else if (v != k) {
            break;
        }
    }
    std::cout << i - 1 << '\n';

    std::cout << std::flush;
    return 0;
}

int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    const auto fx = find(fa[x]);
    w[x] += w[fa[x]];
    w[x] %= p;
    return fa[x] = fx;
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
    }
    return x * f;
}

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}