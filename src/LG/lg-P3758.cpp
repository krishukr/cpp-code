#include <cstdio>
#include <iostream>

const int MAX_N = 105;
const int MOD = 2017;

int n, m, res;

struct Matrix {
    int map[MAX_N][MAX_N];

    Matrix operator*(const Matrix &m) const {
        Matrix res = {};

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    res.map[i][j] += (map[i][k] * m.map[k][j]) % MOD;
                    res.map[i][j] %= MOD;
                }
            }
        }
        return res;
    }
} ans, a;

void quick_pow(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    n++;
    for (int i = 1; i <= m; i++) {
        int u = read<int>(), v = read<int>();
        a.map[u][v] = a.map[v][u] = 1;
    }
    for (int i = 1; i <= n; i++) {
        a.map[i][n] = a.map[i][i] = ans.map[i][i] = 1;
    }

    int k = read<int>();
    quick_pow(k);

    for (int i = 1; i <= n; i++) {
        res += ans.map[1][i];
        res %= MOD;
    }
    std::cout << res << '\n';

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

void quick_pow(int x) {
    do {
        if (x & 1) {
            ans = ans * a;
        }
        a = a * a;
        x >>= 1;
    } while (x);
}