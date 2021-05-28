#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

struct Matrix {
    long long map[4][4];

    Matrix operator*(const Matrix& m) const {
        Matrix r = {};
        for (long long i = 0; i < 3; i++) {
            for (long long j = 0; j < 3; j++) {
                for (long long k = 0; k < 3; k++) {
                    r.map[i][j] += (map[i][k] * m.map[k][j]) % MOD;
                    r.map[i][j] %= MOD;
                }
            }
        }
        return r;
    }
} ans, base;

void init();

void quick_pow(long long n);

int main() {
    long long t;
    cin >> t;
    for (long long i = 0; i < t; i++) {
        long long n;
        cin >> n;
        if (n <= 3) {
            cout << 1 << endl;
            continue;
        }
        init();
        quick_pow(n - 1);
        cout << ans.map[0][0] << endl;
    }

    return 0;
}

void init() {
    memset(ans.map, 0, sizeof(ans.map));
    for (long long i = 0; i < 3; i++) {
        ans.map[i][i] = 1;
    }
    memset(base.map, 0, sizeof(base.map));
    base.map[0][0] = base.map[0][2] = base.map[1][0] = base.map[2][1] = 1;
}

void quick_pow(long long n) {
    while (n) {
        if (n & 1) {
            ans = ans * base;
        }
        base = base * base;
        n >>= 1;
    }
}