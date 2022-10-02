#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 300050;

class Solution {
   private:
    struct {
        int v;
        int nxt;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    void create(int u, int v);

    struct BIT {
        ll tree[MAX_N << 1];

        void mod(int x, const int& v);

        ll query(int x);
    } t1, t2;

    int f[MAX_N], g[MAX_N];
    bool h[MAX_N];
    int root, lx, ly;
    ll ans;

    void dfs1(int x, int fa);

    void dfs2(int x, int fa);

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

int n;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    return 0;
}

void Solution::create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void Solution::BIT::mod(int x, const int& v) {
    x++;
    while (x <= n + 1) {
        tree[x] += v;
        x += x & -x;
    }
}

ll Solution::BIT::query(int x) {
    x++;
    ll r{};
    while (x) {
        r += tree[x];
        x -= x & -x;
    }
    return r;
}

void Solution::dfs1(int x, int fa) {
    f[x] = 1;
    g[x] = 0;
    bool flag = false;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs1(v, x);
        f[x] += f[v];
        g[x] = std::max(g[x], f[v]);
        if (f[v] > (n >> 1)) {
            flag = true;
        }
    }
    if (n - f[x] > (n >> 1)) {
        flag = true;
    }
    if (!flag) {
        root = x;
    }
}

void Solution::dfs2(int x, int fa) {
    t1.mod(f[fa], -1);
    t1.mod(n - f[x], 1);
    if (x != root) {
        ans += x * t1.query(n - g[x] * 2);
        ans -= x * t1.query(n - f[x] * 2 - 1);
        ans += x * t2.query(n - g[x] * 2);
        ans -= x * t2.query(n - f[x] * 2 - 1);
        if (h[fa]) {
            h[x] = true;
        }
        if (f[x] <= n - f[h[x] ? ly : lx] * 2) {
            ans += root;
        }
    }
    t2.mod(f[x], 1);

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs2(v, x);
    }

    t1.mod(f[fa], 1);
    t1.mod(n - f[x], -1);
    if (x != root) {
        ans -= x * t2.query(n - g[x] * 2);
        ans += x * t2.query(n - f[x] * 2 - 1);
    }
}

void Solution::solve() {
    read(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    dfs1(1, 0);
    dfs1(root, 0);
    for (int i = head[root]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (f[ly] < f[v]) {
            ly = v;
        }
        if (f[lx] < f[ly]) {
            std::swap(lx, ly);
        }
    }
    for (int i = 0; i <= n; i++) {
        t1.mod(f[i], 1);
    }
    h[lx] = true;
    dfs2(root, 0);
    std::cout << ans << '\n';
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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