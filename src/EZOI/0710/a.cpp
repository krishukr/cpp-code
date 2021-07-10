#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 10050;

bool map[MAX_N][MAX_N];
int fa[MAX_N], a[MAX_N], b[MAX_N];

void init(int x);

int query(int x);

void merge(int i, int j);

int read();

int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    int n = read(), m = read(), cnt = 0, tot = -1;
    init(n);

    for (int i = 1; i <= m; i++) {
        int x = read(), y = read();
        map[x][y] = map[y][x] = true;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!map[i][j]) {
                merge(i, j);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            cnt++;
        }
        a[query(i)]++;
    }
    std::cout << cnt << '\n';

    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            b[++tot] = a[i];
        }
    }
    std::sort(b, b + tot + 1);
    for (int i = 0; i <= tot; i++) {
        std::cout << b[i] << ' ';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void init(int x) {
    for (int i = 1; i <= x; i++) {
        fa[i] = i;
    }
}

int query(int x) { return x == fa[x] ? x : (fa[x] = query(fa[x])); }

void merge(int i, int j) { fa[query(i)] = query(j); }

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