#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

struct Seq {
    int p[10];
} a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    for (int i = 0; i < 10; i++) {
        a[0].p[i] = i;
    }
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        int x, y;
        read(x, y);
        a[i] = a[i - 1];
        std::swap(a[i].p[x], a[i].p[y]);
    }
    while (m--) {
        int x, y;
        read(x, y);
        Seq t{};
        for (int i = 0; i < 10; i++) {
            t.p[a[x - 1].p[i]] = i;
        }
        for (int i = 0; i < 10; i++) {
            std::cout << t.p[a[y].p[i]] << ' ';
        }
        std::cout << '\n';
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