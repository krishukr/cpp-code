#include <cstdio>
#include <iostream>
#include <stack>

const int MAX_N = 50050;

struct Node {
	int v;
	int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt = 1, idx, typ;
int u[MAX_N], v[MAX_N];
bool vis[MAX_N];

int dfn[MAX_N], low[MAX_N], col[MAX_N], ind[MAX_N];
std::stack<int> stk;

void craete(int u, int v);

void tarjan(int x);

template <typename T>
T read();

int main() {
	std::ios::sync_with_stdio(false);

	int n = read<int>(), m = read<int>();
	for (int i = 1; i <= m; i++) {
		int x = read<int>(), y = read<int>();
		craete(x, y);
		craete(y, x);
		u[i] = x;
		v[i] = y;
	}

	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}

	for (int i = 1; i <= m; i++) {
		int x = u[i], y = v[i];
		if (col[x] != col[y]) {
			ind[col[x]] ++;
			ind[col[y]] ++;
		}
	}

	int ans = 0;
	for (int i = 1; i <= typ; i++) {
		if (ind[i] == 1) {
			ans ++;
		}
	}

	std::cout << ((ans + 1) >> 1) << '\n';

	return 0;
}

void craete(int u, int v) {
	node[++cnt].v = v;
	node[cnt].nxt = head[u];
	head[u] = cnt;
}

void tarjan(int x) {
	low[x] = dfn[x] = ++idx;
	stk.push(x);

	for (int i = head[x]; i; i = node[i].nxt) {
		int v = node[i].v;
		if (!vis[i]) {
			vis[i] = vis[i ^ 1] = true;	
			if (!dfn[v]) {
				tarjan(v);
				low[x] = std::min(low[x], low[v]);
			} else {
				low[x] = std::min(low[x], dfn[v]);
			}
		}
	}

    int k;
    if (low[x] == dfn[x]) {
        ++typ;
        do {
            k = stk.top();
            stk.pop();
            col[k] = typ;
        } while (x != k);
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