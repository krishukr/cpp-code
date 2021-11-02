#include <cstdio>
#include <iostream>

const int MAX_N = 505;

struct Node {
    int x;
    int y;
    Node *t;  // top
    Node *b;  // bottom
    Node *l;  // left
    Node *r;  // right
} node[MAX_N * MAX_N], row[MAX_N], col[MAX_N], head;

int cnt, n, m;
int siz[MAX_N], ans[MAX_N];

void init(int x, int y);

void insert(int x, int y);

inline void delTB(Node *p);
inline void delLR(Node *p);
inline void falTB(Node *p);
inline void falLR(Node *p);

void cov(int y);
void fal(int y);

bool dance(int k);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    init(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = read<int>();
            if (x) {
                insert(i, j);
            }
        }
    }

    if (dance(0)) {
        std::cout << "No Solution!\n";
    }

    return 0;
}

void init(int x, int y) {
    head.x = x;
    head.y = y;
    head.t = head.b = head.l = head.r = &head;

    for (int i = x - 1; i >= 0; i--) {
        row[i].x = i;
        row[i].y = y;
        row[i].t = &head;
        row[i].b = head.b;
        row[i].t->b = row[i].b->t = &row[i];
        row[i].l = row[i].r = &row[i];
    }

    for (int i = 0; i < y; i++) {
        col[i].y = i;
        col[i].x = x;
        col[i].l = &head;
        col[i].r = head.r;
        col[i].l->r = col[i].r->l = &col[i];
        col[i].t = col[i].b = &col[i];
    }
}

void insert(int x, int y) {
    cnt++;
    node[cnt].x = x;
    node[cnt].y = y;

    node[cnt].l = row[x].l;
    node[cnt].r = &row[x];
    node[cnt].l->r = node[cnt].r->l = &node[cnt];

    node[cnt].t = &col[y];
    node[cnt].b = col[y].b;
    node[cnt].t->b = node[cnt].b->t = &node[cnt];
    siz[y]++;
}

inline void delTB(Node *p) {
    p->t->b = p->b;
    p->b->t = p->t;
}

inline void delLR(Node *p) {
    p->l->r = p->r;
    p->r->l = p->l;
}

inline void falTB(Node *p) { p->t->b = p->b->t = p; }

inline void falLR(Node *p) { p->l->r = p->r->l = p; }

void cov(int y) {
    if (y == m) {
        return;
    }
    delLR(&col[y]);

    for (Node *i = col[y].b; i != &col[y]; i = i->b) {
        if (i->y == m) {
            continue;
        }
        for (Node *j = i->l; j != i; j = j->l) {
            if (j->y == m) {
                continue;
            }
            delTB(j);
            siz[j->y]--;
        }
        delLR(i);
    }
}

void fal(int y) {
    if (y == m) {
        return;
    }

    for (Node *i = col[y].t; i != &col[y]; i = i->t) {
        if (i->y == m) {
            continue;
        }
        falLR(i);
        for (Node *j = i->r; j != i; j = j->r) {
            if (j->y == m) {
                continue;
            }
            falTB(j);
            siz[j->y]++;
        }
    }
    falLR(&col[y]);
}

bool dance(int k) {
    if (head.l == &head) {
        for (int i = 0; i < k; i++) {
            std::cout << ans[i] << ' ';
        }
        return false;
    }

    int min = 0x3f3f3f3f, idx;
    for (Node *i = head.l; i != &head; i = i->l) {
        if (siz[i->y] < min) {
            min = siz[i->y];
            idx = i->y;
        }
    }
    cov(idx);

    for (Node *i = col[idx].b; i != &col[idx]; i = i->b) {
        i->r->l = i;
        for (Node *j = i->l; j != i; j = j->l) {
            cov(j->y);
        }
        i->r->l = i->l;

        ans[k] = i->x + 1;
        if (!dance(k + 1)) {
            return false;
        }

        i->l->r = i;
        for (Node *j = i->r; j != i; j = j->r) {
            fal(j->y);
        }
        i->l->r = i->r;
    }
    fal(idx);
    return true;
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