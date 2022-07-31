#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;
constexpr int MOD = 10086001;
constexpr int M = 1000001;

ll frac[MAX_N];
ll s1[MAX_N], s2[MAX_N], s3[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    frac[0] = s1[0] = 1;
    for (int i = 1; i <= M; i++) {
        frac[i] = frac[i - 1] * i % MOD;
    }
    for (int i = 1; i <= M; i++) {
        s1[i] = s1[i - 1] + frac[i] % MOD;
    }
    for (int i = 1; i <= M; i++) {
        s2[i] = s2[i - 1] + frac[i] * 4 * i % MOD;
    }
    for (int i = 1; i <= M; i++) {
        s3[i] = s3[i - 1] + frac[i] * 4 * i % MOD * i % MOD;
    }

    int T;
    read(T);
    while (T--) {
        int x;
        read(x);
        const auto y = (x - 1) / 2;
        std::cout << ((s1[y] * x % MOD * x - s2[y] * x % MOD + s3[y]) % MOD +
                      MOD) %
                         MOD
                  << '\n';
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