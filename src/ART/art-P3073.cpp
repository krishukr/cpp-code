#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iostream>

using db = double;

constexpr int MAX_N = 1000050;
constexpr int INF = 5e8;

int a[MAX_N];
int f[MAX_N], g[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1);

    {
        int p{1};
        for (int i = 2; i <= n; i++) {
            f[i] = INF;
            while (a[i] - a[p + 1] >= (int)((1.0 * f[p + 1] * 3 + 1.0) / 2)) {
                p++;
            }
            f[i] = std::min((int)((1.0 * f[p + 1] * 3 + 1.0) / 2), a[i] - a[p]);
        }
    }
    {
        int p{n};
        for (int i = n - 1; i >= 1; i--) {
            g[i] = INF;
            while (a[p - 1] - a[i] >= (int)((1.0 * g[p - 1] * 3 + 1.0) / 2)) {
                p--;
            }
            g[i] = std::min((int)((1.0 * g[p - 1] * 3 + 1.0) / 2), a[p] - a[i]);
        }
    }

    int ans{INF};
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, std::max(f[i], g[i]));
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    return 0;
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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