#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;

int mp[MAX_N][MAX_N];
int h[MAX_N][MAX_N], l[MAX_N][MAX_N], r[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch = getchar();
            while (ch != 'R' and ch != 'F') {
                ch = getchar();
            }
            if (ch == 'F') {
                mp[i][j] = true;
                h[i][j] = h[i - 1][j] + 1;
                l[i][j] = l[i][j - 1];
            } else {
                l[i][j] = j;
            }
        }
        r[i][m + 1] = m + 1;
        for (int j = m; j > 0; j--) {
            r[i][j] = mp[i][j] ? r[i][j + 1] : j;
        }
    }

    int ans{};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (h[i][j] != 1) {
                l[i][j] = std::max(l[i][j], l[i - 1][j]);
                r[i][j] = std::min(r[i][j], r[i - 1][j]);
            }
            ans = std::max(ans, (r[i][j] - l[i][j] - 1) * h[i][j]);
        }
    }
    std::cout << ans * 3 << '\n';

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