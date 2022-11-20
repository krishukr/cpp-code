#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <queue>

using db = double;

constexpr int MAX_N = 1050;
constexpr db EPS = 1e-6;

struct {
    int v;
    int nxt;
    int _type;
    db w;
    db k;
} node[MAX_N << 2];

int head[MAX_N];
int cnt;

void create(int u, int v, int _type, db w, db k);

db dis[MAX_N];
int bfx[MAX_N];
bool vis[MAX_N];

bool check(db x);

int n, s, t;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    double l{}, r{10.0};
    read(n, s, t);
    for (int i = 1; i <= s; i++) {
        int o, a, b, k;
        read(o, a, b, k);
        create(b, a, o, 0, k);
        if (o == 1) {
            r = std::min<db>(r, k);
        }
    }
    for (int i = 1; i <= t; i++) {
        int c, x;
        read(c, x);
        create(0, c, 0, std::log2((db)(x)), 0);
        create(c, 0, 0, -std::log2((db)(x)), 0);
    }
    for (int i = 0; i <= n; i++) {
        create(n + 1, i, 0, 0, 0);
    }

    if (check(0)) {
        std::cout << -1 << '\n';
        return 0;
    }
    while (r - l > EPS) {
        const auto mid = (l + r) / 2.0;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    std::cout << std::fixed << l << '\n';

    return 0;
}

void create(int u, int v, int _type, db w, db k) {
    node[++cnt] = {v, head[u], _type, w, k};
    head[u] = cnt;
}

bool check(db x) {
    std::fill(dis, dis + n + 10, -1e9);
    std::fill(bfx, bfx + n + 10, 0);
    std::fill(vis, vis + n + 10, false);
    std::queue<int> q;

    dis[n + 1] = 0;
    bfx[n + 1]++;
    q.push(n + 1);
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        vis[p] = false;
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, _type = node[i]._type;
            auto w = node[i].w, k = node[i].k;
            if (_type == 1) {
                w = std::log2(k - x);
            } else if (_type == 2) {
                w = -std::log2(k + x);
            }

            if (dis[v] < dis[p] + w) {
                dis[v] = dis[p] + w;
                if (vis[v]) {
                    continue;
                }
                q.push(v);
                vis[v] = true;
                bfx[v]++;
                if (bfx[v] >= n) {
                    return false;
                }
            }
        }
    }
    return true;
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}