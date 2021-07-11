#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

const int MAX_N = 150000;

struct Node {
    int lc;  // 左儿子
    int rc;  // 右儿子
    int s;   // 节点数
    int v;   // 数值
    int p;   // 权重
} tree[MAX_N];

int tot, cnt;
int crt, qx, qy, qqx, qqy;
std::string s[MAX_N];

#pragma region initial
void update(int x);

int create(int x);

void spilt(int l, int r, int &x, int &y);

int merge(int x, int y);

void insert(int x, int y);

void query(int x);

int read();
#pragma endregion initial

int main() {
    // std::ios::sync_with_stdio(false);
    srand(20210711);

    int n = read();
    for (int i = 1; i <= n; i++) {
        std::cin >> s[++cnt];
        insert(i - 1, cnt);
    }
    int m = read();
    for (int i = 1; i <= m; i++) {
        std::cin >> s[++cnt];
        insert(read(), cnt);
    }

    int q = read();
    for (int i = 1; i <= q; i++) {
        query(read());
    }

    return 0;
}

void update(int x) { tree[x].s = tree[tree[x].lc].s + tree[tree[x].rc].s + 1; }

int create(int x) {
    tree[++tot].s = 1;
    tree[tot].v = x;
    tree[tot].p = rand();
    return tot;
}

void spilt(int l, int r, int &x, int &y) {
    if (!l) {
        x = y = 0;
    } else {
        if (r <= tree[tree[l].lc].s) {
            y = l;
            spilt(tree[l].lc, r, x, tree[l].lc);
        } else {
            x = l;
            spilt(tree[l].rc, r - tree[tree[l].lc].s - 1, tree[l].rc, y);
        }
        update(l);
    }
}

int merge(int x, int y) {
    if (!x or !y) {
        return x + y;
    }
    if (tree[x].p < tree[y].p) {
        tree[x].rc = merge(tree[x].rc, y);
        update(x);
        return x;
    } else {
        tree[y].lc = merge(x, tree[y].lc);
        update(y);
        return y;
    }
}

void insert(int x, int y) {
    spilt(crt, x, qx, qy);
    crt = merge(qx, merge(create(y), qy));
}

void query(int x) {
    spilt(crt, x, qx, qy);
    spilt(qy, 1, qqx, qqy);
    std::cout << s[tree[qqx].v] << '\n';
    crt = merge(qx, merge(qqx, qqy));
}

int read() {
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