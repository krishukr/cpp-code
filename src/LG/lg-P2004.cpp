#include <climits>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;

int s[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, c;
    read(n, m, c);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(s[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];
        }
    }

    int a{INT_MIN}, ax{}, ay{};
    for (int i = c; i <= n; i++) {
        for (int j = c; j <= m; j++) {
            const auto t =
                s[i][j] - s[i - c][j] - s[i][j - c] + s[i - c][j - c];
            if (a < t) {
                a = t;
                ax = i;
                ay = j;
            }
        }
    }
    std::cout << ax - c + 1 << ' ' << ay - c + 1 << '\n';

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