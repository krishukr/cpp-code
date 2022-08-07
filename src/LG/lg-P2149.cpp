#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 1505;
constexpr int MAX_M = (MAX_N * MAX_N) << 1;

struct {
    int v;
    int nxt;
    int w;
} node1[MAX_M], node2[MAX_M];

int head1[MAX_N], head2[MAX_N];
int cnt1, cnt2;

void create1(int u, int v, int w);

void create2(int u, int v, int w);

int dis[4][MAX_N];

void dij(int k, int S);

int deg[MAX_N], ans[MAX_N];

void topos();

int n, m;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int S1, T1, S2, T2;
    read(n, m, S1, T1, S2, T2);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        create1(x, y, z);
        create1(y, x, z);
    }

    memset(dis, 0x3f, sizeof(dis));
    dij(0, S1);
    dij(1, T1);
    dij(2, S2);
    dij(3, T2);

    int res{};
    for (int k = 1; k <= n; k++) {
        for (int i = head1[k]; i; i = node1[i].nxt) {
            const auto v = node1[i].v, w = node1[i].w;
            if (dis[0][k] + dis[1][v] + w == dis[0][T1] and
                dis[2][k] + dis[3][v] + w == dis[2][T2]) {
                create2(k, v, w);
                deg[v]++;
            }
        }
    }

    topos();
    for (int i = 1; i <= n; i++) {
        res = std::max(res, ans[i]);
    }
    memset(deg, 0, sizeof(deg));
    memset(ans, 0, sizeof(ans));
    memset(head2, 0, sizeof(head2));
    cnt2 = 0;

    for (int k = 1; k <= n; k++) {
        for (int i = head1[k]; i; i = node1[i].nxt) {
            const auto v = node1[i].v, w = node1[i].w;
            if (dis[0][k] + dis[1][v] + w == dis[0][T1] and
                dis[3][k] + dis[2][v] + w == dis[2][T2]) {
                create2(k, v, w);
                deg[v]++;
            }
        }
    }
    topos();
    for (int i = 1; i <= n; i++) {
        res = std::max(res, ans[i]);
    }

    std::cout << res << '\n';

    return 0;
}

void create1(int u, int v, int w) {
    node1[++cnt1].v = v;
    node1[cnt1].nxt = head1[u];
    node1[cnt1].w = w;
    head1[u] = cnt1;
}

void create2(int u, int v, int w) {
    node2[++cnt2].v = v;
    node2[cnt2].nxt = head2[u];
    node2[cnt2].w = w;
    head2[u] = cnt2;
}

void dij(int k, int S) {
    pq<std::pair<int, int>> q;
    q.push({0, S});
    dis[k][S] = 0;
    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        for (int i = head1[p]; i; i = node1[i].nxt) {
            const auto v = node1[i].v, w = node1[i].w;
            if (dis[k][v] > dis[k][p] + w) {
                dis[k][v] = dis[k][p] + w;
                q.push({dis[k][v], v});
            }
        }
    }
}

void topos() {
    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        for (int i = head2[p]; i; i = node2[i].nxt) {
            const auto v = node2[i].v, w = node2[i].w;
            ans[v] = std::max(ans[v], ans[p] + w);
            deg[v]--;
            if (!deg[v]) {
                q.push(v);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}