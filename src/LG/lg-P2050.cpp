#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

class MCMF {
   private:
    static const int MAX_N = 100050;

   public:
    struct Node {
        int v;
        int nxt;
        int w;
        int c;
    } node[MAX_N << 5];

    int head[MAX_N];
    int cnt = 1;

    int dis[MAX_N], flw[MAX_N], pre[MAX_N], nxt[MAX_N], top[MAX_N];
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

    int dfs(int x, int l);

    void solve();
};

const int MAX_N = 105;

int c[MAX_N][MAX_N];
int p[MAX_N];
int n, m, s, t, sum, mc;
MCMF* mcmf;

inline int idx(const int& i, const int& j) { return (i - 1) * sum + j; }

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    sum = 0;
    for (int i = 1; i <= n; i++) {
        p[i] = read<int>();
        sum += p[i];
    }

    s = m * sum + n + 5, t = s + 1;
    mcmf = new MCMF(s, t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[i][j] = read<int>();
            mcmf->create(i, n + idx(j, 1), 1, c[i][j]);
            mcmf->create(n + idx(j, 1), i, 0, -c[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        mcmf->create(s, i, p[i], 0);
        mcmf->create(i, s, 0, 0);
    }
    for (int i = 1; i <= m; i++) {
        mcmf->top[i] = 1;
        mcmf->create(n + idx(i, 1), t, 1, 0);
        mcmf->create(t, n + idx(i, 1), 0, 0);
    }

    mcmf->solve();
    std::cout << mc << '\n';
    delete mcmf;

    return 0;
}

int MCMF::dfs(int x, int l) {
    if (x == t) {
        return l;
    }
    int flw = 0;
    vis[x] = true;

    for (int i = head[x]; i and l; i = node[i].nxt) {
        int v = node[i].v, w = node[i].w;
        if (vis[v]) {
            continue;
        }

        if (w and dis[v] == dis[x] + node[i].c) {
            int k = dfs(v, std::min(l, w));
            if (k) {
                node[i].w -= k;
                node[i ^ 1].w += k;

                l -= k;
                flw += k;

                mc += k * node[i].c;
                nxt[x] = v;
            }
        }
    }

    if (!flw) {
        dis[x] = 0x3f3f3f3f;
    }
    vis[x] = 0;
    return flw;
}

void MCMF::solve() {
    while (spfa()) {
        dfs(s, 0x3f3f3f3f);
        for (int i = 1; i <= m; i++) {
            if (nxt[n + idx(i, top[i])] and top[i] < sum) {
                top[i]++;
                int x = n + idx(i, top[i]);

                for (int j = 1; j <= n; j++) {
                    create(j, x, 1, c[j][i] * top[i]);
                    create(x, j, 0, -(c[j][i] * top[i]));
                }
                create(x, t, 1, 0);
                create(t, x, 0, 0);
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