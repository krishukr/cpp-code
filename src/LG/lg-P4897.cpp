#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>

template <typename T>
T read();

class Flow {
   private:
    const static int MAX_N = 500050;

   protected:
    struct Node {
        int v;
        int nxt;
        long long w;
    } node[MAX_N];

    int head[MAX_N], dep[MAX_N], q[MAX_N];
    int cnt = 1, n, s, t;
    long long ans;

    bool bfs() {
        std::fill(dep, dep + n + 10, 0);
        int l, r;
        l = r = 1;
        q[l] = s;
        dep[s] = 1;

        while (l <= r) {
            int u = q[l++];
            for (int i = head[u]; i; i = node[i].nxt) {
                if (node[i].w and !dep[node[i].v]) {
                    dep[node[i].v] = dep[u] + 1;
                    q[++r] = node[i].v;
                }
            }
        }

        return dep[t];
    }

    long long dfs(int x, long long flow) {
        if (x == t) {
            return flow;
        }
        long long tot = 0;

        for (int i = head[x]; i and flow; i = node[i].nxt) {
            int y = node[i].v;
            if (node[i].w and dep[y] == dep[x] + 1) {
                long long res = dfs(y, std::min(node[i].w, flow));
                node[i].w -= res;
                node[i ^ 1].w += res;
                flow -= res;
                tot += res;
            }
        }

        if (tot == 0) {
            dep[x] = 0;
        }
        return tot;
    }

   public:
    Flow(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
    }
    Flow(int n) { this->n = n; }
    ~Flow() = default;

    void create(int u, int v, long long w) {
        node[++cnt].v = v;
        node[cnt].w = w;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }

    long long dinic() {
        while (bfs()) {
            ans += dfs(s, 0x7fffffffffffffff);
        }
        return ans;
    }

    void set_st(int s, int t) {
        this->s = s;
        this->t = t;
    }

    void clear() {
        std::fill(node, node + cnt + 10, (Node){0, 0, 0});
        std::fill(head, head + cnt + 10, 0);
        std::fill(q, q + n + 10, 0);
        n = s = t = 0;
        cnt = 1;
        ans = 0;
    }

    void back() {
        for (int i = 2; i <= cnt; i += 2) {
            node[i].w += node[i ^ 1].w;
            node[i ^ 1].w = 0;
        }
        ans = 0;
    }

    int* get_dep() { return this->dep; }
};

class Tree {
   private:
    const static int MAX_N = 500050;
    Flow* flow;

   protected:
    struct Node {
        int v;
        int nxt;
        long long w;
    } node[MAX_N];

    int head[MAX_N];
    int cnt = 1;

    int fa[MAX_N], t1[MAX_N], t2[MAX_N];

    int lg;
    int dep[MAX_N];
    int gdf[MAX_N][20];
    long long min[MAX_N][20];

    void build(int l, int r) {
        if (l == r) {
            return;
        }

        int s = fa[l], t = fa[l + 1];
        flow->set_st(s, t);
        flow->back();
        long long w = flow->dinic();

        create(s, t, w);
        create(t, s, w);

        int cnt1 = 0, cnt2 = 0;
        for (int i = l; i <= r; i++) {
            if (flow->get_dep()[fa[i]]) {
                t1[++cnt1] = fa[i];
            } else {
                t2[++cnt2] = fa[i];
            }
        }

        for (int i = l; i <= l + cnt1 - 1; i++) {
            fa[i] = t1[i - l + 1];
        }
        for (int i = l + cnt1; i <= r; i++) {
            fa[i] = t2[i - l - cnt1 + 1];
        }

        build(l, l + cnt1 - 1);
        build(l + cnt1, r);
    }

    void dfs(int x, int f) {
        dep[x] = dep[f] + 1;
        for (int i = 1; i <= lg; i++) {
            gdf[x][i] = gdf[gdf[x][i - 1]][i - 1];
            min[x][i] = std::min(min[x][i - 1], min[gdf[x][i - 1]][i - 1]);
        }

        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            long long w = node[i].w;
            if (v == f) {
                continue;
            }

            gdf[v][0] = x;
            min[v][0] = w;
            dfs(v, x);
        }
    }

   public:
    Tree(Flow* flow, int n) {
        this->flow = flow;
        this->lg = std::log2(n) + 1;

        std::iota(fa + 1, fa + n + 1, 1);
        build(1, n);
        dfs(1, 0);
    }
    ~Tree() = default;

    void create(int u, int v, long long w) {
        node[++cnt].v = v;
        node[cnt].w = w;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }

    long long query(int x, int y) {
        long long ans = 0x7fffffffffffffff;
        if (dep[x] < dep[y]) {
            std::swap(x, y);
        }

        for (int i = lg; i >= 0; i--) {
            int f = gdf[x][i];
            if (dep[f] >= dep[y]) {
                ans = std::min(ans, min[x][i]);
                x = f;
            }
        }
        if (x == y) {
            return ans;
        }

        for (int i = lg; i >= 0; i--) {
            if (gdf[x][i] != gdf[y][i]) {
                ans = std::min(ans, std::min(min[x][i], min[y][i]));
                x = gdf[x][i];
                y = gdf[y][i];
            }
        }
        ans = std::min(ans, std::min(min[x][0], min[y][0]));

        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    auto* flow = new Flow(n);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        long long z = read<long long>();
        flow->create(x, y, z);
        flow->create(y, x, 0);
        flow->create(y, x, z);
        flow->create(x, y, 0);
    }

    auto* tree = new Tree(flow, n);
    int q = read<int>();
    while (q--) {
        int x = read<int>(), y = read<int>();
        std::cout << tree->query(x, y) << '\n';
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