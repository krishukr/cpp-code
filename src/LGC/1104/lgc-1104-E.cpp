#include <cstdio>
#include <iostream>

bool f[4];

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
        int x, y;
        read(x, y);
        if (x == 0 and y == 0) {
            std::cout << "NO" << '\n';
            return 0;
        }

        if (x > 0 and y > 0) {
            f[0] = true;
        } else if (x > 0 and y < 0) {
            f[1] = true;
        } else if (x < 0 and y > 0) {
            f[2] = true;
        } else if (x < 0 and y < 0) {
            f[3] = true;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (!f[i]) {
            std::cout << "YES" << '\n';
            return 0;
        }
    }
    std::cout << "NO" << '\n';

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