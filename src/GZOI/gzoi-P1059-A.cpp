#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 15;

class Solution {
    int d[MAX_N][MAX_N];
    int f[MAX_N][1 << 11];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve(int n);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    while (true) {
        int n;
        read(n);
        if (n) {
            std::unique_ptr<Solution> solution(new Solution());
            solution->solve(n);
        } else {
            break;
        }
    }

    return 0;
}

void Solution::solve(int n) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            read(d[i][j]);
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }

    for (int k = 0; k <= (1 << n) - 1; k++) {
        for (int i = 1; i <= n; i++) {
            if (!(k & (1 << (i - 1)))) {
                continue;
            }
            if (k == (1 << (i - 1))) {
                f[i][k] = d[0][i];
            } else {
                f[i][k] = INT_MAX;
                for (int j = 1; j <= n; j++) {
                    if (!(k & (1 << (j - 1))) or i == j) {
                        continue;
                    }
                    f[i][k] =
                        std::min(f[i][k], f[j][k ^ (1 << (i - 1))] + d[j][i]);
                }
            }
        }
    }

    int res{INT_MAX};
    for (int i = 1; i <= n; i++) {
        res = std::min(res, f[i][(1 << n) - 1] + d[i][0]);
    }
    std::cout << res << '\n';
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