#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MAX_M = 205;

struct Node {
    int s;
    int t;
    int d;
    ll w;
} node[MAX_N];

std::priority_queue<Node, std::vector<Node>,
                    std::function<bool(const Node&, const Node&)>>
    q([](const Node& a, const Node& b) {
        return (a.w == b.w ? a.d < b.d : a.w < b.w);
    });

int nxt[MAX_N];
ll cst[MAX_N];
ll f[MAX_N][MAX_M];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, k;
    read(n, m, k);
    for (int i = 1; i <= k; i++) {
        read(node[i].s, node[i].t, node[i].d, node[i].w);
    }
    std::sort(node + 1, node + k + 1,
              [](const Node& a, const Node& b) { return a.s < b.s; });

    {
        int x = 1;
        nxt[0] = 1;
        for (int i = 1; i <= n; i++) {
            while (x <= k and node[x].s <= i) {
                q.push(node[x]);
                x++;
            }
            if (q.empty()) {
                nxt[i] = i + 1;
            } else {
                const auto p = q.top();
                if (p.t < i) {
                    q.pop();
                    i--;
                    continue;
                } else {
                    nxt[i] = p.d + 1;
                    cst[i] = p.w;
                }
            }
        }
    }

    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i + 1][j + 1] = std::min(f[i + 1][j + 1], f[i][j]);
            f[nxt[i]][j] = std::min(f[nxt[i]][j], f[i][j] + cst[i]);
        }
    }

    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 0; i <= m; i++) {
        ans = std::min(ans, f[n + 1][i]);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}