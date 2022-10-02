#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MOD = 1e9 + 7;

int trans[256];

void init();

struct Mat {
    ll a[64][64];

    Mat operator*(const Mat& x) const;

    ll* operator[](const int& x) { return a[x]; }

    const ll* operator[](const int& x) const { return a[x]; }
};

Mat quick_pow(Mat a, ll n);

template <typename T>
T read();

template <>
char read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    init();
    ll n;
    int m, k;
    read(n, m, k);

    Mat base{};
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            base[i][j] = 1;
        }
    }
    for (int i = 1; i <= k; i++) {
        char x, y;
        read(x, y);
        base[trans[x]][trans[y]] = 0;
    }

    Mat res{};
    for (int i = 1; i <= m; i++) {
        res[0][i] = 1;
    }
    res = res * quick_pow(base, n - 1);

    ll ans{};
    for (int i = 1; i <= m; i++) {
        ans += res[0][i];
        ans %= MOD;
    }
    std::cout << ans << '\n';

    return 0;
}

void init() {
    int cnt{};
    for (auto i = 'a'; i <= 'z'; i++) {
        trans[i] = ++cnt;
    }
    for (auto i = 'A'; i <= 'Z'; i++) {
        trans[i] = ++cnt;
    }
}

Mat Mat::operator*(const Mat& x) const {
    Mat r{};
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            for (int k = 0; k < 64; k++) {
                r[i][j] += a[i][k] * x[k][j] % MOD;
                r[i][j] %= MOD;
            }
        }
    }
    return r;
}

Mat quick_pow(Mat a, ll n) {
    Mat r{};
    for (int i = 0; i < 64; i++) {
        r[i][i] = 1;
    }
    while (n) {
        if (n & 1) {
            r = r * a;
        }
        a = a * a;
        n >>= 1;
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

template <>
char read() {
    char ch = getchar();
    while (!isalpha(ch)) {
        ch = getchar();
    }
    return ch;
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