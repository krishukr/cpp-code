#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

constexpr int MAX_N = 100050;

struct Node {
    char c;
    int lc;
    int rc;
    int x;
    int a;
} tree[MAX_N << 3];

int cnt;
std::stack<int> stk;

int get_node(char c, int lc, int rc, int x);

char s[1000050];
int x[MAX_N], ans[MAX_N];

int dfs1(int x);

void dfs2(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("expr.in", "r", stdin);
    freopen("expr.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    fgets(s + 1, 1000005, stdin);
    const int m = strlen(s + 1);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(x[i]);
    }

    for (int i = 1; i <= m; i++) {
        if (s[i] == ' ') {
            continue;
        }
        if (s[i] == 'x') {
            i++;
            int f{};
            while (isdigit(s[i])) {
                f = f * 10 + s[i] - 48;
                i++;
            }
            stk.push(get_node(x[f], 0, 0, f));
        } else if (s[i] == '&' or s[i] == '|') {
            auto p1 = stk.top();
            stk.pop();
            auto p2 = stk.top();
            stk.pop();
            stk.push(get_node(s[i], p1, p2, 0));
        } else if (s[i] == '!') {
            auto p = stk.top();
            stk.pop();
            stk.push(get_node(s[i], p, 0, 0));
        }
    }

    dfs1(stk.top());
    dfs2(stk.top());

    int q;
    read(q);
    while (q--) {
        int x;
        read(x);
        std::cout << (ans[x] ? !(tree[stk.top()].a) : tree[stk.top()].a)
                  << '\n';
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

int get_node(char c, int lc, int rc, int x) {
    tree[++cnt] = {c, lc, rc, x, 0};
    return cnt;
}

int dfs1(int x) {
    if (tree[x].c == 0 or tree[x].c == 1) {
        return (tree[x].a = tree[x].c);
    } else if (tree[x].c == '&') {
        return (tree[x].a = (dfs1(tree[x].lc) & dfs1(tree[x].rc)));
    } else if (tree[x].c == '|') {
        return (tree[x].a = (dfs1(tree[x].lc) | dfs1(tree[x].rc)));
    } else {
        return (tree[x].a = !dfs1(tree[x].lc));
    }
}

void dfs2(int x) {
    if (tree[x].c == 0 or tree[x].c == 1) {
        ans[tree[x].x] = 1;
        return;
    }
    auto la = tree[tree[x].lc].a, ra{0};
    if (tree[x].rc) {
        ra = tree[tree[x].rc].a;
    }
    if (tree[x].c == '&') {
        if (la) {
            dfs2(tree[x].rc);
        }
        if (ra) {
            dfs2(tree[x].lc);
        }
    } else if (tree[x].c == '|') {
        if (!la) {
            dfs2(tree[x].rc);
        }
        if (!ra) {
            dfs2(tree[x].lc);
        }
    } else {
        dfs2(tree[x].lc);
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