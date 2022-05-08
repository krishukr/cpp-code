#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;
constexpr int MAX_L = 21;

namespace Gen {
unsigned int s;

unsigned int get(unsigned int x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return s = x;
}
}  // namespace Gen

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v);

int f[MAX_L][MAX_N];
int d[MAX_N];

void dfs(int x);

int query(int x, int k);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, q, r;
    read(n, q, Gen::s);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        if (x == 0) {
            r = i;
            f[0][i] = i;
        } else {
            f[0][i] = x;
            create(x, i);
        }
    }

    dfs(r);

    long long a{0};
    int l{0};
    for (int i = 1; i <= q; i++) {
        int x = ((Gen::get(Gen::s) ^ l) % n) + 1,
            k = (Gen::get(Gen::s) ^ l) % d[x];
        l = query(x, k);
        a ^= 1ll * i * l;
    }
    std::cout << a << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    d[x] = d[f[0][x]] + 1;
    for (int i = 0; i + 1 < MAX_L; i++) {
        f[i + 1][x] = f[i][f[i][x]];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        dfs(node[i].v);
    }
}

int query(int x, int k) {
    for (int i = MAX_L; i >= 0; i--) {
        if (k >= (1 << i)) {
            x = f[i][x];
            k -= (1 << i);
        }
    }
    return x;
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