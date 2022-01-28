#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 101;

class Star {
   private:
    int cnt;
    int head[MAX_N];

    struct Node {
        int v;
        int nxt;
        ll w;
    } node[MAX_N];

   public:
    int n;
    ll t;
    bool flag = false;

    void create(int u, int v, ll w);
    void dfs(ll cst, int x, int f);
};

template <typename T>
T read();

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>(), m = read<int>();
        Star s;
        s.t = read<ll>(), s.n = n;

        for (int i = 1; i <= m; i++) {
            int x = read<int>(), y = read<int>();
            ll z = read<ll>();

            s.create(x, y, z);
            s.create(y, x, z);
        }

        s.dfs(0, 0, 0);
        if (!s.flag) {
            std::cout << "Impossible\n";
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void Star::create(int u, int v, ll w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void Star::dfs(ll cst, int x, int f) {
    if (flag) {
        return;
    }
    if (cst > t) {
        return;
    }
    if (cst == t) {
        if (x == n - 1) {
            std::cout << "Possible\n";
            flag = true;
        }
        return;
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        ll w = node[i].w;
        dfs(cst + w, v, x);
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