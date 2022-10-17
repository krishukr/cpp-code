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

    int T;
    read(T);
    while (T--) {
        int n, m, a, b, c;
        read(n, m, a, b, c);
        int res = (n - 1) / a + (m - 1) / b + 1;
        for (int i = 1; i <= std::min(n, m / c); i++) {
            int s = (i - 1) * 2 + 1;
            if (n - i >= 1) {
                s += (n - i - 1) / a + 1;
            }
            if (c > b) {
                s += (c - 1) / b * i;
            }
            if (m - c * i >= 1) {
                s++;
                auto t = m - c * i - 1, u = ((c - 1) / b + 1) * b - c + 1;
                if (t / u >= i) {
                    s += i;
                    t -= u * i;
                } else {
                    s += t / u;
                    t -= t / u * u;
                }
                s += t / b;
            }
            res = std::max(res, s);
        }
        std::cout << res + 1 << '\n';
    }

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