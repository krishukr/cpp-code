#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

constexpr int mp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                      0, 0, 4, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr int MAX_N = 1000050;

class Trie {
   private:
    struct Node {
        int son[5];
        bool v;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

   public:
    Trie() {
        for (int i = 0; i < 5; i++) {
            trie[0].son[i] = 1;
        }
        cnt = 1;
    }
    ~Trie() = default;

    void insert(const std::string& s);

    void build(const std::string&& s);

    int query(const std::string& s);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto trie = std::make_unique<Trie>();
    std::vector<std::string> s;
    int n, m;
    std::cin >> n >> m;
    s.resize(m);

    std::string p;
    std::cin >> p;
    for (int i = 0; i < m; i++) {
        std::cin >> s[i];
        trie->insert(s[i]);
    }
    trie->build(std::move(p));

    for (const auto& i : s) {
        std::cout << trie->query(i) << '\n';
    }

    return 0;
}

void Trie::insert(const std::string& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = mp[i];
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
}

void Trie::build(const std::string&& s) {
    {
        std::queue<int> q;
        q.push(1);
        while (!q.empty()) {
            auto c = q.front();
            q.pop();
            for (int i = 1; i <= 4; i++) {
                if (trie[c].son[i]) {
                    nxt[trie[c].son[i]] = trie[nxt[c]].son[i];
                    q.push(trie[c].son[i]);
                } else {
                    trie[c].son[i] = trie[nxt[c]].son[i];
                }
            }
        }
    }
    {
        int c = 1;
        for (const auto& i : s) {
            const auto x = mp[i];
            c = trie[c].son[x];
            for (int j = c; j; j = nxt[j]) {
                trie[j].v = true;
            }
        }
    }
}

int Trie::query(const std::string& s) {
    int c = 1, res{};
    for (int i = 0; i < s.length(); i++) {
        const auto x = mp[s[i]];
        c = trie[c].son[x];
        if (trie[c].v) {
            res = i + 1;
        } else {
            break;
        }
    }
    return res;
}