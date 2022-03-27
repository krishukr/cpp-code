#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;

template <typename T>
T read();

int g[MAX_N];

int main() {
    freopen("kingdom.in", "r", stdin);
    freopen("kingdom.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            g[j] += read<int>();
        }
    }

    int r = 0;
    for (int i = 1; i <= n; i++) {
        r += read<int>() == (g[i] > (m - g[i]));
    }
    std::cout << r << '\n';

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