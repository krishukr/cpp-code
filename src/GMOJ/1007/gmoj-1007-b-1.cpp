#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

int a[MAX_N], p[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        if (!x) {
            x = -1;
        }
        a[i] = a[i - 1] + x;
    }

    for (int i = 1; i <= n; i++) {
        if (!a[i]) {
            ans = std::max(ans, i);
            continue;
        }
        if (p[a[i]] and ans < i - p[a[i]]) {
            ans = i - p[a[i]];
        }
        if (!p[a[i]]) {
            p[a[i]] = i;
        }
    }

    std::cout << ans << '\n';

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