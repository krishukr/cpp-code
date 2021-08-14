#include <iostream>

const int MAX_N = 2010;

int tri[MAX_N][MAX_N], sum[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);
    // freopen("problem.in", "r", stdin);
    // freopen("problem.out", "w", stdout);

    int T = read<int>(), p = read<int>();

    tri[1][1] = 1;
    for (int i = 0; i <= 2000; i++) {
        tri[i][0] = 1;
    }
    for (int i = 2; i <= 2000; i++) {
        for (int j = 1; j <= i; j++) {
            tri[i][j] = (tri[i - 1][j] + tri[i - 1][j - 1]) % p;
        }
    }

    for (int i = 2; i <= 2000; i++) {
        for (int j = 1; j <= i; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            if (tri[i][j] == 0) {
                sum[i][j] += 1;
            }
        }
        sum[i][i + 1] = sum[i][i];
    }

    while (T--) {
        int n = read<int>(), m = read<int>();

        if (m > n) {
            m = n;
        }
        std::cout << sum[n][m] << "\n";
    }

    fclose(stdin);
    fclose(stdout);
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