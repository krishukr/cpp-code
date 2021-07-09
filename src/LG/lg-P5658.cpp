#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], sta[MAX_N], fa[MAX_N];
ll f[MAX_N], sum[MAX_N], ans;
int cnt, top;
char ch[MAX_N];

void create(int u, int v);

void dfs(int x);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::cin >> (ch + 1);

    for (int i = 2; i <= n; i++) {
        int tmp;
        std::cin >> tmp;
        create(tmp, i);
        fa[i] = tmp;
    }

    dfs(1);
    for (int i = 1; i <= n; i++) {
        ans ^= sum[i] * i * 1ll;
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].nxt = head[u];
    node[cnt].v = v;
    head[u] = cnt;
}

void dfs(int x) {
    int tmp = 0;
    if (ch[x] == ')') {
        if (top) {
            tmp = sta[top];
            f[x] = f[fa[tmp]] + 1;
            top--;
        }
    } else if (ch[x] == '(') {
        sta[++top] = x;
    }
    sum[x] = sum[fa[x]] + f[x];
    for (int i = head[x]; i; i = node[i].nxt) {
        dfs(node[i].v);
    }

    if (tmp) {
        sta[++top] = tmp;
    } else if (top) {
        top--;
    }
}