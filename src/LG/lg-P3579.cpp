#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    while (n--) {
        int a = read<int>(), b = read<int>(), c = read<int>(), d = read<int>();
        int m = std::min(b, d), ans = 0;
        for (int i = 1; i <= m; i++) {
            i = std::min(b / (b / i), d / (d / i));
            if (b / i * i >= a and d / i * i >= c) {
                ans = i;
            }
        }
        std::cout << ans << '\n';
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