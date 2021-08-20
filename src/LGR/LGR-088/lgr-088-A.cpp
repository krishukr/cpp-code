#include <cstdio>
#include <iostream>

typedef long long ll;

ll cyc[11][11];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), m = read<ll>(), k = read<ll>();
    ll x = n, y = m, z = 0, p = 0;

    if (k <= 2) {
        if (k == 1) {
            std::cout << n << '\n';
        } else {
            std::cout << m << '\n';
        }
        return 0;
    }

    cyc[x][y] = 2;

    for (int i = 3; i <= k; i++) {
        z = (x * y) % 10;
        x = y;
        y = z;

        if (cyc[x][y]) {
            p = i - cyc[x][y];
            break;
        }

        cyc[x][y] = i;
    }

    if (p < 2) {
        std::cout << z << '\n';
        return 0;
    }

    x = n, y = m;
    k %= p;
    k += (k ? 0 : p);

    for (int i = 3; i <= k; i++) {
        z = (x * y) % 10;
        x = y;
        y = z;
    }

    std::cout << z << '\n';

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