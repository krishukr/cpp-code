#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>

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
        memset(dep, 0, sizeof(dep));
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
    bool vis[MAX_N];

    Flow(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
    }
    ~Flow() = default;

    void create(int u, int v, long long w) {
        node[++cnt].v = v;
        node[cnt].w = w;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }

    void out(int x) {
        if (vis[x]) {
            return;
        }
        vis[x] = true;
        std::cout << x << ' ';
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (!w and v != s) {
                out(v - n);
            }
        }
    }

    long long dinic() {
        while (bfs()) {
            ans += dfs(s, 0x7fffffffffffffff);
        }
        return ans;
    }
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    int s = n + n + 5, t = s + 1;
    auto flow = std::make_unique<Flow>(n, s, t);

    for (int i = 1; i <= n; i++) {
        flow->create(s, i, 1);
        flow->create(i, s, 0);
        flow->create(n + i, t, 1);
        flow->create(t, n + i, 0);
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        flow->create(x, n + y, 1);
        flow->create(n + y, x, 0);
    }

    const auto res = flow->dinic();
    for (int i = 1; i <= n; i++) {
        if (!flow->vis[i]) {
            flow->out(i);
            std::cout << '\n';
        }
    }
    std::cout << n - res << '\n';

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