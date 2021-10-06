#include <cstdio>
#include <cstring>
#include <iostream>

const int MOD = 7459;

int a[2001];

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>();

    if (n > 1001) {
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        std::string op;
        std::cin >> op;
        if (op[0] == 'A') {
            int x = read<int>(), y = read<int>(), z = read<int>();
            for (int i = x; i <= y; i++) {
                a[i] += z;
            }
        }
        if (op[0] == 'Q') {
            int x = read<int>(), y = read<int>();
            int res = 0;
            for (int i = x; i <= y; i++) {
                res += a[i] * a[i] % MOD;
                res %= MOD;
            }
            std::cout << res << '\n';
        }
        if (op[0] == 'I') {
            int x = read<int>(), y = read<int>();
            for (int i = n; i >= x; i--) {
                std::swap(a[i + 1], a[i]);
            }
            a[x] = y;
            n++;
        }
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