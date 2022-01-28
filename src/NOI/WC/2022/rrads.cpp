#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 500050;

int a[MAX_N], b[MAX_N], p[MAX_N];

template <typename T>
T read();

int main() {
    freopen("rrads.in", "r", stdin);
    freopen("rrads.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        p[a[i]] = i;
    }

    for (int i = 1; i <= m; i++) {
        int l = read<int>(), r = read<int>();
        for (int j = l; j <= r; j++) {
            b[j] = a[j];
        }
        std::sort(b + l, b + r + 1);

        int ans = 0;
        for (int j = l; j < r; j++) {
            ans += std::abs(p[b[j]] - p[b[j + 1]]);
        }
        std::cout << ans << '\n';
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