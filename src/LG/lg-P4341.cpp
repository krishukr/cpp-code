#include <cstdio>
#include <iostream>

constexpr int MAX_N = 3050;

struct {
    int son[2];
    int siz;
} trie[MAX_N * MAX_N];

int cnt = 1;

void insert(const std::string& s);

void dfs(int x);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::string s;
    std::cin >> n >> s;
    for (int i = 0; i < s.length(); i++) {
        insert(s.substr(i));
    }
    dfs(1);

    return 0;
}

void insert(const std::string& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - '0';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
        trie[c].siz++;
    }
}

void dfs(int x) {
    if (trie[x].siz > 1) {
        std::cout << trie[x].siz << '\n';
    }
    for (int i = 0; i < 2; i++) {
        if (trie[x].son[i]) {
            dfs(trie[x].son[i]);
        }
    }
}
