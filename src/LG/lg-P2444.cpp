#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 30050;

class Trie {
   private:
    struct Node {
        int son[2];
        bool v;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

    bool ins[MAX_N], vis[MAX_N];

   public:
    Trie() {
        for (int i = 0; i < 2; i++) {
            trie[cnt].son[i] = 1;
        }
        cnt++;
    }
    ~Trie() = default;

    void insert(const std::string&& s);

    void build();

    bool dfs(int x);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto trie = std::make_unique<Trie>();
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        trie->insert(std::move(s));
    }
    trie->build();
    std::cout << (trie->dfs(1) ? "TAK" : "NIE") << '\n';

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
        for (int i = 0; i < 2; i++) {
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

bool Trie::dfs(int x) {
    ins[x] = true;
    for (int i = 0; i < 2; i++) {
        int v = trie[x].son[i];
        if (ins[v]) {
            return true;
        }
        if (vis[v] or trie[v].v) {
            continue;
        }
        vis[v] = true;
        if (dfs(v)) {
            return true;
        }
    }
    ins[x] = false;
    return false;
}