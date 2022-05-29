#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 200050;

class Trie {
   private:
    struct Node {
        int son[32];
        bool v;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

   public:
    Trie() {
        for (int i = 0; i < 32; i++) {
            trie[cnt].son[i] = 1;
        }
        cnt++;
    }
    ~Trie() = default;

    int insert(const std::string&& s);

    void build();

    void query(const std::string&& s);
};

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int cnt;
int head[MAX_N];

void create(int u, int v);

int ed[MAX_N], sz[MAX_N];

void dfs(int x);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    auto trie = std::make_unique<Trie>();
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        ed[i] = trie->insert(std::move(s));
    }
    trie->build();
    {
        std::string s;
        std::cin >> s;
        trie->query(std::move(s));
    }
    dfs(1);

    for (int i = 1; i <= n; i++) {
        std::cout << sz[ed[i]] << '\n';
    }

    return 0;
}

int Trie::insert(const std::string&& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - 'a';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].v = true;
    return c;
}

void Trie::build() {
    std::queue<int> q;
    q.push(1);
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (trie[c].son[i]) {
                nxt[trie[c].son[i]] = trie[nxt[c]].son[i];
                q.push(trie[c].son[i]);
            } else {
                trie[c].son[i] = trie[nxt[c]].son[i];
            }
        }
    }
}

void Trie::query(const std::string&& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - 'a';
        c = trie[c].son[x];
        sz[c]++;
    }
    for (int i = 2; i <= cnt; i++) {
        create(nxt[i], i);
    }
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        dfs(v);
        sz[x] += sz[v];
    }
}