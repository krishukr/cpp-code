#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

const int MAX_N = 101;

long long n, k;

struct Matrix {
    long long map[MAX_N][MAX_N];

    Matrix operator*(const Matrix &m) const {
        Matrix r = {};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int l = 0; l < n; l++) {
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
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a.map[i][j];
        }
        ans.map[i][i] = 1;
    }
    quick_pow(k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans.map[i][j] << " ";
        }
        cout << endl;
    }

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