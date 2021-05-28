#include <cmath>
#include <cstdio>
#include <iostream>

int map[100010][30];

inline int read();

int main() {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
        map[i][0] = read();
    }
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            map[j][i] = std::max(map[j][i - 1], map[j + (1 << (i - 1))][i - 1]);
        }
    }
    for (int i = 1; i <= m; i++) {
        int l = read(), r = read();
        int k = std::log(r - l + 1) / std::log(2);
        printf("%d\n", std::max(map[l][k], map[r - (1 << k) + 1][k]));
    }

    return 0;
}

inline int read() {
    int x = 0, f = 1;
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