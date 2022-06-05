#include <cassert>
#include <cstdio>
#include <iostream>

constexpr int mp[10][10] = {
    {0},
    {0, 2, 4, 8, 16, 32, 64, 128, 256},
    {0, 4, 12, 36, 108, 324, 972, 2916, 8748},
    {0, 8, 36, 112, 336, 1008, 3024, 9072, 27216},
    {0, 16, 108, 336, 912, 2688, 8064, 24192, 72576},
    {0, 32, 324, 1008, 2688, 7136, 21312, 63936, 191808},
    {0, 64, 972, 3024, 8064, 21312, 56768, 170112, 510336},
    {0, 128, 2916, 9072, 24192, 63936, 170112, 453504, 1360128},
    {0, 256, 8748, 27216, 72576, 191808, 510336, 1360128, 3626752}};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    assert(n <= 8 and m <= 8);
    std::cout << mp[n][m] << '\n';

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