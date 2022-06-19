#include <cstdio>
#include <iostream>

constexpr int MAX_N = 2050;
constexpr int MOD = 1e9 + 7;

struct ANS {
    int C[MAX_N][MAX_N];

    constexpr ANS() : C() {
        C[0][0] = 1;
        for (int i = 1; i <= 1000; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
            }
        }
    }
};

constexpr auto ans = ANS();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, k;
    read(n, m, k);
    std::cout << (1ll * ans.C[n - 1][k + k] * ans.C[m - 1][k + k] % MOD)
              << '\n';

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