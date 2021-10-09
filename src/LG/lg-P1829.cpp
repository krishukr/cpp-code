#include <cstdio>
#include <iostream>

const int MAX_N = 10000050;
const int MOD = 20101009;

int pri[MAX_N], s[MAX_N], sum[MAX_N];
bool vis[MAX_N];
int cnt;

void init(int n);

int q(int a, int b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    init(std::max(n, m));
    std::cout << q(n, m) << '\n';

    return 0;
}

void init(int n) {
    s[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pri[++cnt] = i;
            s[i] = (1 + MOD - i) % MOD;
        }
        for (int j = 1; j <= cnt; j++) {
            if (i * pri[j] > n) {
                break;
            }

            vis[i * pri[j]] = true;
            if (i % pri[j]) {
                s[i * pri[j]] = 1ll * s[i] * s[pri[j]] % MOD;
            } else {
                s[i * pri[j]] = s[i];
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + (1ll * s[i] * i % MOD);
        s[i] %= MOD;
        sum[i] = sum[i - 1] + i;
        sum[i] %= MOD;
    }
}

int q(int a, int b) {
    int l, r, res = 0;
    for (l = 1; l <= std::min(a, b); l = r + 1) {
        r = std::min(a / (a / l), b / (b / l));
        res += 1ll * (s[r] - s[l - 1] + MOD) % MOD * sum[a / l] % MOD *
               sum[b / l] % MOD;
        res %= MOD;
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