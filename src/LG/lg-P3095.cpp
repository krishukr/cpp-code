#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), q = read<int>();
    auto* a = new int[n + 10];

    for (int i = 1; i <= m; i++) {
        int x = read<int>();
        a[x] = i;
    }

    while (q--) {
        int x = read<int>();
        int r = n - x + 1;

        for (int i = r; i > 0; i--) {
            if (r <= i + m - 1 and i + m - 1 <= n) {
                r = i + a[r - i + 1] - 1;
            }
        }
        std::cout << r << '\n';
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