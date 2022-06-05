#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 1550;
constexpr int MOD = 1e9 + 7;

class Trie {
   private:
    std::string n;

    struct Node {
        int son[16];
        bool v;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

    int f[MAX_N][MAX_N][2][2];
    bool vis[MAX_N][MAX_N][2][2];

   public:
    Trie(std::string n) {
        for (int i = 0; i < 16; i++) {
            trie[0].son[i] = 1;
        }
        cnt = 1;
        this->n = n;
    }
    ~Trie() = default;

    void insert(const std::string&& s);

    void build();

    int dfs(int x, int c, bool l, bool b);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string n;
    std::cin >> n;
    int m;
    std::cin >> m;
    auto trie = std::make_unique<Trie>(n);
    for (int i = 1; i <= m; i++) {
        std::string s;
        std::cin >> s;
        trie->insert(std::move(s));
    }
    trie->build();
    std::cout << (trie->dfs(0, 1, true, true) - 1 + MOD) % MOD << '\n';

    return 0;
}

void Trie::insert(const std::string&& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - '0';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].v = true;
}

void Trie::build() {
    std::queue<int> q;
    q.push(1);
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        for (int i = 0; i < 10; i++) {
            if (trie[c].son[i]) {
                nxt[trie[c].son[i]] = trie[nxt[c]].son[i];
                q.push(trie[c].son[i]);
                if (trie[nxt[trie[c].son[i]]].v) {
                    trie[trie[c].son[i]].v = true;
                }
            } else {
                trie[c].son[i] = trie[nxt[c]].son[i];
            }
        }
    }
}

int Trie::dfs(int x, int c, bool l, bool b) {
    if (x >= n.length()) {
        return (int)(!trie[c].v);
    }
    if (trie[c].v) {
        return 0;
    }
    if (vis[x][c][l][b]) {
        return f[x][c][l][b];
    }
    vis[x][c][l][b] = true;

    const int w = (l ? (n[x] - '0') : 9);
    int res{};
    for (int i = 0; i <= w; i++) {
        res += dfs(x + 1, (b and (i == 0) ? 1 : trie[c].son[i]),
                   (l and (n[x] - '0' == i)), (b and (i == 0)));
        res %= MOD;
    }
    return f[x][c][l][b] = res;
}