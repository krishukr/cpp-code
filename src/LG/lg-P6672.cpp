#include <cstdio>
#include <iostream>

typedef long long ll;

const int MOD = 998244353;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += read<int>();
    }

    ll ans = 1;
    for (int i = 1; i <= sum; i++) {
        if (i == sum - n + 1) {
            continue;
        }
        ans *= i;
        ans %= MOD;
    }

    std::cout << ans << '\n';

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