#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 50050;

int a[MAX_N], b[MAX_N], x[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1);

    {
        int t{n};
        for (int i = n; i > 0; i--) {
            while (a[i] + k < a[t]) {
                t--;
            }
            b[i] = t - i + 1;
            x[i] = std::max(x[i + 1], b[i]);
        }
    }

    int ans{};
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, b[i] + x[i + b[i]]);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}