#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

class MCMF {
   private:
    static const int MAX_N = 100050;

   protected:
    class Result {
       public:
        int max_flow;
        int min_cost;

        Result() = default;
        Result(int max_flow, int min_cost) {
            this->max_flow = max_flow;
            this->min_cost = min_cost;
        }
        ~Result() = default;
    };

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

    Result* __instance = nullptr;

    auto __mcmf() {
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
        return new Result(f, c);
    }

   public:
    MCMF() = default;
    MCMF(int s, int t) {
        this->s = s;
        this->t = t;
    }
    ~MCMF() {
        if (this->__instance != nullptr) {
            delete this->__instance;
        }
    }

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

    auto mcmf() {
        if (__instance == nullptr) {
            __instance = __mcmf();
        }
        return __instance;
    }
};

const int MAX_N = 105;

int c[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    int s = n + n + 5, t = s + 1;
    auto* mcmf = new MCMF(s, t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c[i][j] = read<int>();
        }
    }

    for (int i = 1; i <= n; i++) {
        mcmf->create(s, i, 1, 0);
        mcmf->create(i, s, 0, 0);
        mcmf->create(n + i + 1, t, 1, 0);
        mcmf->create(t, n + i + 1, 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mcmf->create(i, n + j + 1, 1, -c[i][j]);
            mcmf->create(n + j + 1, i, 0, c[i][j]);
        }
    }

    auto me = *(mcmf->mcmf());
    delete mcmf;
    mcmf = new MCMF(s, t);

    for (int i = 1; i <= n; i++) {
        mcmf->create(s, i, 1, 0);
        mcmf->create(i, s, 0, 0);
        mcmf->create(n + i + 1, t, 1, 0);
        mcmf->create(t, n + i + 1, 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mcmf->create(i, n + j + 1, 1, c[i][j]);
            mcmf->create(n + j + 1, i, 0, -c[i][j]);
        }
    }

    std::cout << mcmf->mcmf()->min_cost << '\n' << -(me.min_cost) << '\n';

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