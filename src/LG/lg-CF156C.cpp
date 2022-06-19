#include <cstdio>
#include <iostream>

constexpr int MAX_N = 105;
constexpr int MAX_M = 2605;
constexpr int MOD = 1e9 + 7;

int f[MAX_N][MAX_M];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    f[0][0] = 1;
    for (int i = 1; i <= 100; i++) {
        for (int j = 1; j <= 2600; j++) {
            for (int k = 1; k <= std::min(j, 26); k++) {
                f[i][j] += f[i - 1][j - k];
                f[i][j] %= MOD;
            }
        }
    }

    int T;
    read(T);
    while (T--) {
        int s{}, n{};
        char ch = getchar();
        while (!islower(ch)) {
            ch = getchar();
        }
        while (islower(ch)) {
            s += ch - 'a' + 1;
            n++;
            ch = getchar();
        }
        std::cout << f[n][s] - 1 << '\n';
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