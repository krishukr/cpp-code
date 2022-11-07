#include <climits>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

int s[MAX_N], c[MAX_N];
int f[1 << 17];

int check(int x, int b);

int k, n;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(k, n);
    for (int i = 1; i <= k; i++) {
        read(c[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(s[i]);
        s[i] += s[i - 1];
    }
    for (int i = 0; i <= (1 << k) - 1; i++) {
        for (int j = 0; j < k; j++) {
            if (!(i & (1 << j)) or f[i] >= n) {
                continue;
            }
            f[i] = std::max(f[i],
                            f[i ^ (1 << j)] + check(f[i ^ (1 << j)], c[j + 1]));
        }
    }

    int ans{-1};
    for (int i = 0; i <= (1 << k) - 1; i++) {
        if (f[i] != n) {
            continue;
        }
        int s{};
        for (int j = 0; j < k; j++) {
            if (i & (1 << j)) {
                continue;
            }
            s += c[j + 1];
        }
        ans = std::max(ans, s);
    }
    std::cout << ans << '\n';

    return 0;
}

int check(int x, int b) {
    int l{x + 1}, r{n}, a{};
    while (l <= r) {
        const auto mid = (l + r) >> 1;
        if (s[mid] - s[x] <= b) {
            l = mid + 1;
            a = mid - x;
        } else {
            r = mid - 1;
        }
    }
    return a;
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