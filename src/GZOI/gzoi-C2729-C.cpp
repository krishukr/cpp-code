#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_M = 105;
constexpr int MOD = 1e9 + 7;

struct Mat {
    ll m[MAX_M][MAX_M];

    Mat(const int n);
    Mat operator*(const Mat& x) const;
} a{0}, b{0};

template <typename T, typename U>
T quick_pow(T a, U b);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

template <>
char read();

int main() {
    std::ios::sync_with_stdio(false);

    ll n, m;
    read(n, m);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            char x;
            read(x);
            a.m[i][j] = (x == '0' ? 1 : 0);
        }
    }
    for (int i = 0; i <= m; i++) {
        a.m[0][i] = a.m[i][0] = 1;
    }
    b.m[0][0] = 1;
    b = b * quick_pow(a, n);

    ll ans{};
    for (int i = 0; i <= m; i++) {
        ans += b.m[0][i];
        ans %= MOD;
    }
    std::cout << ans << '\n';

    return 0;
}

Mat::Mat(const int n) {
    for (int i = 0; i < MAX_M; i++) {
        for (int j = 0; j < MAX_M; j++) {
            this->m[i][j] = 0;
        }
    }
    for (int i = 0; i < MAX_M; i++) {
        this->m[i][i] = n;
    }
}

Mat Mat::operator*(const Mat& x) const {
    Mat r{0};
    for (int i = 0; i < MAX_M; i++) {
        for (int k = 0; k < MAX_M; k++) {
            for (int j = 0; j < MAX_M; j++) {
                r.m[i][j] += m[i][k] * x.m[k][j];
                r.m[i][j] %= MOD;
            }
        }
    }
    return r;
}

template <typename T, typename U>
T quick_pow(T a, U b) {
    T r{1};
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

template <>
char read() {
    char ch = getchar_unlocked();
    while (ch != '0' and ch != '1') {
        ch = getchar_unlocked();
    }
    return ch;
}