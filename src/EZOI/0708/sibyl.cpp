#include <iostream>

const int MAX_N = 300050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1], weight[MAX_N];
int cnt;

void create(int u, int v);

inline int read();

int main() {
    std::ios::sync_with_stdio(false);
    freopen("sibyl.in", "r", stdin);
    freopen("sibyl.out", "w", stdout);

    int n = read(), m = read(), q = read();
    for (int i = 0; i < m; i++) {
        int u = read(), v = read();
        create(u, v);
        create(v, u);
    }

    for (int i = 0; i < q; i++) {
        int type = read();
        if (type) {
            int x = read(), y = read();
            for (int j = head[x]; j; j = node[j].nxt) {
                weight[node[j].v] += y;
            }
        } else {
            int x = read();
            std::cout << weight[x] << '\n';
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

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