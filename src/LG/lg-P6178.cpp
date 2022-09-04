#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MOD = 1e9 + 7;

template <typename T, T N>
class Gauss {
   protected:
    T quick_pow(T a, T b);

   public:
    Gauss() = default;
    ~Gauss() = default;

    T m[N][N + 1];

    T gauss(int);

    T* operator[](const int& i) { return m[i]; }
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    Gauss<ll, 320> g;

    int n, m, t;
    read(n, m, t);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        x--;
        y--;
        if (t) {
            (g[y][y] += z) %= MOD;
            (g[y][x] += MOD - z) %= MOD;
        } else {
            (g[y][y] += z) %= MOD;
            (g[x][x] += z) %= MOD;
            (g[y][x] += MOD - z) %= MOD;
            (g[x][y] += MOD - z) %= MOD;
        }
    }

    std::cout << g.gauss(n) << '\n';

    return 0;
}

template <typename T, T N>
T Gauss<T, N>::quick_pow(T a, T b) {
    T res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

template <typename T, T N>
T Gauss<T, N>::gauss(int n) {
    T res = 1;
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (m[j][i]) {
                std::swap(m[i], m[j]);
                if (i != j) {
                    res = MOD - res;
                }
                break;
            }
        }

        auto inv = quick_pow(m[i][i], MOD - 2);
        for (int j = i + 1; j < n; j++) {
            if (m[j][i]) {
                for (int k = n - 1; k >= i; k--) {
                    m[j][k] -= m[i][k] * inv % MOD * m[j][i] % MOD;
                    m[j][k] += MOD;
                    m[j][k] %= MOD;
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        res *= m[i][i] % MOD;
        res %= MOD;
    }
    return res;
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