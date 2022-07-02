#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 100050;

struct Node {
    bool t;
    bool v;
    bool w;
    bool l;
    int son[32];
} trie[MAX_N];

int cnt = 1;

void insert(const std::string&& s);

bool dfs1(int c);

bool dfs2(int c);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        insert(std::move(s));
    }
    dfs1(1);
    dfs2(1);

    if (trie[1].w) {
        if (trie[1].l) {
            std::cout << "First" << '\n';
        } else {
            if (k & 1) {
                std::cout << "First" << '\n';
            } else {
                std::cout << "Second" << '\n';
            }
        }
    } else {
        std::cout << "Second" << '\n';
    }

    return 0;
}

void insert(const std::string&& s) {
    int c = 1;
    for (const auto& i : s) {
        trie[c].t = true;
        const auto x = i - 'a';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].v = true;
}

bool dfs1(int c) {
    if (!trie[c].t) {
        return (trie[c].w = false);
    }
    for (int i = 0; i < 26; i++) {
        const auto& v = trie[c].son[i];
        if (v and !dfs1(v)) {
            return (trie[c].w = true);
        }
    }
    return (trie[c].w = false);
}

bool dfs2(int c) {
    if (!trie[c].t) {
        return (trie[c].l = true);
    }
    for (int i = 0; i < 26; i++) {
        const auto& v = trie[c].son[i];
        if (v and !dfs2(v)) {
            return (trie[c].l = true);
        }
    }
    return (trie[c].l = false);
}