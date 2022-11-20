#include <bits/stdc++.h>

using ll = long long;

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 100050;
constexpr int MAX_M = 1000050;
constexpr ll INF = 1e15;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_M << 2];

int head[MAX_M];
int cnt;

void create(int u, int v, int w);

class SegTree {
    void build(int x, int l, int r);

   public:
    int tree[MAX_N << 2];

    SegTree() = default;
    SegTree(const int n) { this->build(1, 1, n); }
    ~SegTree() = default;

    void mod(int x, int l, int r, const int ml, const int mr);
};

ll dis[MAX_M], ans[MAX_M];
bool vis[MAX_M];

void dij(int S);

void adij();

int m;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, k;
    read(n, k);
    m = n << 2;
    auto segTree = std::make_unique<SegTree>(n);
    for (int i = 1; i <= k; i++) {
        int c, p, a, b;
        read(c, p, a, b);
        c = segTree->tree[c];
        create(++m, c, p);
        segTree->mod(1, 1, n, a, b);
    }

    dij(segTree->tree[1]);
    for (int i = 1; i <= m; i++) {
        ans[i] += dis[i];
    }
    dij(segTree->tree[n]);
    for (int i = 1; i <= m; i++) {
        ans[i] += dis[i];
    }

    adij();
    for (int i = 1; i <= n; i++) {
        const auto t = ans[segTree->tree[i]];
        std::cout << (t >= INF ? -1 : t) << '\n';
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[l] = x;
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    create(lc, x, 0);
    create(rc, x, 0);
}

void SegTree::mod(int x, int l, int r, const int ml, const int mr) {
    if (ml <= l and r <= mr) {
        create(x, m, 0);
        return;
    }
    const auto mid = (l + r) >> 1;
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr);
    }
}

#undef lc
#undef rc

void dij(int S) {
    std::fill(dis, dis + m + 10, INF);
    std::fill(vis, vis + m + 10, false);
    pq<std::pair<ll, int>> q;
    q.push({0, S});
    dis[S] = 0;

    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                q.push({dis[v], v});
            }
        }
    }
}

void adij() {
    std::fill(vis, vis + m + 10, false);
    pq<std::pair<ll, int>> q;
    for (int i = 1; i <= m; i++) {
        q.push({ans[i], i});
    }

    while (!q.empty()) {
        const auto p = q.top().second;
        q.pop();
        if (vis[p]) {
            continue;
        }
        vis[p] = true;
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            if (ans[v] > ans[p] + w) {
                ans[v] = ans[p] + w;
                q.push({ans[v], v});
            }
        }
    }
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