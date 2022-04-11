#include <cstdio>
#include <iostream>
#include <map>

constexpr int MAX_N = 100050;

struct Node {
    int p;
    int l;
    int r;
} tree[MAX_N];

bool vis[MAX_N];
std::map<int, bool> mp;

void dfs(int x, int l, int r);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(tree[i].p, tree[i].l, tree[i].r);
        (tree[i].l == -1 ?: vis[tree[i].l] = 1);
        (tree[i].r == -1 ?: vis[tree[i].r] = 1);
    }

    int root;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            root = i;
        }
    }

    int ans = 0;
    dfs(root, -1, 0x3f3f3f3f);
    for (int i = 1; i <= n; i++) {
        if (!mp[tree[i].p]) {
            ans++;
        }
    }
    std::cout << ans << '\n';

    return 0;
}

void dfs(int x, int l, int r) {
    if (x == -1) {
        return;
    }
    if (l < tree[x].p and tree[x].p < r) {
        mp[tree[x].p] = true;
    }
    dfs(tree[x].l, l, std::min(r, tree[x].p));
    dfs(tree[x].r, std::max(l, tree[x].p), r);
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