#include <cmath>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    freopen("review.in", "r", stdin);
    freopen("review.out", "w", stdout);

    int n = read<int>();
    if (n == 1) {
        printf("2 1\n1 2\n");
    } else if (n == 2) {
        printf("3 3\n1 2\n2 3\n1 3\n");
    } else if (((-n) & n) == n) {
        long long x = log2(n) + 2;
        printf("%lld %lld\n", x, x * (x - 1ll) / 2ll);

        for (int i = 1; i < x; i++) {
            for (int j = i + 1; j <= x; j++) {
                printf("%d %d\n", i, j);
            }
        }
    } else {
        int x = n + 2;
        printf("%d %d\n", x, x * 2);
        for (int i = 1; i < x; i++) {
            printf("%d %d\n%d %d\n", 1, i, i, x);
        }
    }

    fclose(stdin);
    fclose(stdout);
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