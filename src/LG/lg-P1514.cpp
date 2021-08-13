#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 550;

int h[MAX_N][MAX_N], l[MAX_N][MAX_N], r[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int n, m;

void dfs(int x, int y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    memset(l, 63, sizeof(l));

    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= m; j++) {
            h[i][j] = read<int>();
            if (i == n) {
                l[i][j] = r[i][j] = j;
            }
        }
    }

    for (register int i = 1; i <= m; i++) {
        if (vis[1][i]) {
            continue;
        } else {
            dfs(1, i);
        }
    }

    bool flag = true;
    int res = 0;

    for (register int i = 1; i <= m; i++) {
        if (vis[n][i]) {
            continue;
        } else {
            flag = false;
            res++;
        }
    }

    if (flag) {
        register int ll = 1, rr = r[1][1];
        while (ll <= m) {
            for (int i = 1; i <= m; i++) {
                if (l[1][i] <= ll) {
                    rr = std::max(rr, r[1][i]);
                }
            }

            ll = rr + 1;
            res++;
        }

        std::cout << "1\n" << res << '\n';
    } else {
        std::cout << "0\n" << res << '\n';
    }

    return 0;
}

void dfs(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 1 or xx > n or yy < 1 or yy > m or h[x][y] <= h[xx][yy]) {
            continue;
        }

        if (!vis[xx][yy]) {
            dfs(xx, yy);
        }
        l[x][y] = std::min(l[x][y], l[xx][yy]);
        r[x][y] = std::max(r[x][y], r[xx][yy]);
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