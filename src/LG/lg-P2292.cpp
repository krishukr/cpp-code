#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 505;
constexpr int MAX_T = 2000050;

class Trie {
   private:
    struct Node {
        int son[32];
        int d;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

    int f[MAX_T], g[MAX_T];

   public:
    Trie() {
        for (int i = 0; i < 32; i++) {
            trie[cnt].son[i] = 1;
        }
        cnt++;
    }
    ~Trie() = default;

    void insert(const std::string&& s);

    void build();

    int query(const std::string&& s);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    auto trie = std::make_unique<Trie>();
    while (n--) {
        std::string s;
        std::cin >> s;
        trie->insert(std::move(s));
    }
    trie->build();
    while (m--) {
        std::string s;
        std::cin >> s;
        std::cout << trie->query(std::move(s)) << '\n';
    }

    return 0;
}

void Trie::insert(const std::string&& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - 'a';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].d = s.length();
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
    for (int c = 1; c <= cnt; c++) {
        for (int i = c; i; i = nxt[i]) {
            if (trie[i].d > 0 and trie[i].d <= 10) {
                g[c] |= (1 << (trie[i].d - 1));
            }
        }
    }
    f[0] = 1;
}

int Trie::query(const std::string&& s) {
    int c = 1, y{};
    for (int i = 1; i <= s.length(); i++) {
        const auto x = s[i - 1] - 'a';
        c = trie[c].son[x];
        y = ((y << 1) | f[i - 1]) & ((1 << 10) - 1);
        f[i] = (int)((bool)(y & g[c]));
    }
    for (int i = s.length(); i >= 1; i--) {
        if (f[i]) {
            return i;
        }
    }
    return 0;
}