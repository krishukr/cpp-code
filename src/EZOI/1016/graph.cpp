#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 2000050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N];
int cnt, n, m;

std::string dis[MAX_N];
bool vis[MAX_N];

void create(int u, int v, int w);

bool cmp(std::string &a, std::string b);

void spfa();

template <typename T>
T read();

int main() {
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
    }

    spfa();
    std::string res = dis[n];
    while (!res.empty()) {
        if (*(res.begin()) == '1') {
            break;
        }
        res.erase(res.begin());
    }
    if (res.empty()) {
        res = "0";
    }

    std::cout << res << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

bool cmp(std::string &a, std::string b) {
    while (!a.empty()) {
        if (*(a.begin()) == '1') {
            break;
        }
        a.erase(a.begin());
    }
    while (!b.empty()) {
        if (*(b.begin()) == '1') {
            break;
        }
        b.erase(b.begin());
    }
    return a > b;
}

void spfa() {
    std::string tmp;
    for (int i = 0; i <= m; i++) {
        tmp += '1';
    }
    std::fill(dis, dis + m + 10, tmp);

    std::queue<int> q;
    q.push(1);
    dis[1] = "";

    while (!q.empty()) {
        int p = q.front();
        q.pop();
        vis[p] = false;

        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v;
            char w = node[i].w + '0';

            if (cmp(dis[v], dis[p] + w)) {
                dis[v] = dis[p] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
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