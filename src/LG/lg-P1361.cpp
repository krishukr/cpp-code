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

    void set_n(int n) { this->n = n; }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), s = n + 5, t = s + 1, tot = 0;
    auto* flow = new Flow(0, s, t);

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        flow->create(s, i, x);
        flow->create(i, s, 0);
        tot += x;
    }
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        flow->create(i, t, x);
        flow->create(t, i, 0);
        tot += x;
    }

    int m = read<int>();
    flow->set_n(n + m + m + 10);

    for (int i = 1; i <= m; i++) {
        int k = read<int>(), c1 = read<int>(), c2 = read<int>();
        flow->create(s, t + i, c1);
        flow->create(t + i, s, 0);
        flow->create(t + i + m, t, c2);
        flow->create(t, t + i + m, 0);
        tot += c1;
        tot += c2;

        for (int j = 1; j <= k; j++) {
            int x = read<int>();
            flow->create(t + i, x, 0x3f3f3f3f);
            flow->create(x, t + i, 0);
            flow->create(x, t + i + m, 0x3f3f3f3f);
            flow->create(t + i + m, x, 0);
        }
    }

    std::cout << tot - flow->dinic() << '\n';

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