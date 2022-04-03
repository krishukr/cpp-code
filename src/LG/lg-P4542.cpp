#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
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

constexpr int INF = 0x3f3f3f3f;

int l[155][155];

template <typename T = int>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read() + 1, m = read(), K = read();
    int s = n + n + 5, t = s + 1;
    auto mcmf = std::make_unique<MCMF>(s, t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            l[i][j] = INF;
        }
        l[i][i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int x = read() + 1, y = read() + 1;
        l[x][y] = l[y][x] = std::min(l[x][y], read());
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (i < std::max(j, k)) {
                    l[j][k] = std::min(l[j][k], l[j][i] + l[i][k]);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            mcmf->create(s, i + i - 1, K, 0);
            mcmf->create(i + i - 1, s, 0, 0);
        } else {
            mcmf->create(s, i + i - 1, 1, 0);
            mcmf->create(i + i - 1, s, 0, 0);
        }
        mcmf->create(i + i, t, 1, 0);
        mcmf->create(t, i + i, 0, 0);

        for (int j = i + 1; j <= n; j++) {
            mcmf->create(i + i - 1, j + j, 1, l[i][j]);
            mcmf->create(j + j, i + i - 1, 0, -l[i][j]);
        }
    }

    std::cout << mcmf->mcmf().second << '\n';

    return 0;
}

template <typename T = int>
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