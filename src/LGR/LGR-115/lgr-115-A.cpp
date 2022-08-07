#include <cstdio>
#include <iostream>

constexpr int MAX_N = 55;
constexpr int MAX_M = 1050;

int mp[MAX_N][MAX_N];
std::pair<int, int> p[MAX_M];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, x, y;
    read(n, m, x, y);
    // m++;
    p[1] = {x, y};
    for (int i = 2; i <= m; i++) {
        char op = getchar();
        while (op != 'N' and op != 'S' and op != 'W' and op != 'E') {
            op = getchar();
        }
        if (op == 'N') {
            y++;
        }
        if (op == 'S') {
            y--;
        }
        if (op == 'W') {
            x--;
        }
        if (op == 'E') {
            x++;
        }
        p[i] = {x, y};
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int t{};
            for (int k = 1; k <= m; k++) {
                const auto &x = p[k].first, &y = p[k].second;
                if (x == j and y == i) {
                    t = 0;
                } else {
                    t++;
                    mp[i][j] += t;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cout << mp[n - i + 1][j] << ' ';
        }
        std::cout << '\n';
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}