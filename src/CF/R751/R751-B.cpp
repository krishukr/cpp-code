#include <cstdio>
#include <iostream>

const int MAX_N = 2050;

int a[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>();

        for (int i = 1; i <= n; i++) {
            a[0][i] = read<int>();
        }
        for (int i = 1; i <= n; i++) {
            auto *cnt = new int[n + 1]{};
            for (int j = 1; j <= n; j++) {
                cnt[a[i - 1][j]]++;
            }
            for (int j = 1; j <= n; j++) {
                a[i][j] = cnt[a[i - 1][j]];
            }
        }

        int q = read<int>();
        while (q--) {
            int x = read<int>(), y = read<int>();
            std::cout << a[std::min(y, n)][x] << '\n';
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