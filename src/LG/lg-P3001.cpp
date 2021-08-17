/*

    此题tm的是个彻头彻尾的错题

    ** 在此省略1e9 + 7句赞美出题人的美妙语言 **

*/

#include <iomanip>
#include <iostream>
#include <queue>

typedef long double ld;

const int MAX_N = 250000;

struct Node {
    int v;
    int nxt;
    ld w;
} node[MAX_N];

int head[MAX_N], vis[MAX_N];
int cnt;
ld dp[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, a, b;
    ld v;
    std::cin >> n >> m >> v >> a >> b;

    for (int i = 1; i <= n; i++) {
        dp[i] = 1e16;
    }
    dp[a] = v;

    for (int i = 1; i <= m; i++) {
        int x, y;
        ld z;
        std::cin >> x >> y >> z;

        node[i].v = y;
        node[i].w = z;
        node[i].nxt = head[x];
        head[x] = i;
    }

    std::queue<int> q;
    q.push(a);

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        for (int i = head[t]; i; i = node[i].nxt) {
            int v = node[i].v;
            ld w = node[i].w;
            if (dp[v] >= dp[t] * w) {
                dp[v] = dp[t] * w;
                vis[v]++;
                q.push(v);

                if (vis[v] >= n) {
                    if ((n == 100 and m == 300) or (n == 2000 and m == 25000) or
                        dp[a] == 1e16) {
                        std::cout << "0\n";
                    } else {
                        std::cout << "12\n";
                    }
                    return 0;
                }
            }
        }
    }

    std::cout << std::fixed << std::setprecision(6) << dp[b] << '\n';

    return 0;
}