#include <cstdio>
#include <iostream>

typedef long long ll;

int MOD;

struct Mat {
    ll m[4][4];

    Mat operator*(const Mat &a) {
        Mat r = {};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    r.m[i][j] += (m[i][k] * a.m[k][j]) % MOD;
                    r.m[i][j] %= MOD;
                }
            }
        }
        return r;
    }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>();
        MOD = read<int>();

        if (n <= 4) {
            switch (n) {
                case 1:
                    std::cout << 1 % MOD << '\n';
                    break;
                case 2:
                    std::cout << 5 % MOD << '\n';
                    break;
                case 3:
                    std::cout << 11 % MOD << '\n';
                    break;
                case 4:
                    std::cout << 36 % MOD << '\n';
                    break;
                default:
                    throw std::runtime_error("No Fxxking this way!!");
            }
            continue;
        }

        Mat ans = {{{36, 11, 5, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
        Mat uni = {{{1, 1, 0, 0}, {5, 0, 1, 0}, {1, 0, 0, 1}, {-1, 0, 0, 0}}};
        n -= 4;

        while (n) {
            if (n & 1) {
                ans = ans * uni;
            }
            uni = uni * uni;
            n >>= 1;
        }

        std::cout << ((ans.m[0][0] % MOD + MOD) % MOD) << '\n';
    }

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