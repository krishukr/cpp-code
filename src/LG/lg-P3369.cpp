#include <climits>
#include <cstdlib>
#include <iostream>

const int MAX_N = 100010;

struct Node {
    int ch[2];
    int cnt;
    int val;
    int son;
    int pri;
} tree[MAX_N];

int tot, root;

#pragma region init
void build();

int create(int x);

void upd(int x);

void rotate(int &x, int d);

void insert(int &x, int v);

void remove(int &x, int v);

int query_rank(int x, int v);

int query_val(int x, int v);

int query_pre(int v);

int query_nxt(int v);
#pragma endregion init

int main() {
    std::ios::sync_with_stdio(false);

    build();
    int n;
    std::cin >> n;

    while (n--) {
        int op, x;
        std::cin >> op >> x;
        switch (op) {
            case 1:
                insert(root, x);
                break;
            case 2:
                remove(root, x);
                break;
            case 3:
                std::cout << query_rank(root, x) - 1 << '\n';
                break;
            case 4:
                std::cout << query_val(root, x + 1) << '\n';
                break;
            case 5:
                std::cout << query_pre(x) << '\n';
                break;
            case 6:
                std::cout << query_nxt(x) << '\n';
                break;
            default:
                break;
        }
    }

    return 0;
}

void build() {
    root = create(INT_MIN);
    tree[root].ch[1] = create(INT_MAX);
    upd(root);
}

int create(int x) {
    tree[++tot].val = x;
    tree[tot].pri = rand();
    tree[tot].son = 1;
    tree[tot].cnt = 1;
    return tot;
}

void upd(int x) {
    tree[x].son =
        tree[tree[x].ch[0]].son + tree[tree[x].ch[1]].son + tree[x].cnt;
}

void rotate(int &x, int d) {
    int tmp = tree[x].ch[d ^ 1];
    tree[x].ch[d ^ 1] = tree[tmp].ch[d];
    tree[tmp].ch[d] = x;
    x = tmp;
    upd(tree[x].ch[d]);
    upd(x);
}

void insert(int &x, int v) {
    if (!x) {
        x = create(v);
        return;
    }
    if (v == tree[x].val) {
        tree[x].cnt++;
    } else {
        int dir = v < tree[x].val ? 0 : 1;
        insert(tree[x].ch[dir], v);
        if (tree[x].pri < tree[tree[x].ch[dir]].pri) {
            rotate(x, dir ^ 1);
        }
    }
    upd(x);
}

void remove(int &x, int v) {
    if (!x) {
        return;
    }
    if (v == tree[x].val) {
        if (tree[x].cnt > 1) {
            tree[x].cnt--;
            upd(x);
            return;
        }
        if (tree[x].ch[0] or tree[x].ch[1]) {
            if (!tree[x].ch[1] or
                tree[tree[x].ch[0]].pri > tree[tree[x].ch[1]].pri) {
                rotate(x, 1);
                remove(tree[x].ch[1], v);
            } else {
                rotate(x, 0);
                remove(tree[x].ch[0], v);
            }
            upd(x);
        } else {
            x = 0;
        }
        return;
    }
    v < tree[x].val ? remove(tree[x].ch[0], v) : remove(tree[x].ch[1], v);
    upd(x);
}

int query_rank(int x, int v) {
    if (!x) {
        return -2;
    }
    if (v == tree[x].val) {
        return tree[tree[x].ch[0]].son + 1;
    } else if (v < tree[x].val) {
        return query_rank(tree[x].ch[0], v);
    } else {
        return tree[tree[x].ch[0]].son + tree[x].cnt +
               query_rank(tree[x].ch[1], v);
    }
}

int query_val(int x, int v) {
    if (!x) {
        return INT_MAX;
    }
    if (v <= tree[tree[x].ch[0]].son) {
        return query_val(tree[x].ch[0], v);
    } else if (v <= tree[tree[x].ch[0]].son + tree[x].cnt) {
        return tree[x].val;
    } else {
        return query_val(tree[x].ch[1],
                         v - tree[tree[x].ch[0]].son - tree[x].cnt);
    }
}

int query_pre(int v) {
    int x = root, pre;
    while (x) {
        if (tree[x].val < v) {
            pre = tree[x].val;
            x = tree[x].ch[1];
        } else {
            x = tree[x].ch[0];
        }
    }
    return pre;
}

int query_nxt(int v) {
    int x = root, nxt;
    while (x) {
        if (tree[x].val > v) {
            nxt = tree[x].val;
            x = tree[x].ch[0];
        } else {
            x = tree[x].ch[1];
        }
    }
    return nxt;
}