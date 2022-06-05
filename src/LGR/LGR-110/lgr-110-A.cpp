#include <cmath>
#include <cstdio>
#include <iostream>

using ll = long long;

struct Mat {
    int map[2][2];
    Mat operator*(const Mat& m) const {
        Mat r{};
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    r.map[i][j] += (map[i][k] * m.map[k][j]) % 9;
                    r.map[i][j] %= 9;
                }
            }
        }
        return r;
    }
} a, b;

int get(int n);

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
        ll n;
        read(n);
        std::cout << (get(n + 2) - 1 + 9) % 9 << '\n';
    }

    return 0;
}

int get(int n) {
    a.map[0][0] = a.map[1][1] = 1;
    a.map[0][1] = a.map[1][0] = 0;
    b.map[0][0] = b.map[0][1] = b.map[1][0] = 1;
    b.map[1][1] = 0;
    while (n) {
        if (n & 1) {
            a = a * b;
        }
        b = b * b;
        n >>= 1;
    }
    return a.map[0][1];
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