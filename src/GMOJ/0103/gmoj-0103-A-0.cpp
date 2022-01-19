#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 250;
const int MAX_M = 25;

const int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};

struct Node {
    int x;
    int y;
} a[MAX_N], b[MAX_N];

int dis[MAX_N][MAX_M][MAX_M];
int n, k, r, c;

void dfs(int x, int y, int d);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), r = read<int>(), c = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i].x = read<int>();
        a[i].y = read<int>();
        k = i;

        memset(dis[k], 0x3f, sizeof(dis[k]));
        dfs(a[i].x, a[i].y, 0);
    }

    int ans = 0x3f3f3f3f;
    for (int x1 = 1; x1 <= r; x1++) {
        for (int y1 = 1; y1 <= c; y1++) {
            for (int x2 = 1; x2 <= r; x2++) {
                for (int y2 = 1; y2 <= c; y2++) {
                    if (x1 == y1 and x2 == y2) {
                        continue;
                    }
                    for (int i = 1; i <= n; i++) {
                        b[i].x = dis[i][x1][y1];
                        b[i].y = dis[i][x2][y2];
                    }
                    std::sort(b + 1, b + n + 1,
                              [](const Node& x, const Node& y) -> bool {
                                  return x.x - x.y < y.x - y.y;
                              });

                    int res = 0;
                    for (int i = 1; i <= n / 2; i++) {
                        res += b[i].x;
                    }
                    for (int i = n / 2 + 1; i <= n; i++) {
                        res += b[i].y;
                    }
                    ans = std::min(ans, res);
                }
            }
        }
    }
    std::cout << ans << '\n';

    return 0;
}

void dfs(int x, int y, int d) {
    if (dis[k][x][y] <= d) {
        return;
    }
    dis[k][x][y] = d;

    for (int i = 0; i < 8; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if (xx < 1 or xx > r or yy < 1 or yy > c) {
            continue;
        }
        dfs(xx, yy, d + 1);
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