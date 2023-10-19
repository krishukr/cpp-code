#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;

int a[MAX_N];
int n, m;

bool check(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    int l = 0, r = 2e9;
    while (l + 1 < r) {
        const auto mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    std::cout << l << '\n';

    std::cout << std::flush;
    return 0;
}

bool check(int x) {
    ll res{};
    for (int i = 1; i <= n; i++) {
        res += std::max(0, a[i] - x);
    }
    return res >= m;
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