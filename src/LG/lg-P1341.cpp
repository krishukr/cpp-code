#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 64;

bool g[MAX_N][MAX_N];
int d[MAX_N];
std::vector<int> ans;

void dfs(int x);

template <typename T>
T read();

template <>
char read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, r{255};
    read(n);
    for (int i = 1; i <= n; i++) {
        char x, y;
        read(x, y);
        g[x][y] = g[y][x] = true;
        d[y]++;
        d[x]++;
        r = std::min<int>({r, x, y});
    }

    std::vector<int> e;
    for (int i = 0; i < 64; i++) {
        if (d[i] & 1) {
            e.push_back(i);
        }
    }
    if (e.size() == 0) {
        dfs(r);
    } else if (e.size() == 2) {
        dfs(*e.begin());
    } else {
        std::cout << "No Solution" << '\n';
        return 0;
    }

    std::reverse(ans.begin(), ans.end());
    for (const auto& i : ans) {
        std::cout << (char)(i + 'A');
    }
    std::cout << '\n';

    return 0;
}

void dfs(int x) {
    for (int i = 0; i < 64; i++) {
        if (g[x][i]) {
            g[x][i] = g[i][x] = false;
            dfs(i);
        }
    }
    ans.push_back(x);
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

template <>
char read() {
    char ch = getchar_unlocked();
    while (!isalpha(ch)) {
        ch = getchar_unlocked();
    }
    return ch - 'A';
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