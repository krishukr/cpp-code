#include <cstdio>
#include <iostream>

typedef long long ll;

ll fac[20];

ll c(ll x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    fac[0] = 1;
    for (int i = 1; i <= 15; i++) {
        fac[i] = fac[i - 1] * i;
    }

    int t = read<int>();
    while (t--) {
        int n = read<int>(), m = read<int>(), k = read<int>();
        k -= 2;
        if (k < 0) {
            std::cout << "NO\n";
            continue;
        }
        n -= (k - 1);
        if (n > 14) {
            std::cout << "NO\n";
            continue;
        }

        if (c(n) <= m) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}

ll c(ll x) { return fac[x] / 4ll; }

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