#include <bits/stdc++.h>

constexpr int MAX_N = 1000050;

int v[MAX_N];

int tree[MAX_N][2];
int siz[MAX_N];

void dfs(int x);

bool check(int a, int b);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(v[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(tree[i][0], tree[i][1]);
    }
    dfs(1);

    int ans{};
    for (int i = 1; i <= n; i++) {
        if (check(tree[i][0], tree[i][1])) {
            ans = std::max(ans, siz[i]);
        }
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

#define lc tree[x][0]
#define rc tree[x][1]

void dfs(int x) {
    siz[x] = 1;
    if (lc != -1) {
        dfs(lc);
        siz[x] += siz[lc];
    }
    if (rc != -1) {
        dfs(rc);
        siz[x] += siz[rc];
    }
}

#undef lc
#undef rc

bool check(int a, int b) {
    if (a == -1 and b == -1) {
        return true;
    }
    return (a != -1 and b != -1 and siz[a] == siz[b] and v[a] == v[b] and
            check(tree[a][1], tree[b][0]) and check(tree[a][0], tree[b][1]));
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