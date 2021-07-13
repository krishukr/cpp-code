#include <cstdio>
#include <iostream>

const int MOD = 998244353;
const int MAX_N = 3;

long long n;

struct Matrix {
    long long map[MAX_N][MAX_N];

    Matrix operator*(const Matrix &m) const {
        Matrix r = {};
        for (int i = 0; i < MAX_N; i++) {
            for (int j = 0; j < MAX_N; j++) {
                for (int l = 0; l < MAX_N; l++) {
                    r.map[i][j] += (map[i][l] * m.map[l][j]) % MOD;
                    r.map[i][j] %= MOD;
                }
            }
        }
        return r;
    }
} a, ans;

void quick_pow(long long x);

int main() {
    freopen("peace.in", "r", stdin);
    freopen("peace.out", "w", stdout);

    std::cin >> n;
    if (n <= 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    a.map[0][0] = a.map[0][1] = a.map[1][0] = 1;
    ans.map[0][0] = ans.map[0][1] = 1;
    quick_pow(n - 1);
    std::cout << (ans.map[0][0] - 1) % MOD << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void quick_pow(long long x) {
    do {
        if (x & 1) {
            ans = ans * a;
        }
        a = a * a;
        x >>= 1;
    } while (x);
}