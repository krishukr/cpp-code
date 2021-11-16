#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 1050;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

bool mp[MAX_N][MAX_N], vis[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

std::deque<std::pair<int, int>> q;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    int sx = read<int>(), sy = read<int>();
    q.push_back(std::make_pair(sx, sy));
    vis[sx][sy] = true;

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), y = read<int>();
        mp[x][y] = true;
    }

    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop_front();

        if (!x and !y) {
            std::cout << dp[x][y] << '\n';
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (vis[xx][yy] or xx < 0 or yy < 0 or xx > 1001 or yy > 1001) {
                continue;
            }
            vis[xx][yy] = true;
            dp[xx][yy] = dp[x][y];

            if (mp[xx][yy]) {
                q.push_back(std::make_pair(xx, yy));
                dp[xx][yy]++;
            } else {
                q.push_front(std::make_pair(xx, yy));
            }
        }
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