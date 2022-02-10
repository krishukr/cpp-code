#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T quick_pow(T a, T b, T m);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        ll n = read<ll>(), m = read<ll>(), x = read<ll>(), p = read<ll>();
        ll s = 0;

        for (ll i = 1; i <= n; i++) {
            s ^= read<ll>();
        }
        for (ll i = 1; i <= m; i++) {
            s ^= read<ll>();
        }

        if (s) {
            std::cout << 0 << '\n';
            continue;
        }

        std::cout << quick_pow((x + 1) % p, (n - 1) * (m - 1), p) << '\n';
    }

    return 0;
}

template <typename T>
T quick_pow(T a, T b, T m) {
    T res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % m;
        }
        a = a * a % m;
        b >>= 1;
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