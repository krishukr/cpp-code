#include <cstdio>
#include <iostream>

const int MAX_N = 1050;

int siz, len;

bool m[MAX_N][MAX_N], vis[MAX_N][MAX_N];

void dfs(int x, int y);

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int n = read<int>(), resl, ress;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char ch;
            std::cin >> ch;
            if (ch == '#') {
                m[i][j] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!vis[i][j] and m[i][j]) {
                len = siz = 0;
                dfs(i, j);

                if (siz > ress) {
                    ress = siz;
                    resl = len;
                } else if (siz == ress) {
                    resl = std::min(resl, len);
                }
            }
        }
    }

    std::cout << ress << ' ' << resl;

    return 0;
}

void dfs(int x, int y) {
    vis[x][y] = true;
    siz++;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (std::abs(i) != std::abs(j)) {
                if (m[x + i][y + j] and !vis[x + i][y + j]) {
                    dfs(x + i, y + j);
                }
                if (!m[x + i][y + j]) {
                    len++;
                }
            }
        }
    }
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