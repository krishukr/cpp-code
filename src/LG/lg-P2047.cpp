#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 105;

ll d[MAX_N][MAX_N], c[MAX_N][MAX_N];
double a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(d, 0x3f, sizeof(d));
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        d[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        d[x][y] = d[y][x] = z;
        c[x][y] = c[y][x] = 1;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                const auto v = d[i][k] + d[k][j];
                if (d[i][j] > v) {
                    d[i][j] = v;
                    c[i][j] = c[i][k] * c[k][j];
                } else if (d[i][j] == v) {
                    c[i][j] += c[i][k] * c[k][j];
                }
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (k != i) {
                for (int j = 1; j <= n; j++) {
                    if (i != j and k != j) {
                        if (d[i][j] == d[i][k] + d[k][j]) {
                            a[k] += 1.0 * c[i][k] * c[k][j] / c[i][j];
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << std::fixed << std::setprecision(3) << a[i] << '\n';
    }

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
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