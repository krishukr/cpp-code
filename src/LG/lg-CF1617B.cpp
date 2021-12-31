#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>();
        if (n & 1) {
            int h = (n - 1) / 2;
            if (h & 1) {
                printf("%d %d 1\n", h - 2, h + 2);
            } else {
                printf("%d %d 1\n", h - 1, h + 1);
            }
        } else {
            printf("%d %d 1\n", n / 2 - 1, n / 2);
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