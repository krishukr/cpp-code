#include <cstdio>
#include <iostream>

void dfs(int x1, int y1, int x2, int y2, int n);

template <typename T>
void outL(const T& t);

template <typename T, typename... Args>
void outL(const T& t, const Args&... rest);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int k, x, y;
    read(k, x, y);
    dfs(1, 1, x, y, k);

    return 0;
}

void dfs(int x1, int y1, int x2, int y2, int n) {
    if (!n) {
        return;
    }
    const auto d = n >= 2 ? 2 << (n - 2) : 1;
    const auto mx = x1 + d, my = y1 + d;
    if (x2 < mx and y2 < my) {
        outL(mx, my, 1);
        dfs(x1, y1, x2, y2, n - 1);
        dfs(x1, my, mx - 1, my, n - 1);
        dfs(mx, y1, mx, my - 1, n - 1);
        dfs(mx, my, mx, my, n - 1);
    } else if (x2 < mx and my <= y2) {
        outL(mx, my - 1, 2);
        dfs(x1, y1, mx - 1, my - 1, n - 1);
        dfs(x1, my, x2, y2, n - 1);
        dfs(mx, y1, mx, my - 1, n - 1);
        dfs(mx, my, mx, my, n - 1);
    } else if (mx <= x2 and y2 < my) {
        outL(mx - 1, my, 3);
        dfs(x1, y1, mx - 1, my - 1, n - 1);
        dfs(x1, my, mx - 1, my, n - 1);
        dfs(mx, y1, x2, y2, n - 1);
        dfs(mx, my, mx, my, n - 1);
    } else if (mx <= x2 and my <= y2) {
        outL(mx - 1, my - 1, 4);
        dfs(x1, y1, mx - 1, my - 1, n - 1);
        dfs(x1, my, mx - 1, my, n - 1);
        dfs(mx, y1, mx, my - 1, n - 1);
        dfs(mx, my, x2, y2, n - 1);
    }
}

template <typename T>
void outL(const T& t) {
    std::cout << t << '\n';
}

template <typename T, typename... Args>
void outL(const T& t, const Args&... rest) {
    std::cout << t << ' ';
    outL(rest...);
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