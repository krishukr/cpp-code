#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 100050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], oud[MAX_N];
bool vis[MAX_N];
int cnt;

struct cmp {
    bool operator()(const int x, const int y) const { return oud[x] < oud[y]; }
};

void create(int u, int v);

template <typename T>
T read();

int main() {
    freopen("ddl.in", "r", stdin);
    freopen("ddl.out", "w", stdout);

    int n = read<int>(), m = read<int>();

    if (m != 1) {
        std::cout << "FUCK!!\n";
        return 0;
    }

    for (int i = 2; i <= n; i++) {
        int x = read<int>();
        create(x, i);
    }

    std::priority_queue<int, std::vector<int>, cmp> q;
    std::vector<int> res;
    q.push(1);
    vis[1] = true;

    while (!q.empty()) {
        int h = q.top();
        q.pop();
        vis[h] = true;
        res.push_back(h);

        for (int i = head[h]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (vis[v]) {
                continue;
            }

            q.push(v);
            vis[v] = true;
        }
    }

    std::cout << res.size() << '\n';

    for (int i = 0; i < res.size(); i++) {
        std::cout << i + 1 << ' ' << res[i] << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
    oud[u]++;
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