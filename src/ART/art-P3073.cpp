#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

int n;
int d[MAX_N];

bool check(int x, int e);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i <= n; i++) {
        read(d[i]);
    }
    std::sort(d + 1, d + n + 1);

    int ans{INT_MAX};
    for (int i = 1; i <= n; i++) {
        int l{0}, r{800000000};
        while (l < r) {
            const auto mid = (l + r) >> 1;
            if (check(i, mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        ans = std::min(ans, l);
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    return 0;
}

bool check(int x, int e) {
    {
        int c{x}, p{e};
        for (int i = x + 1; i <= n; i++) {
            if (d[i] - d[c] > p) {
                return false;
            }
            if (p * 2 / 3 > p - (d[i] - d[c])) {
                p = p * 2 / 3;
                c = i;
            }
        }
    }
    {
        int c{x}, p{e};
        for (int i = x - 1; i >= 1; i--) {
            if (d[c] - d[i] > p) {
                return false;
            }
            if (p * 2 / 3 > p - (d[c] - d[i])) {
                p = p * 2 / 3;
                c = i;
            }
        }
    }
    return true;
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