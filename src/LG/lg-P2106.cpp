#include <cstdio>
#include <iostream>

typedef long long ll;

const int MOD = 1e9 + 7;

class Mat {
   public:
    ll m[10][10];

    Mat operator*(const Mat &a) const {
        Mat r = {};
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    r.m[i][j] += (m[i][k] * a.m[k][j]) % MOD;
                    r.m[i][j] %= MOD;
                }
            }
        }
        return r;
    }
};

Mat quick_pow(Mat b, ll k);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    ll k = read<ll>(), res = 0;
    if (k == 1) {
        std::cout << "10\n";
        return 0;
    }

    Mat base = {{{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                 {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                 {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                 {0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                 {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
                 {0, 0, 0, 1, 1, 1, 1, 1, 0, 0},
                 {0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
                 {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
                 {0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                 {0, 0, 0, 0, 0, 0, 0, 1, 1, 1}}},
        a = {{{0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};

    a = a * quick_pow(base, k - 1);
    for (int i = 0; i < 10; i++) {
        res += a.m[0][i];
        res %= MOD;
    }

    std::cout << res << '\n';

    return 0;
}

Mat quick_pow(Mat b, ll k) {
    Mat res = {{{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}}};

    while (k) {
        if (k & 1) {
            res = res * b;
        }
        b = b * b;
        k >>= 1;
    }
    return res;
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