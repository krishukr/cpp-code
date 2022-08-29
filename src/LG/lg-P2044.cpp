#include <cstdio>
#include <iostream>

using ll = long long;

ll m, a, c, x0, n, g;

struct Mat {
    ll m[2][2];
    Mat operator*(const Mat& x) const;
};

template <typename T>
T slow_multi(T a, T b, T p);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(m, a, c, x0, n, g);
    Mat a{{{x0, c}, {}}};
    Mat b{{{::a, 0}, {1, 1}}};
    while (n) {
        if (n & 1) {
            a = a * b;
        }
        b = b * b;
        n >>= 1;
    }
    std::cout << a.m[0][0] % g << '\n';

    return 0;
}

Mat Mat::operator*(const Mat& x) const {
    Mat r{};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                r.m[i][j] += slow_multi(m[i][k], x.m[k][j], ::m);
                r.m[i][j] %= ::m;
            }
        }
    }
    return r;
}

template <typename T>
T slow_multi(T a, T b, T p) {
    T r{};
    while (b) {
        if (b & 1) {
            r = r + a % p;
        }
        a = a + a % p;
        b >>= 1;
    }
    return r;
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