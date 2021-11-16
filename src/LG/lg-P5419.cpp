#include <cstdio>
#include <iostream>

const int MAX_N = 550;

int mp[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>() - 1, idx = 0;
    for (int i = 0; i < n; i++) {
        mp[i][n] = mp[n][i] = ++idx;
        for (int j = 1; j <= n / 2; j++) {
            int x = (i - j + n) % n, y = (i + j) % n;
            mp[x][y] = mp[y][x] = ++idx;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            std::cout << mp[i][j] << ' ';
        }
        std::cout << '\n';
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