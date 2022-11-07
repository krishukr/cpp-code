#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;

int a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, k;
    read(n, m, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1);

    int ans{INT_MAX};
    for (int i = 2; i <= n; i++) {
        const auto d = a[i] - a[i - 1];
        if (d > ans) {
            continue;
        }
        if ((d << 1) <= k) {
            ans = std::min(ans, d);
        } else {
            for (int j = 0; j <= k; j++) {
                ans = std::min(ans, (a[i] + j) ^ (a[i - 1] + j));
            }
        }
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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