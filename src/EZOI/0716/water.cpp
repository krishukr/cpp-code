#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);

    ll m = read<ll>();
    ll h1 = read<ll>(), a1 = read<ll>(), x1 = read<ll>(), y1 = read<ll>();
    ll h2 = read<ll>(), a2 = read<ll>(), x2 = read<ll>(), y2 = read<ll>();

    ll r1 = -1, r2 = -1, l1 = -1, l2 = -1;
    for (ll i = 1; i <= 2 * m; i++) {
        h1 = (h1 * x1 + y1) % m;
        if (h1 == a1) {
            if (r1 == -1) {
                r1 = i;
            } else if (l1 == -1) {
                l1 = i - r1;
            }
        }
        h2 = (h2 * x2 + y2) % m;
        if (h2 == a2) {
            if (r2 == -1) {
                r2 = i;
            } else if (l2 == -1) {
                l2 = i - r2;
            }
        }
    }

    if (r1 == -1 or r2 == -1) {
        std::cout << "-1\n";
    } else if (r1 == r2) {
        std::cout << r1 << '\n';
    } else {
        for (ll i = 1; i <= 2 * m; i++) {
            if (r1 < r2) {
                r1 += l1;
            } else if (r1 > r2) {
                r2 += l2;
            }

            if (r1 == r2) {
                std::cout << r1 << '\n';
                return 0;
            }
        }
        std::cout << "-1\n";
    }

    fclose(stdin);
    fclose(stdout);
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