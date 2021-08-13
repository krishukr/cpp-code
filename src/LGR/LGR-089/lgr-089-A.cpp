#include <cstdio>
#include <iostream>

#define int long long

const int MOD = 1e9 + 7;

template <typename T>
T read();

int quick_pow(int a, int b);

signed main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();

    while (T--) {
        int n = read<int>(), k = read<int>();

        if (k > 1) {
            int e1 = (n * (n - 1)) / 2;
            int e2 = (n * (n + 1)) / 2;
            int ans = 0;

            int s1 = k / 2;
            int s2 = k - s1;

            ans += (((e1 + e1 - s1 + 1) % MOD * s1 % MOD) % MOD) *
                   (quick_pow(2, MOD - 2)) % MOD;
            ans += (((e2 + e2 - s2 + 1) % MOD * s2 % MOD) % MOD) *
                   (quick_pow(2, MOD - 2)) % MOD;

            std::cout << ans % MOD << '\n';
        } else {
            std::cout << (n * (n + 1) / 2) % MOD << '\n';
        }
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

int quick_pow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}