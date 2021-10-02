#include <cstdio>
#include <cstdlib>
#include <iostream>

#define int long long

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        int x1 = read<int>(), y1 = read<int>(), x2 = read<int>(),
            y2 = read<int>();

        int dx = std::abs(x1 - x2), dy = std::abs(y1 - y2);
        int d = std::abs(dx - dy);
        if (d == 0) d = 1;
        std::cout << dx + dy + (d - 1) * 2 << '\n';
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