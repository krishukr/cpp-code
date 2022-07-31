#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 205;

int t[MAX_N];
int f[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(t, 0x3f, sizeof(t));
    memset(f, 0x3f, sizeof(f));
    int n, m;
    read(n, m);
    for (int i = 0; i < n; i++) {
        f[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        read(t[i]);
    }
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        f[x][y] = f[y][x] = z;
    }

    int q, k{};
    read(q);
    while (q--) {
        int x, y, z;
        read(x, y, z);
        for (; t[k] <= z; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
                }
            }
        }
        if (f[x][y] == 0x3f3f3f3f or t[x] > z or t[y] > z) {
            std::cout << "-1\n";
        } else {
            std::cout << f[x][y] << '\n';
        }
    }

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