#include <cstdio>
#include <iostream>

using ll = long long;

struct Mat {
    ll m[2][2];
    Mat operator*(const Mat& x) const;
};

ll MOD;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll p, q, a1, a2, n;
    read(p, q, a1, a2, n, MOD);

    if (n == 1) {
        std::cout << a1 << '\n';
    } else if (n == 2) {
        std::cout << a2 << '\n';
    } else {
        Mat a{{{a2, a1}, {}}};
        Mat b{{{p, 1}, {q, 0}}};
        n -= 2;
        while (n) {
            if (n & 1) {
                a = a * b;
            }
            b = b * b;
            n >>= 1;
        }
        std::cout << a.m[0][0] << '\n';
    }

    return 0;
}

Mat Mat::operator*(const Mat& x) const {
    Mat r{};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                r.m[i][j] += m[i][k] * x.m[k][j] % MOD;
                r.m[i][j] %= MOD;
            }
        }
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