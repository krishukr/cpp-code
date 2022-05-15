#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 300050;

struct Node {
    bool w;
    int son[32];
} trie[MAX_N];

int cnt = 1;

void insert(const std::string&& s);

bool vis[MAX_N];
bool flag;
int ans;

void dfs(int x, int l, bool t, const std::string& s);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        insert(std::move(s));
    }

    for (int i = 1; i <= m; i++) {
        std::string s;
        std::cin >> s;
        dfs(1, 0, false, s);

        std::cout << (flag ? -1 : ans) << '\n';

        flag = false;
        ans = 0;
        std::fill_n(vis, cnt + 10, false);
    }

    return 0;
}

void insert(const std::string&& s) {
    int c = 1;
    for (const auto& it : s) {
        const auto i = it - 'a';
        c = (trie[c].son[i] ? trie[c].son[i] : (trie[c].son[i] = ++cnt));
    }
    trie[c].w = true;
}

void dfs(int x, int l, bool t, const std::string& s) {
    if (flag) {
        return;
    }
    if (l == s.length() and trie[x].w and !t) {
        flag = true;
        return;
    }
    if (l == s.length() and trie[x].w and t) {
        ans += !vis[x];
        vis[x] = true;
        return;
    }

    if (!t) {
        if (l < s.length()) {
            dfs(x, l + 1, true, s);
        }
        for (int i = 0; i < 26; i++) {
            if (trie[x].son[i]) {
                dfs(trie[x].son[i], l, true, s);
                if (i != s[l] - 'a') {
                    dfs(trie[x].son[i], l + 1, true, s);
                }
            }
        }
    }
    if (l >= s.length()) {
        return;
    }
    if (trie[x].son[s[l] - 'a']) {
        dfs(trie[x].son[s[l] - 'a'], l + 1, t, s);
    }
}
