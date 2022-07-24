#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 20050;

int l[MAX_N], r[MAX_N];
int b[MAX_N << 1], f[MAX_N << 1];

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
        read(l[i], r[i]);
        b[i] = l[i];
        b[n + i] = r[i];
    }

    std::sort(b + 1, b + n + n + 1);
    const auto cnt = std::unique(b + 1, b + n + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        l[i] = std::lower_bound(b + 1, b + cnt + 1, l[i]) - b;
        r[i] = std::lower_bound(b + 1, b + cnt + 1, r[i]) - b;
        f[l[i]]++;
        f[r[i]]--;
    }

    int ans{};
    for (int i = 1; i < cnt; i++) {
        f[i] += f[i - 1];
        if (f[i]) {
            ans += b[i + 1] - b[i];
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}