#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

struct A {
    int a[MAX_N];

    A();
    A operator*(const A& x) const;
    int& operator[](const int& i) { return a[i]; }
};

template <typename T, typename U>
T quick_pow(T a, U b);

int n, k;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, k);
    A b{};
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    auto a = quick_pow(b, k);
    A r{};
    for (int i = 1; i <= n; i++) {
        r[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        std::cout << r[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

A::A() {
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
}

A A::operator*(const A& x) const {
    A r{};
    for (int i = 1; i <= n; i++) {
        r.a[i] = a[x.a[i]];
    }
    return r;
}

template <typename T, typename U>
T quick_pow(T a, U b) {
    T r{};
    while (b) {
        if (b & 1) {
            r = r * a;
        }
        a = a * a;
        b >>= 1;
    }
    return r;
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