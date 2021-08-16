#include <cstdio>
#include <iostream>

const int MAX_N = 105;

int m[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    int x = 0, y = n / 2;
    for (int i = 1; i <= n * n; i++) {
        m[x][y] = i;
        x--;
        y++;

        if (x < 0 and y > n - 1) {
            x += 2;
            y -= 1;
        } else if (x < 0) {
            x += n;
        } else if (y > n - 1) {
            y -= n;
        } else if (m[x][y]) {
            x += 2;
            y -= 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << m[i][j] << ' ';
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