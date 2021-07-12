#include <cstdio>
#include <iostream>

const int MAX_N = 5000000;

struct Node {
    int lc;  // 左儿子
    int rc;  // 右儿子
    int s;   // 子节点和
    char d;  // 数据
} tree[MAX_N << 2];

int root[MAX_N];
int cnt = 1;

void update(int x);

int create(int x);

void mod(int &x, int p, int l, int r, char v);

char query(int x, int l, int r, int k);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    int m = n;
    for (int i = 1; i <= m; i++) {
        char op;
        std::cin >> op;
        if (op == 'T') {
            char x;
            std::cin >> x;
            mod(root[i], root[i - 1], 1, n, x);
        }
        if (op == 'U') {
            int x;
            std::cin >> x;
            root[i] = root[i - x - 1];
        }
        if (op == 'P') {
            int x;
            std::cin >> x;
            i--, m--;
            std::cout << query(root[i], 1, n, x + 1) << '\n';
        }
    }

    return 0;
}

void update(int x) { tree[x].s = tree[tree[x].lc].s + tree[tree[x].rc].s; }

int create(int x) {
    tree[++cnt].lc = tree[x].lc;
    tree[cnt].rc = tree[x].rc;
    tree[cnt].s = tree[x].s + 1;
    tree[cnt].d = tree[x].d;
    return cnt;
}

void mod(int &x, int p, int l, int r, char v) {
    x = create(p);
    if (l > r) {
        return;
    }
    if (l == r) {
        tree[x].s = 1;
        tree[x].d = v;
    } else {
        int mid = (l + r) / 2;
        if (tree[tree[x].lc].s == mid - l + 1) {
            mod(tree[x].rc, tree[p].rc, mid + 1, r, v);
        } else {
            mod(tree[x].lc, tree[p].lc, l, mid, v);
        }
        update(x);
    }
}

char query(int x, int l, int r, int k) {
    if (l >= r) {
        return tree[x].d;
    }
    int mid = (l + r) / 2;
    if (k <= tree[tree[x].lc].s) {
        return query(tree[x].lc, l, mid, k);
    } else {
        return query(tree[x].rc, mid + 1, r, k - tree[tree[x].lc].s);
    }
}