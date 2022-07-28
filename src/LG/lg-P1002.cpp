#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 35;
constexpr int dx[] = {0, 1, 1, 2, 2, -1, -1, -2, -2};
constexpr int dy[] = {0, 2, -2, 1, -1, 2, -2, 1, -1};

ll f[MAX_N][MAX_N];
bool mp[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int bx, by, hx, hy;
    read(bx, by, hx, hy);
    mp[hx][hy] = true;
    for (int i = 1; i <= 8; i++) {
        const auto xx = hx + dx[i], yy = hy + dy[i];
        if (xx >= 0 and yy >= 0) {
            mp[xx][yy] = true;
        }
    }

    for (int i = 0; i <= bx; i++) {
        for (int j = 0; j <= by; j++) {
            if (mp[i][j]) {
                continue;
            }
            if (i == 0 and j == 0) {
                f[i][j] = 1;
            } else if (i == 0) {
                f[i][j] = f[i][j - 1];
            } else if (j == 0) {
                f[i][j] = f[i - 1][j];
            } else {
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
    }
    std::cout << f[bx][by] << '\n';

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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}