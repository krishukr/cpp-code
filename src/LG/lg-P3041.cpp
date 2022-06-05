#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 2050;

class Trie {
   private:
    struct Node {
        int son[32];
        int v;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

    int f[MAX_N][MAX_N];

   public:
    Trie() {
        for (int i = 0; i < 32; i++) {
            trie[0].son[i] = 1;
        }
        cnt = 1;
    }
    ~Trie() = default;

    void insert(const std::string&& s);

    void build();

    int solve(const int k);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto trie = std::make_unique<Trie>();
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        trie->insert(std::move(s));
    }
    trie->build();
    std::cout << trie->solve(k) << '\n';

    return 0;
}

void Trie::insert(const std::string&& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - 'A';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].v = 1;
}

void Trie::build() {
    std::queue<int> q;
    q.push(1);
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        for (int i = 0; i < 3; i++) {
            if (trie[c].son[i]) {
                nxt[trie[c].son[i]] = trie[nxt[c]].son[i];
                q.push(trie[c].son[i]);
            } else {
                trie[c].son[i] = trie[nxt[c]].son[i];
            }
        }
        trie[c].v += trie[nxt[c]].v;
    }
}

int Trie::solve(const int k) {
    memset(f, 0xaf, sizeof(f));
    for (int i = 0; i <= k; i++) {
        f[i][0] = f[i][1] = 0;
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= cnt; j++) {
            for (int k = 0; k < 3; k++) {
                const int v = trie[j].son[k];
                f[i][v] = std::max(f[i][v], f[i - 1][j] + trie[v].v);
            }
        }
    }
    int ans{};
    for (int i = 1; i <= cnt; i++) {
        ans = std::max(ans, f[k][i]);
    }
    return ans;
}