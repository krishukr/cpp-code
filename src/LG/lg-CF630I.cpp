#include <cmath>
#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    if (n == 1) {
        std::cout << 0 << '\n';
    } else if (n == 2) {
        std::cout << 4 << '\n';
    } else {
        ll res = 2ll * 4ll * 3ll * std::pow(4ll, n - 3) +
                 4ll * (n - 3) * 3ll * 3ll * std::pow(4ll, n - 4);
        std::cout << res << '\n';
    }

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