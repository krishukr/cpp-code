#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

class MCMF {
   private:
    static const int MAX_N = 1000050;

   protected:
    struct Node {
        int v;
        int nxt;
        int w;
        int c;
    } node[MAX_N];

    int head[MAX_N];
    int cnt = 1;

    int dis[MAX_N], flw[MAX_N], pre[MAX_N];
    bool vis[MAX_N];
    int s, t;

    bool spfa() {
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));

        std::queue<int> q;
        q.push(s);
        vis[s] = true;
        dis[s] = 0;
        flw[s] = INT_MAX;

        while (!q.empty()) {
            int h = q.front();
            q.pop();
            vis[h] = false;

            for (int i = head[h]; i; i = node[i].nxt) {
                int v = node[i].v;
                if (!node[i].w) {
                    continue;
                }

                if (dis[v] > dis[h] + node[i].c) {
                    dis[v] = dis[h] + node[i].c;
                    flw[v] = std::min(flw[h], node[i].w);
                    pre[v] = i;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }

        return dis[t] != 0x3f3f3f3f;
    }

   public:
    MCMF() = default;
    MCMF(int s, int t) {
        this->s = s;
        this->t = t;
    }
    ~MCMF() = default;

    void set_st(int s, int t) {
        this->s = s;
        this->t = t;
    }

    void create(int u, int v, int w, int c) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        node[cnt].w = w;
        node[cnt].c = c;
        head[u] = cnt;
    }

    std::pair<int, int> mcmf() {
        int f = 0, c = 0;
        while (spfa()) {
            int x = t;
            f += flw[x];
            c += dis[x] * flw[x];

            for (int i; x != s; x = node[i ^ 1].v) {
                i = pre[x];
                node[i].w -= flw[t];
                node[i ^ 1].w += flw[t];
            }
        }
        return std::make_pair(f, c);
    }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();
    int s = n * n * 3 + 5, t = s + 1;
    auto idx = [&n](const int& i, const int& j) { return (i - 1) * n + j; };
    auto* mcmf = new MCMF(s, t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = read<int>();

            mcmf->create(idx(i, j), n * n + idx(i, j), 1, -x);
            mcmf->create(n * n + idx(i, j), idx(i, j), 0, x);

            mcmf->create(idx(i, j), n * n + idx(i, j), 0x3f3f3f3f, 0);
            mcmf->create(n * n + idx(i, j), idx(i, j), 0, 0);

            if (i < n) {
                mcmf->create(n * n + idx(i, j), idx(i + 1, j), 0x3f3f3f3f, 0);
                mcmf->create(idx(i + 1, j), n * n + idx(i, j), 0, 0);
            }
            if (j < n) {
                mcmf->create(n * n + idx(i, j), idx(i, j + 1), 0x3f3f3f3f, 0);
                mcmf->create(idx(i, j + 1), n * n + idx(i, j), 0, 0);
            }
        }
    }

    mcmf->create(s, 1, k, 0);
    mcmf->create(1, s, 0, 0);
    mcmf->create(n * n * 2, t, k, 0);
    mcmf->create(t, n * n * 2, 0, 0);

    std::cout << -(mcmf->mcmf().second) << '\n';

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