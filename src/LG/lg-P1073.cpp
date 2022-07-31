#include <cstdio>
#include <iostream>
#include <queue>

constexpr int MAX_N = 100050;
constexpr int MAX_M = 500050;

struct {
    int v;
    int nxt;
} node1[MAX_M << 1], node2[MAX_M << 1];

int head1[MAX_N], head2[MAX_N];
int cnt1, cnt2;

void create1(int u, int v);

void create2(int u, int v);

int v[MAX_N];
int mx[MAX_N], mn[MAX_N];
int n, m;

void spfa1();

void spfa2();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(v[i]);
    }
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        if (z == 1) {
            create1(x, y);
            create2(y, x);
        } else if (z == 2) {
            create1(x, y);
            create1(y, x);
            create2(x, y);
            create2(y, x);
        }
    }
    spfa1();
    spfa2();

    int a{};
    for (int i = 1; i <= n; i++) {
        a = std::max(a, mx[i] - mn[i]);
    }
    std::cout << a << '\n';

    return 0;
}

void create1(int u, int v) {
    node1[++cnt1].v = v;
    node1[cnt1].nxt = head1[u];
    head1[u] = cnt1;
}

void create2(int u, int v) {
    node2[++cnt2].v = v;
    node2[cnt2].nxt = head2[u];
    head2[u] = cnt2;
}

void spfa1() {
    for (int i = 1; i <= n; i++) {
        mn[i] = 0x3f3f3f3f;
    }
    std::queue<int> q;
    q.push(1);
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        mn[p] = std::min(mn[p], v[p]);
        for (int i = head1[p]; i; i = node1[i].nxt) {
            const auto vv = node1[i].v;
            if (mn[vv] > mn[p]) {
                mn[vv] = mn[p];
                q.push(vv);
            }
        }
    }
}

void spfa2() {
    std::queue<int> q;
    q.push(n);
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        mx[p] = std::max(mx[p], v[p]);
        for (int i = head2[p]; i; i = node2[i].nxt) {
            const auto vv = node2[i].v;
            if (mx[vv] < mx[p]) {
                mx[vv] = mx[p];
                q.push(vv);
            }
        }
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}