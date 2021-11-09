#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 500050;
const int MOD = 1e9 + 7;

ll pos[MAX_N], rng[MAX_N];
int lwl[MAX_N], rwl[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        pos[i] = read<ll>();
        rng[i] = read<ll>();

        lwl[i] = rwl[i] = i;
    }

    for (int i = 2; i <= n; i++) {
        while (lwl[i] > 1 and pos[i] - pos[lwl[i] - 1] <= rng[i]) {
            rng[i] =
                std::max(rng[i], rng[lwl[i] - 1] - (pos[i] - pos[lwl[i] - 1]));
            lwl[i] = lwl[lwl[i] - 1];
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        while (rwl[i] < n and pos[rwl[i] + 1] - pos[i] <= rng[i]) {
            lwl[i] = std::min(lwl[i], lwl[rwl[i] + 1]);
            rwl[i] = rwl[rwl[i] + 1];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 1ll * i * (rwl[i] - lwl[i] + 1) % MOD;
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