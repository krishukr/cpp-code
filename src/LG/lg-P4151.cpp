#include <cstdio>
#include <iostream>

template <typename T>
T read();

class Basis {
   private:
    typedef long long ll;

    const static int SIZE = 64;

   protected:
    ll p[SIZE];

   public:
    void insert(ll x) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (!p[i]) {
                    p[i] = x;
                    return;
                } else {
                    x ^= p[i];
                }
            }
        }
    }

    ll query(ll x) {
        ll ans = x;
        for (int i = SIZE - 1; i >= 0; i--) {
            ans = std::max(ans, ans ^ p[i]);
        }
        return ans;
    }
};

class Star {
   private:
    const static int MAX_N = 200050;
    typedef long long ll;

   protected:
    struct Node {
        int v;
        int nxt;
        ll w;
    } node[MAX_N];

    int head[MAX_N];
    int cnt;

   public:
    void create(int u, int v, ll w) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        node[cnt].w = w;
        head[u] = cnt;
    }
};

class Solution : public Basis, public Star {
   private:
    typedef long long ll;

    const static int MAX_N = 100050;

   protected:
    bool vis[MAX_N];
    ll lst[MAX_N];

    void dfs(int x, int f, ll r) {
        vis[x] = true;
        lst[x] = r;

        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            ll w = node[i].w;

            if (v == f) {
                continue;
            }
            if (!vis[v]) {
                dfs(v, x, r ^ w);
            } else {
                insert(r ^ w ^ lst[v]);
            }
        }
    }

   public:
    void solve() {
        int n = read<int>(), m = read<int>();
        for (int i = 1; i <= m; i++) {
            int x = read<int>(), y = read<int>();
            ll z = read<ll>();
            create(x, y, z);
            create(y, x, z);
        }

        dfs(1, 0, 0ll);
        std::cout << query(lst[n]) << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    Solution* solution = new Solution();
    solution->solve();
    delete solution;

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
};