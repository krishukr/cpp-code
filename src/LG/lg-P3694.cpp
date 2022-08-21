#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 100050;
constexpr int MAX_M = 21;

int a[MAX_N], c[MAX_N];
int s[MAX_M][MAX_N];
int f[1 << MAX_M];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    memset(f, 0x3f, sizeof(f));
    f[0] = 0;

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        c[a[i]]++;
        for (int j = 1; j <= m; j++) {
            s[j][i] = s[j][i - 1];
        }
        s[a[i]][i]++;
    }

    for (int i = 1; i <= (1 << m) - 1; i++) {
        int r{};
        for (int j = 0; j < m; j++) {
            if ((i >> j) & 1) {
                r += c[j + 1];
            }
        }
        for (int j = 0; j < m; j++) {
            if ((i >> j) & 1) {
                const auto l = r - c[j + 1] + 1;
                f[i] = std::min(f[i], f[i - (1 << j)] + (r - l + 1) -
                                          (s[j + 1][r] - s[j + 1][l - 1]));
            }
        }
    }
    std::cout << f[(1 << m) - 1] << '\n';

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