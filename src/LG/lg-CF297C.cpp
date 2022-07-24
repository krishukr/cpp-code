#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

std::pair<int, int> s[MAX_N], a[MAX_N], b[MAX_N];

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
    const auto k = n % 3 ? n / 3 + 1 : n / 3;
    for (int i = 1; i <= n; i++) {
        s[i] = {read<int>(), i};
    }
    std::sort(s + 1, s + n + 1);

    for (int i = 1; i <= n; i++) {
        a[i] = b[i] = s[i];
    }
    for (int i = 1; i <= k; i++) {
        a[i].first = i - 1;
        b[i].first = s[i].first - a[i].first;
    }
    for (int i = k + 1; i <= n - k; i++) {
        b[i].first = i - 1;
        a[i].first = s[i].first - b[i].first;
    }
    for (int i = n - k + 1; i <= n; i++) {
        b[i].first = n - i;
        a[i].first = s[i].first - b[i].first;
    }
    std::sort(a + 1, a + n + 1,
              [](const auto& x, const auto& y) { return x.second < y.second; });
    std::sort(b + 1, b + n + 1,
              [](const auto& x, const auto& y) { return x.second < y.second; });

    std::cout << "YES" << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << a[i].first << ' ';
    }
    std::cout << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << b[i].first << ' ';
    }
    std::cout << '\n';

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