#include <algorithm>
#include <cstdio>
#include <iostream>
#include <random>

using ull = unsigned long long;

constexpr int MAX_N = 300050;

std::mt19937_64 mrand(1145142007);

int a[MAX_N];
ull r[MAX_N], s[MAX_N], p[MAX_N];

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
        r[i] = mrand();
        s[i] = s[i - 1] ^ r[i];
    }
    for (int i = 1; i <= n; i++) {
        p[i] = p[i - 1] ^ r[a[i]];
    }

    int ans{};
    for (int i = 1, j = 1; i <= n; i++) {
        if (a[i] == 1) {
            j = 1;
            ans++;
        } else {
            j = std::max(j, a[i]);
            if (i < j) {
                continue;
            }
            if ((p[i] ^ p[i - j]) == s[j]) {
                ans++;
            }
        }
    }

    std::reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = p[i - 1] ^ r[a[i]];
    }
    for (int i = 1, j = 1; i <= n; i++) {
        if (a[i] == 1) {
            j = 1;
        } else {
            j = std::max(j, a[i]);
            if (i < j) {
                continue;
            }
            if ((p[i] ^ p[i - j]) == s[j]) {
                ans++;
            }
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