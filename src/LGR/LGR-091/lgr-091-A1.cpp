#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int t = read<int>(), T = read<int>();

    while (T--) {
        int n = read<int>(), m = read<int>(), k = 0, p = 101;
        if (m == 1) {
            std::cout << "NO\n";
            continue;
        }
        std::cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << (((p - 1) - j) + k) % p << ' ';
            }
            k++;
            if (k == p) {
                p--;
                k = 0;
            }
            std::cout << '\n';
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