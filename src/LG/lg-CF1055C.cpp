#include <algorithm>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int la, ra, ta, lb, rb, tb, a{};
    read(la, ra, ta, lb, rb, tb);
    const auto p = std::__gcd(ta, tb);
    const auto d = ((lb - la) % p + p) % p;
    a = std::max(a, std::min(ra - la - d + 1, rb - lb + 1));
    a = std::max(a, std::min(rb - lb + d - p + 1, ra - la + 1));
    std::cout << a << '\n';

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