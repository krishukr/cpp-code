#include <algorithm>
#include <cstdio>
#include <iostream>

class Flow {
   private:
    const static int MAX_N = 5000050;

   protected:
    struct Node {
        int v;
        int nxt;
        int w;
    } node[MAX_N];

    int head[MAX_N], dep[MAX_N], q[MAX_N];
    int cnt = 1, n, s, t;
    int ans;

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

    int dfs(int x, int flow) {
        if (x == t) {
            return flow;
        }
        int tot = 0;

        for (int i = head[x]; i and flow; i = node[i].nxt) {
            int y = node[i].v;
            if (node[i].w and dep[y] == dep[x] + 1) {
                int res = dfs(y, std::min(node[i].w, flow));
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

    void create(int u, int v, int w) {
        node[++cnt].v = v;
        node[cnt].w = w;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }

    int dinic() {
        while (bfs()) {
            ans += dfs(s, 0x7fffffff);
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
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    int s = n + m + 5, t = n + m + 6, sum = 0;
    auto* flow = new Flow(n + m + 10, s, t);

    for (int i = 1; i <= n; i++) {
        int x = read<int>(), t = read<int>();
        sum += x;
        flow->create(s, i, x);
        flow->create(i, s, 0);

        for (int j = 1; j <= t; j++) {
            int a = read<int>(), b = read<int>();
            flow->create(i, n + a, b);
            flow->create(n + a, i, 0);
        }
    }

    for (int i = 1; i <= m; i++) {
        int y = read<int>();
        flow->create(n + i, t, y);
        flow->create(t, n + i, 0);
    }

    std::cout << sum - flow->dinic() << '\n';

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