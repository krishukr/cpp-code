#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;

std::string s[MAX_N / 10];

struct Node {
    bool m;
    bool v;
    int son[32];
} trie[MAX_N];

int cnt = 1, ans, n;
std::string as;

void insert(const std::string& s);

void solve(int k);

int main() {
    std::ios::sync_with_stdio(false);

    int m{}, p{};
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        if (m < s[i].length()) {
            m = s[i].length();
            p = i;
        }
        insert(s[i]);
    }

    {
        int c = 1;
        for (const auto& i : s[p]) {
            const auto x = i - 'a';
            c = trie[c].son[x];
            trie[c].m = true;
        }
    }

    solve(1);

    return 0;
}

void insert(const std::string& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - 'a';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].v = true;
}

void solve(int k) {
    if (trie[k].v) {
        ans++;
        as.push_back('P');
    }
    if (ans == n) {
        std::cout << as.length() << '\n';
        for (const auto& i : as) {
            std::cout << i << '\n';
        }
        return;
    }

    for (int x = 0; x < 26; x++) {
        if (trie[k].son[x] and !trie[trie[k].son[x]].m) {
            as.push_back(x + 'a');
            solve(trie[k].son[x]);
            as.push_back('-');
        }
    }

    for (int x = 0; x < 26; x++) {
        if (trie[k].son[x] and trie[trie[k].son[x]].m) {
            as.push_back(x + 'a');
            solve(trie[k].son[x]);
            as.push_back('-');
        }
    }
}