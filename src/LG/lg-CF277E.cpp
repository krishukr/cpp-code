#include <bits/stdc++.h>

class MCMF {
   private:
    static constexpr int MAX_N = 1000050;

   protected:
    struct Node {
        int v;
        int nxt;
        int w;
        double c;
    } node[MAX_N];

    int head[MAX_N];
    int cnt = 1;

    double dis[MAX_N];
    int flw[MAX_N], pre[MAX_N];
    bool vis[MAX_N];
    int s, t;

    bool spfa() {
        std::fill(std::begin(dis), std::end(dis), INT_MAX);
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

        return dis[t] < INT_MAX;
    }

    void create(int u, int v, int w, double c) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        node[cnt].w = w;
        node[cnt].c = c;
        head[u] = cnt;
    }

   public:
    MCMF() = default;
    MCMF(int s, int t) {
        this->s = s;
        this->t = t;
    }
    ~MCMF() = default;

    void createE(int u, int v, int w, double c) {
        create(u, v, w, c);
        create(v, u, 0, -c);
    }

    std::pair<int, double> mcmf() {
        int f = 0;
        double c = 0;
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
        return {f, c};
    }
};

std::pair<int, int> p[405];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    const int S = n + n + 5, T = S + 1;
    auto mcmf = std::make_unique<MCMF>(S, T);

    for (int i = 1; i <= n; i++) {
        int x, y;
        read(x, y);
        p[i] = {x, y};
    }
    std::sort(p + 1, p + n + 1,
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return (a.second == b.second ? a.first > b.first
                                               : a.second > b.second);
              });

    for (int i = 1; i <= n; i++) {
        mcmf->createE(S, i, 2, 0);
        mcmf->createE(n + i, T, 1, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (p[i].second > p[j].second) {
                mcmf->createE(i, n + j, 1,
                              std::sqrt(1.0 * (p[i].first - p[j].first) *
                                            (p[i].first - p[j].first) +
                                        1.0 * (p[i].second - p[j].second) *
                                            (p[i].second - p[j].second)));
            }
        }
    }

    const auto ans = mcmf->mcmf();
    if (ans.first == n - 1) {
        std::cout << std::fixed << std::setprecision(6) << ans.second << '\n';
    } else {
        std::cout << -1 << '\n';
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}