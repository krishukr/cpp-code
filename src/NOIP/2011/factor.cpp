#include <cstdio>
#include <iostream>

#define int long long

const int MAX_N = 1500;
const int MOD = 10007;

int quick_pow(int a, int b);

template <typename T>
T read();

int tri[MAX_N][MAX_N];

signed main() {
    freopen("factor.in", "r", stdin);
    freopen("factor.out", "w", stdout);

    int a = read<int>(), b = read<int>(), k = read<int>(), n = read<int>(),
        m = read<int>();

    tri[1][1] = 1;
    for (int i = 2; i <= k + 1; i++) {
        for (int j = 1; j <= i; j++) {
            tri[i][j] = (tri[i - 1][j] + tri[i - 1][j - 1]) % MOD;
        }
    }

    std::cout << tri[k + 1][k - n + 1] * quick_pow(a, n) % MOD *
                     quick_pow(b, m) % MOD
              << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

int quick_pow(int a, int b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
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