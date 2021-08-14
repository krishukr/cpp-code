#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const ll MOD = 998244353;
const int MAX_N = 200050;

int b[MAX_N];
int p = -1, cnt;

ll quick_pow(ll a, ll b);

template <typename T>
T read();

int main() {
    freopen("luna.in", "r", stdin);
    freopen("luna.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        int m = read<int>(), n = read<int>();
        memset(b, 0, sizeof(b));
        cnt = 0, p = -1;

        for (int i = 1; i <= n; i++) {
            b[i] = read<int>();
        }

        for (int i = n; i > n / 2; i--) {
            if (b[1] == b[i]) {
                p = i;
            }
        }

        bool flag = true;
        if (p != -1) {
            for (int i = 1; i <= n - p + 1; i++) {
                if (b[i] != b[i + p - 1]) {
                    std::cout << quick_pow(m, n) << '\n';
                    flag = false;
                    break;
                } else {
                    cnt++;
                }
            }

            if (flag) {
                std::cout << (quick_pow(m, n) + quick_pow(m, cnt)) % MOD
                          << '\n';
            }
        } else {
            std::cout << quick_pow(m, n) << '\n';
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ll quick_pow(ll a, ll b) {
    a %= MOD;
    ll res = 1;

    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
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