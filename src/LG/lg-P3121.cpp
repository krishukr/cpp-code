#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

constexpr int MAX_N = 100050;

class Trie {
   private:
    struct Node {
        int son[32];
        int d;
    } trie[MAX_N];

    int cnt;
    int nxt[MAX_N], l[MAX_N];

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

    std::string query(const std::string&& s);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto trie = std::make_unique<Trie>();
    std::string s;
    std::cin >> s;
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string t;
        std::cin >> t;
        trie->insert(std::move(t));
    }
    trie->build();
    std::cout << trie->query(std::move(s)) << '\n';

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
}

std::string Trie::query(const std::string&& s) {
    std::vector<int> stk;
    int c = 1;
    for (int i = 0; i < s.length(); i++) {
        const auto x = s[i] - 'a';
        l[i] = c = trie[c].son[x];
        stk.push_back(i);
        if (trie[c].d) {
            for (int j = 0; j < trie[c].d; j++) {
                stk.pop_back();
            }
            c = l[*(stk.rbegin())];
        }
    }
    std::string res;
    res.reserve(s.length());
    for (const auto& i : stk) {
        res.push_back(s[i]);
    }
    return res;
}