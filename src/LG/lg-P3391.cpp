#include <climits>
#include <cstdio>
#include <iostream>

const int MAX_N = 100000;

struct Node {
    int f;      // father
    int v;      // value
    int t;      // tag
    int c;      // count
    int s;      // size
    int ch[2];  // child
} tree[MAX_N << 4];

int head[MAX_N << 4];
int root, tot;

#pragma region initial
bool is_right(int x);

void pushdown(int x);

void update(int x);

void rotate(int x);

void splay(int x, int g);

int create(int l, int r, int f);

int query(int x);

void reverse(int x, int y);

void dfs(int x);

inline int read();
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);

    int n = read(), m = read();
    head[1] = INT_MIN;
    head[n + 2] = INT_MAX;

    for (int i = 1; i <= n; i++) {
        head[i + 1] = i;
    }
    root = create(1, n + 2, 0);

    for (int i = 1; i <= m; i++) {
        int x = read(), y = read();
        reverse(x + 1, y + 1);
    }
    dfs(root);

    return 0;
}

bool is_right(int x) { return x == tree[tree[x].f].ch[1]; }

void pushdown(int x) {
    if (x and tree[x].t) {
        tree[tree[x].ch[0]].t ^= 1;
        tree[tree[x].ch[1]].t ^= 1;
        std::swap(tree[x].ch[0], tree[x].ch[1]);
        tree[x].t = 0;
    }
}

void update(int x) {
    if (x) {
        tree[x].s = tree[x].c;
        if (tree[x].ch[0]) {
            tree[x].s += tree[tree[x].ch[0]].s;
        }
        if (tree[x].ch[1]) {
            tree[x].s += tree[tree[x].ch[1]].s;
        }
    }
}

void rotate(int x) {
    int fa = tree[x].f;
    int gf = tree[fa].f;
    pushdown(x);
    pushdown(fa);

    bool flag = is_right(x);
    tree[fa].ch[flag] = tree[x].ch[flag ^ 1];
    tree[tree[fa].ch[flag]].f = fa;
    tree[fa].f = x;
    tree[x].f = gf;
    tree[x].ch[flag ^ 1] = fa;
    if (gf) {
        tree[gf].ch[tree[gf].ch[1] == fa] = x;
    }
    update(fa);
}

void splay(int x, int g) {
    for (int i; (i = tree[x].f) != g; rotate(x)) {
        if (tree[i].f != g) {
            rotate(is_right(x) == is_right(i) ? i : x);
        }
    }
    if (!g) {
        root = x;
    }
}

int create(int l, int r, int f) {
    if (l > r) {
        return 0;
    }
    int mid = (l + r) / 2;
    int crt = ++tot;
    tree[crt].f = f;
    tree[crt].c++;
    tree[crt].s++;
    tree[crt].v = head[mid];
    tree[crt].ch[0] = create(l, mid - 1, crt);
    tree[crt].ch[1] = create(mid + 1, r, crt);
    update(crt);
    return crt;
}

int query(int x) {
    int crt = root;
    while (true) {
        pushdown(crt);
        if (x <= tree[tree[crt].ch[0]].s) {
            crt = tree[crt].ch[0];
        } else {
            x -= tree[tree[crt].ch[0]].s + 1;
            if (!x) {
                return crt;
            }
            crt = tree[crt].ch[1];
        }
    }
}

void reverse(int x, int y) {
    int l = query(x - 1), r = query(y + 1);
    splay(l, 0);
    splay(r, l);
    int p = tree[root].ch[1];
    p = tree[p].ch[0];
    tree[p].t ^= 1;
}

void dfs(int x) {
    pushdown(x);
    if (tree[x].ch[0]) {
        dfs(tree[x].ch[0]);
    }
    if (tree[x].v != INT_MIN and tree[x].v != INT_MAX) {
        std::cout << tree[x].v << ' ';
    }
    if (tree[x].ch[1]) {
        dfs(tree[x].ch[1]);
    }
}

inline int read() {
    int x = 0, f = 1;
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