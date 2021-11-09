#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    int T = read<int>();
    while (T--) {
        ll x = read<ll>(), n = read<ll>();
        for (ll i = n - (n % 4) + 1; i <= n; i++) {
            if (x & 1) {
                x += i;
            } else {
                x -= i;
            }
        }
        std::cout << x << '\n';
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