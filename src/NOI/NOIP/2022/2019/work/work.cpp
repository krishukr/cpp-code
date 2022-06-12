#include <bits/stdc++.h>

constexpr int MAX_N = 10050;

bool f[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("work.in", "r", stdin);
    freopen("work.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m, q;
    read(n, m, q);
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        if (x == 1) {
            f[y] = true;
        }
        if (y == 1) {
            f[x] = true;
        }
    }
    while (q--) {
        int a, l;
        read(a, l);
        assert(l == 1);
        std::cout << (f[a] ? "Yes" : "No") << '\n';
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}