#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MOD = 998244353;
constexpr int MAX_N = 2000050;
constexpr int MAX_M = 105;

int fra[MAX_N], inv[MAX_N];

template <typename T>
T quick_pow(T a, T b);

int combination(int a, int b);

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

class Solution {
   private:
    int a[MAX_M], b[MAX_M];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    {
        constexpr int k = 2000000;
        fra[0] = 1;
        for (int i = 1; i <= k; i++) {
            fra[i] = 1ll * fra[i - 1] * i % MOD;
        }
        inv[k] = (int)quick_pow<ll>(fra[k], MOD - 2);
        for (int i = k - 1; i >= 0; i--) {
            inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
        }
    }

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    return 0;
}

template <typename T>
T quick_pow(T a, T b) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

int combination(int a, int b) {
    if (a < b) {
        return 0;
    } else {
        return 1ll * fra[a] * inv[b] % MOD * inv[a - b] % MOD;
    }
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

void Solution::solve() {
    Gauss<ll, MAX_M> g;
    int n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        read(a[i], b[i]);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            g[i][j] = combination(b[j] - a[i] + n - 1, n - 1);
        }
    }
    std::cout << g.gauss(m + 1) << '\n';
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