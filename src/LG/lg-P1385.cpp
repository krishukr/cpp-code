#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100;
constexpr int MAX_S = 26;
constexpr int MOD = 1e9 + 7;

int f[MAX_N + 50][MAX_N * MAX_S + 50];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    for (int i = 0; i < MAX_S; i++) {
        f[1][i] = 1;
    }
    for (int i = 2; i <= MAX_N; i++) {
        f[i][0] = 1;
        for (int j = 1; j <= MAX_N * MAX_S; j++) {
            for (int k = 0; k < MAX_S and j >= k; k++) {
                f[i][j] += f[i - 1][j - k];
                f[i][j] %= MOD;
            }
        }
    }

    int T;
    read(T);
    while (T--) {
        char ch = getchar();
        int c{}, s{};
        while (!islower(ch)) {
            ch = getchar();
        }
        while (islower(ch)) {
            c++;
            s += ch - 'a';
            ch = getchar();
        }
        std::cout << f[c][s] - 1 << '\n';
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