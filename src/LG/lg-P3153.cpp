#include <algorithm>
#include <cstdio>
#include <iostream>

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
        std::fill(head, head + cnt + 10, 0);
        cnt = 1;
        ans = 0;
    }
};

bool mp[55][55];

int n, k, s, t;
Flow* flow;

void build(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), k = read<int>();
    s = n * 4 + 5, t = s + 1;
    flow = new Flow(n * 4 + 10, s, t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char ch = getchar();
            while (ch != 'Y' and ch != 'N') {
                ch = getchar();
            }

            mp[i][j] = (ch == 'Y');
        }
    }

    int l = 0, r = n;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        build(mid);

        if (flow->dinic() == mid * n) {
            l = mid;
        } else {
            r = mid;
        }

        flow->clear();
    }

    build(r);
    std::cout << (flow->dinic() == r * n ? r : l) << '\n';

    return 0;
}

void build(int x) {
    for (int i = 1; i <= n; i++) {
        flow->create(s, i, x);
        flow->create(i, s, 0);

        flow->create(i + n * 2, t, x);
        flow->create(t, i + n * 2, 0);

        flow->create(i, i + n, k);
        flow->create(i + n, i, 0);

        flow->create(i + n * 3, i + n * 2, k);
        flow->create(i + n * 2, i + n * 3, 0);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (mp[i][j]) {
                flow->create(i, j + n * 2, 1);
                flow->create(j + n * 2, i, 0);
            } else {
                flow->create(i + n, j + n * 3, 1);
                flow->create(j + n * 3, i + n, 0);
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