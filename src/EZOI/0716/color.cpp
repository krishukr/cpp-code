#include <cstdio>
#include <iostream>

const int MAX_N = 500000;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], min[MAX_N], max[MAX_N], size[MAX_N];
int q[MAX_N], p[MAX_N];
int cnt, n, b;

void pre(int x, int f);

void create(int u, int v);

bool dfs(int x, int f);

bool check(int x);

template <typename T>
T read();

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);

    n = read<int>();
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    int a = read<int>();
    for (int i = 1; i <= a; i++) {
        int x = read<int>(), y = read<int>();
        min[x] = std::max(min[x], y);
    }
    pre(1, 0);

    b = read<int>();
    for (int i = 1; i <= b; i++) {
        q[i] = read<int>(), p[i] = read<int>();
    }

    int l = min[1], r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid, r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void pre(int x, int f) {
    size[x] = 1;
    int tmp = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        pre(v, x);
        size[x] += size[v];
        tmp += min[v];
    }
    min[x] = std::max(min[x], tmp);
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

bool dfs(int x, int f) {
    int tmp = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }
        if (!dfs(v, x)) return false;
        tmp += max[v];
    }

    max[x] = std::min(max[x], tmp);
    if (max[x] < min[x]) {
        return false;
    } else {
        return true;
    }
}

bool check(int x) {
    for (int i = 1; i <= n; i++) {
        max[i] = size[i];
    }
    for (int i = 1; i <= b; i++) {
        max[q[i]] = std::min(max[q[i]], x - p[i]);
    }
    if (dfs(1, 0) and max[1] >= x) {
        return true;
    } else {
        return false;
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