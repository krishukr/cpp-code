#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using db = double;
constexpr auto dbp = std::pow<db, int>;

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 205;
constexpr int MAX_M = MAX_N * MAX_N;
constexpr db INF = 1e8;

struct Point {
    int x;
    int y;

    double operator-(const Point& p) const {
        return std::sqrt(dbp(this->x - p.x, 2) + dbp(this->y - p.y, 2));
    }
} p[MAX_N];

struct {
    int v;
    int nxt;
    db w;
} node[MAX_M];

int head[MAX_N];
int cnt;

void create(int u, int v);

db dis[MAX_N];
bool vis[MAX_N];
int pth[MAX_N];

void dij1(int n);

void dij2(int n, int du, int dv);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

template <>
void read(Point& p) {
    read(p.x, p.y);
}

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(p[i]);
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dij1(n);
    db ans{INF};
    for (int i = n; pth[i]; i = pth[i]) {
        dij2(n, i, pth[i]);
        ans = std::min(ans, dis[n]);
    }
    std::cout << std::fixed << std::setprecision(2) << ans << '\n';

    std::cout << std::flush;
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
    node[cnt].w = p[u] - p[v];
}

void dij1(int n) {
    std::fill(dis + 2, dis + n + 1, INF);
    std::fill(vis, vis + n + 1, false);
    pq<std::pair<db, int>> q;
    q.push({0, 1});

    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;

        for (int i = head[p]; i; i = node[i].nxt) {
            const auto& v = node[i].v;
            const auto& w = node[i].w;
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                pth[v] = p;
                q.push({dis[v], v});
            }
        }
    }
}

void dij2(int n, int du, int dv) {
    std::fill(dis + 2, dis + n + 1, INF);
    std::fill(vis, vis + n + 1, false);
    pq<std::pair<db, int>> q;
    q.push({0, 1});

    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;

        for (int i = head[p]; i; i = node[i].nxt) {
            const auto& v = node[i].v;
            const auto& w = node[i].w;
            if (du == p and dv == v or du == v and dv == p) {
                continue;
            }
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                q.push({dis[v], v});
            }
        }
    }
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}