#include <cstdio>
#include <iostream>
#include <queue>

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
} node[MAX_N << 2];

int head[MAX_N << 1];
int cnt;

void create(int u, int v);

int d[MAX_N << 1];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, q;
    read(n, m, q);
    std::fill(d, d + n + n + 10, 0x3f3f3f3f);
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        create(x, n + y);
        create(n + y, x);
        create(y, n + x);
        create(n + x, y);
    }

    pq<std::pair<int, int>> qu;
    d[1] = 0;
    qu.push({0, 1});
    while (!qu.empty()) {
        const auto p = qu.top().second;
        qu.pop();
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v;
            if (d[v] > d[p] + 1) {
                d[v] = d[p] + 1;
                qu.push({d[v], v});
            }
        }
    }

    while (q--) {
        int x, y;
        read(x, y);
        std::cout << (d[(y & 1) ? n + x : x] <= y ? "Yes" : "No") << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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