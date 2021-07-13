#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int lc;       // 左儿子
    int rc;       // 右儿子
    int s;        // 被完全覆盖次数
    long long l;  // 被截长度
} tree[MAX_N * 2];

struct Line {
    long long l;  // 左端点
    long long r;  // 右端点
    long long h;  // 高度
    int p;        // 权重

    bool operator<(const Line &a) const { return h < a.h; }
} line[MAX_N * 4];

int poi[MAX_N * 2];

#pragma region initial
void create(int x, int l, int r);

void update(int x);

void mod(int x, long long l, long long r, int v);

template <typename T>
T read();
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x1 = read<int>(), y1 = read<int>(), x2 = read<int>(),
            y2 = read<int>();
        poi[2 * i - 1] = x1;
        poi[2 * i] = x2;
        line[2 * i - 1] = (Line){x1, x2, y1, 1};
        line[2 * i] = (Line){x1, x2, y2, -1};
    }
    n *= 2;

    std::sort(line + 1, line + n + 1);
    std::sort(poi + 1, poi + n + 1);
    int tot = std::unique(poi + 1, poi + n + 1) - poi - 1;
    create(1, 1, tot - 1);

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        mod(1, line[i].l, line[i].r, line[i].p);
        ans += tree[1].l * (line[i + 1].h - line[i].h);
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int x, int l, int r) {
    tree[x].lc = l;
    tree[x].rc = r;
    tree[x].l = 0;
    tree[x].s = 0;

    if (l == r) {
        return;
    } else {
        int mid = (l + r) / 2;
        create(x * 2, l, mid);
        create(x * 2 + 1, mid + 1, r);
    }
}

void update(int x) {
    if (tree[x].s) {
        tree[x].l = poi[tree[x].rc + 1] - poi[tree[x].lc];
    } else {
        tree[x].l = tree[2 * x].l + tree[2 * x + 1].l;
    }
}

void mod(int x, long long l, long long r, int v) {
    if (poi[tree[x].rc + 1] <= l or r <= poi[tree[x].lc]) {
        return;
    }
    if (l <= poi[tree[x].lc] and poi[tree[x].rc + 1] <= r) {
        tree[x].s += v;
        update(x);
    } else {
        mod(x * 2, l, r, v);
        mod(x * 2 + 1, l, r, v);
        update(x);
    }
}

template <typename T>
T read() {
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