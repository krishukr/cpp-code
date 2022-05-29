#include <cstdio>
#include <iostream>

constexpr int MAX_L = 24;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("power.in", "r", stdin);
    freopen("power.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    if (n & 1) {
        std::cout << -1 << '\n';
    } else {
        for (int i = MAX_L; i > 0; i--) {
            if (n >= (1 << i)) {
                n -= (1 << i);
                std::cout << (1 << i) << ' ';
            }
        }
        std::cout << '\n';
    }

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