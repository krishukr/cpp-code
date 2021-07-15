#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 500050;

int c[MAX_N], a[MAX_N];

template <typename T>
T read();

int main() {
    freopen("ioday1.in", "r", stdin);
    freopen("ioday1.out", "w", stdout);

    int k = read<int>();
    double n = 0, ans = 0;
    for (int i = 1; i <= k; i++) {
        c[i] = read<int>();
        n += c[i];
    }
    for (int i = 1; i <= k; i++) {
        a[i] = read<int>();
    }
    for (int i = 1; i <= k; i++) {
        ans += (double)c[i] * a[i] / n;
    }

    std::cout << std::fixed << std::setprecision(6) << ans << '\n';

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