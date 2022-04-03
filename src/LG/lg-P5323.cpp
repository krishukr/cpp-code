#include <cstdio>
#include <iostream>

typedef long long ll;

constexpr int MOD = 1e9 + 7;

template <typename T>
T quick_pow(T a, T b);

template <typename T>
inline T inv(T a);

template <typename T = int>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read();
    ll p = 1, q = 0, w;

    while (n--) {
        ll a = read<ll>() * inv(100ll) % MOD, b = read<ll>() * inv(100ll) % MOD;
        w = inv((1 - q * b % MOD + MOD) % MOD);
        q = b + a * a % MOD * q % MOD * w % MOD;
        p = p * a % MOD * w % MOD;
    }

    std::cout << p << '\n';

    return 0;
}

template <typename T>
inline T inv(T a) {
    return quick_pow(a, (T)(MOD - 2));
}

template <typename T = int>
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
T quick_pow(T a, T b) {
    T r = 1;
    while (b) {
        if (b & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}
