#include <cstdio>
#include <iomanip>
#include <iostream>
#include <queue>

const int MAX_N = 5050;
const double eps = 1e-5;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt;

double a[MAX_N], dp[MAX_N];
int vis[MAX_N], num[MAX_N];
int l, p;

void create(int u, int v, int w);

bool spfa(double x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    l = read<int>(), p = read<int>();
    for (int i = 1; i <= l; i++) {
        a[i] = read<int>();
    }

    for (int i = 1; i <= p; i++) {
        int u = read<int>(), v = read<int>(), w = read<int>();
        create(u, v, w);
    }

    double l = 0, r = 114514;

    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (spfa(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(2) << l << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

bool spfa(double x) {
    std::queue<int> q;
    for (int i = 1; i <= l; i++) {
        q.push(i);
        dp[i] = 0;
        vis[i] = num[i] = 1;
    }

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        vis[t] = 0;

        for (int i = head[t]; i; i = node[i].nxt) {
            int v = node[i].v;
            double w = node[i].w;

            if (v == t) {
                continue;
            }

            if (dp[v] > dp[t] + x * w - a[t]) {
                dp[v] = dp[t] + x * w - a[t];
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;

                    if (++num[v] >= l) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
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