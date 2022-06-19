#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 10050;

int a[MAX_N], b[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("variance.in", "r", stdin);
    freopen("variance.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        b[i] = a[i] - a[i - 1];
    }

    ll ans{0x3f3f3f3f3f3f3f3f};

    do {
        for (int i = 1; i <= n; i++) {
            a[i] = a[i - 1] + b[i];
        }
        ll s1{}, s2{};
        for (int i = 1; i <= n; i++) {
            s1 += a[i];
            s2 += a[i] * a[i];
        }
        ans = std::min(ans, s2 * n - s1 * s1);
    } while (std::next_permutation(b + 2, b + n + 1));
    std::cout << ans << '\n';

    std::cout << std::flush;
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}