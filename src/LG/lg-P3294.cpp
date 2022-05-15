#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 510050;

struct Node {
    int w;
    int son[32];
} trie[MAX_N];

int cnt = 1;

void insert(const std::string&& s, const int idx);

int f[MAX_N];

inline int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }

int dfn[MAX_N], siz[MAX_N];
int crt;
long long ans;
std::vector<int> G[MAX_N];

void build(int x);

void dfs1(int x);

void dfs2(int x);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        insert(std::move(s), i);
    }
    for (int i = 1; i <= cnt + 10; i++) {
        f[i] = i;
    }

    build(1);
    dfs1(0);
    dfs2(0);

    std::cout << ans << '\n';

    return 0;
}

void insert(const std::string&& s, const int idx) {
    int c = 1;
    for (auto it = s.rbegin(); it != s.rend(); it++) {
        const auto i = *it - 'a';
        c = (trie[c].son[i] ? trie[c].son[i] : (trie[c].son[i] = ++cnt));
    }
    trie[c].w = idx;
}

void build(int x) {
    for (int i = 0; i < 26; i++) {
        const int& v = trie[x].son[i];
        if (v) {
            if (trie[v].w) {
                G[trie[find(x)].w].push_back(trie[v].w);
            } else {
                f[v] = find(x);
            }
            build(v);
        }
    }
}

void dfs1(int x) {
    siz[x] = 1;
    for (const auto& v : G[x]) {
        dfs1(v);
        siz[x] += siz[v];
    }
    std::sort(G[x].begin(), G[x].end(),
              [](const int& i, const int& j) { return siz[i] < siz[j]; });
}

void dfs2(int x) {
    dfn[x] = crt++;
    for (const auto& v : G[x]) {
        ans += crt - dfn[x];
        dfs2(v);
    }
}