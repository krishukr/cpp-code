#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;
const int MOD = 1e9 + 7;

ll fac[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);
    // freopen("../../bin/game.in", "r", stdin);
    // freopen("../../bin/game.out", "w", stdout);

    int n = read<int>(), m = read<int>(), tot = 0;
    ll ans = 1;
    fac[0] = 1;

    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }

    for (int i = 1; i <= m; i++) {
        int e = read<int>();
        tot += e;
        ans *= fac[e];
        ans %= MOD;
    }

    ans *= fac[n - tot + m];
    ans %= MOD;

    std::cout << ans << '\n';

    // fclose(stdin);
    // fclose(stdout);
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