#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

ll fib[100];

ll g(ll a, ll b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    fib[0] = fib[1] = 1;

    for (int i = 2; i <= 60; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        std::cout << g(read<ll>(), read<ll>()) << '\n';
    }

    return 0;
}

ll g(ll a, ll b) {
    if (a < b) {
        std::swap(a, b);
    }
    if (a == b) {
        return b;
    }

    return g(b, a - *(std::lower_bound(fib, fib + 60, a) - 1));
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