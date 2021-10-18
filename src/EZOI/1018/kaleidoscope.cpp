#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

int n, m;

template <typename T>
T read();

class Star {
   private:
    const static int MAX_N = 200050;

   public:
    struct Node {
        int v;
        int nxt;
        ll w;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    void create(int u, int v, ll w) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        node[cnt].w = w;
        head[u] = cnt;
    }
};

class MST {
   private:
    Star* star;
    const static int MAX_N = 200050;

   protected:
    ll dis[MAX_N];
    bool vis[MAX_N];
    int tot, crt = 1;

   public:
    MST(Star* star) { this->star = star; }

    ll prim() {
        std::fill(dis, dis + n + 10, 0x3f3f3f3f3f3f3f3f);
        for (int i = star->head[1]; i; i = star->node[i].nxt) {
            int v = star->node[i].v;
            dis[v] = std::min(dis[v], star->node[i].w);
        }
        ll ans = 0;

        while (++tot < n) {
            ll min = 0x3f3f3f3f3f3f3f3f;
            vis[crt] = true;

            for (int i = 1; i <= n; i++) {
                if (!vis[i] and min > dis[i]) {
                    min = dis[i];
                    crt = i;
                }
            }
            ans += min;

            for (int i = star->head[crt]; i; i = star->node[i].nxt) {
                int v = star->node[i].v;
                ll w = star->node[i].w;

                if (dis[v] > w and !vis[v]) {
                    dis[v] = w;
                }
            }
        }

        return ans;
    }
};

signed main() {
    freopen("kaleidoscope.in", "r", stdin);
    freopen("kaleidoscope.out", "w", stdout);

    int t = read<int>();
    while (t--) {
        n = read<int>(), m = read<int>();
        Star* star = new Star();
        for (int i = 1; i <= m; i++) {
            int x = read<int>(), y = read<int>();
            ll z = read<ll>();
            for (int i = 0; i < n; i++) {
                star->create((x + i) % n + 1, (y + i) % n + 1, z);
                star->create((y + i) % n + 1, (x + i) % n + 1, z);
            }
        }

        MST* mst = new MST(star);
        std::cout << mst->prim() << '\n';
    }

    fclose(stdin);
    fclose(stdout);
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