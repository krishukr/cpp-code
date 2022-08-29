#include <cstdio>
#include <cstring>
#include <iostream>

int f[(1 << 10) + 50];
int a[105][15];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            read(a[i][j]);
        }
    }

    memset(f, 0x3f, sizeof(f));
    f[(1 << n) - 1] = 0;
    for (int i = (1 << n) - 1; i >= 0; i--) {
        for (int j = 1; j <= m; j++) {
            int t{i};
            for (int k = 1; k <= n; k++) {
                if (a[j][k]) {
                    if (a[j][k] == 1 and (i & (1 << (k - 1)))) {
                        t ^= (1 << (k - 1));
                    }
                    if (a[j][k] == -1 and !(i & (1 << k - 1))) {
                        t ^= (1 << (k - 1));
                    }
                }
            }
            f[t] = std::min(f[t], f[i] + 1);
        }
    }

    std::cout << (f[0] == 0x3f3f3f3f ? -1 : f[0]) << '\n';

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