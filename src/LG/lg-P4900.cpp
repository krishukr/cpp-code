#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000050;
const ll MOD = 998244353;

ll f1[MAX_N], f2[MAX_N];

void init(int n);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    init(1000000);
    int T = read<int>();

    while (T--) {
        int a = read<int>(), b = read<int>();
        std::cout << ((f1[b] - f1[a - 1] + MOD) % MOD -
                      (f2[b] - f2[a - 1] + MOD) % MOD + MOD) %
                         MOD
                  << '\n';
    }

    return 0;
}

void init(int n) {
    f1[1] = 1;
    for (int i = 2; i <= n; i++) {
        f1[i] = (MOD - MOD / i) * f1[MOD % i] % MOD;
    }
    for (int i = 2; i <= n; i++) {
        f1[i] += f1[i - 1];
        f1[i] %= MOD;
    }
    for (int i = 2; i <= n; i++) {
        f1[i] *= i;
        f1[i] %= MOD;
    }
    for (int i = 2; i <= n; i++) {
        f1[i] += f1[i - 1];
        f1[i] %= MOD;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            f2[j]++;
        }
    }
    for (int i = 2; i <= n; i++) {
        f2[i] += f2[i - 1];
        f2[i] %= MOD;
    }
    for (int i = 2; i <= n; i++) {
        f2[i] += f2[i - 1];
        f2[i] %= MOD;
    }
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