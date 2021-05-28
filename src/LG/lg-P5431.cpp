#include <cstdio>

using namespace std;

long long MOD;
const int MAX_N = 5000000;

long long factorial[MAX_N + 10], inverse[MAX_N + 10], nums[MAX_N + 10];

long long quick_pow(long long a, long long b);

inline long long combination(long long i, long long t);

inline long long read() {
    long long x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

int main() {
    long long n, k;
    n = read(), MOD = read(), k = read();
    inverse[n + 1] = 1;
    factorial[0] = 1;
    for (long long i = 1; i <= n; i++) {
        nums[i] = read();
        factorial[i] = factorial[i - 1] * nums[i] % MOD;
    }
    inverse[n + 1] = quick_pow(factorial[n], MOD - 2);
    for (long long i = n; i >= 1; i--) {
        inverse[i] = inverse[i + 1] * nums[i] % MOD;
    }
    long long tmp = k, ans = 0;
    for (long long i = 1; i <= n; i++) {
        ans = (ans + combination(i, tmp)) % MOD;
        tmp = tmp * k % MOD;
    }
    printf("%lld\n", ans);

    return 0;
}

long long quick_pow(long long a, long long b) {
    a %= MOD;
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline long long combination(long long i, long long t) {
    return ((inverse[i + 1] * factorial[i - 1]) % MOD) * t;
}