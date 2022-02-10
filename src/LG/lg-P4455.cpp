#include <cstdio>
#include <iostream>

typedef long long ll;

const int MOD = 1e4 + 7;

template <typename T>
T read();

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

int main() {
    std::ios::sync_with_stdio(false);

    Gauss<ll, 255> g;

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        x--;
        y--;
        g[x][x]++;
        g[y][x]--;
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