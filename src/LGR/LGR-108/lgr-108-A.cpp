#include <cmath>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;

struct Q {
    int op;
    int x;
    int y;
} q[MAX_N];

int a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int k, x, y;
        read(k, x, y);
        q[i] = {k, x, y};
    }

    for (int i = m; i >= 1; i--) {
        if (q[i].op == 1) {
            if (q[i].x == q[i].y) {
                a[q[i].x] /= 2;
            } else {
                a[q[i].x] -= a[q[i].y];
            }
        } else {
            if (q[i].x == q[i].y) {
                a[q[i].x] = std::sqrt(a[q[i].x]);
            } else {
                a[q[i].x] /= a[q[i].y];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << ' ';
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