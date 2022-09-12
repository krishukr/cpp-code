#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;

int a[MAX_N], b[MAX_N];

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
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }

    int au{}, ad{1};
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) {
            au++;
        }
    }
    std::reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) {
            ad++;
        }
    }
    std::cout << std::min(au, ad) << '\n';

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