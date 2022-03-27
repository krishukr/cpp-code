#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

typedef long long ll;

constexpr int MAX_N = 4000100;
constexpr int EP = 500050;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

int tree[MAX_N];

ll dis[MAX_N];
std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>,
                    std::greater<std::pair<ll, int>>>
    qu;

void create(int u, int v, int w);

// SegTree
void build(int x, int l, int r);

void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv,
         const int& mw, const int& op);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), q = read<int>(), s = read<int>();

    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        create(tree[i], tree[i] + EP, 0);
        create(tree[i] + EP, tree[i], 0);
    }

    for (int i = 1; i <= q; i++) {
        int op = read<int>();
        if (op == 1) {
            int v = read<int>(), u = read<int>(), w = read<int>();
            create(tree[v] + EP, tree[u], w);
        } else {
            int v = read<int>(), l = read<int>(), r = read<int>(),
                w = read<int>();
            mod(1, 1, n, l, r, tree[v], w, op);
        }
    }

    memset(dis, 0x3f, sizeof(dis));
    qu.push({0, tree[s] + EP});
    dis[tree[s] + EP] = 0;

    while (!qu.empty()) {
        auto p = qu.top();
        qu.pop();
        auto s = p.first;
        int x = p.second;

        if (dis[x] < s) {
            continue;
        }
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (dis[v] > s + w) {
                dis[v] = s + w;
                qu.push({dis[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << (dis[tree[i]] == INF ? -1 : dis[tree[i]]) << ' ';
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

#define lc x * 2
#define rc x * 2 + 1

void build(int x, int l, int r) {
    if (l == r) {
        tree[l] = x;
        return;
    }
    create(x, lc, 0);
    create(lc + EP, x + EP, 0);
    create(x, rc, 0);
    create(rc + EP, x + EP, 0);

    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv,
         const int& mw, const int& op) {
    if (ml <= l and r <= mr) {
        if (op == 2) {
            create(mv + EP, x, mw);
        } else if (op == 3) {
            create(x + EP, mv, mw);
        }
        return;
    }

    int mid = (l + r) >> 1;
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr, mv, mw, op);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr, mv, mw, op);
    }
}

#undef lc
#undef rc

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