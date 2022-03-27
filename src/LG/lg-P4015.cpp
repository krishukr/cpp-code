#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

class MCMF {
   private:
    static const int MAX_N = 100050;

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

constexpr int MAX_M = 105;
int a[MAX_M], b[MAX_M];
int c[MAX_M][MAX_M];

int main() {
    std::ios::sync_with_stdio(false);

    int m = read<int>(), n = read<int>();
    int s = m + n + 5, t = s + 1;
    auto* mcmf = new MCMF(s, t);

    for (int i = 1; i <= m; i++) {
        a[i] = read<int>();
        mcmf->create(s, i, a[i], 0);
        mcmf->create(i, s, 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        b[i] = read<int>();
        mcmf->create(i + m, t, b[i], 0);
        mcmf->create(t, i + m, 0, 0);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            c[i][j] = read<int>();
            mcmf->create(i, j + m, 0x3f3f3f3f, c[i][j]);
            mcmf->create(j + m, i, 0, -c[i][j]);
        }
    }

    std::cout << mcmf->mcmf().second << '\n';

    delete mcmf;
    mcmf = new MCMF(s, t);

    for (int i = 1; i <= m; i++) {
        mcmf->create(s, i, a[i], 0);
        mcmf->create(i, s, 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        mcmf->create(i + m, t, b[i], 0);
        mcmf->create(t, i + m, 0, 0);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            mcmf->create(i, j + m, 0x3f3f3f3f, -c[i][j]);
            mcmf->create(j + m, i, 0, c[i][j]);
        }
    }

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