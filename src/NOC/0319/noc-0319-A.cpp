#include <cstdio>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

typedef long long ll;

constexpr int MAX_N = 1050;

struct Node {
    int x;
    int y;
    int h;
};

std::priority_queue<Node, std::vector<Node>,
                    std::function<bool(const Node&, const Node&)>>
    q([](const Node& x, const Node& y) { return x.h > y.h; });

int mp[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];

constexpr int dx[] = {0, 1, 0, -1, 0};
constexpr int dy[] = {0, 0, 1, 0, -1};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            mp[i][j] = read<int>();

            if (i == 1 or j == 1 or i == n or j == m) {
                vis[i][j] = true;
                q.push({i, j, mp[i][j]});
            }
        }
    }

    ll ans = 0;
    while (!q.empty()) {
        Node p = q.top();
        q.pop();
        for (int i = 1; i <= 4; i++) {
            int x = p.x + dx[i], y = p.y + dy[i];
            if (x < 1 or y < 1 or x > n or y > m or vis[x][y]) {
                continue;
            }

            vis[x][y] = true;
            if (p.h > mp[x][y]) {
                ans += p.h - mp[x][y];
                mp[x][y] = p.h;
            }

            q.push({x, y, mp[x][y]});
        }
    }
    std::cout << ans << '\n';

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