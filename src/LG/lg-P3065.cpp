#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

template <typename T>
using arr = std::array<T, 30>;

constexpr int MAX_N = 300050;

class Trie {
   protected:
    struct Node {
        mutable bool v;
        std::unordered_map<char, std::shared_ptr<Node>> son;
    };

    void topos(const arr<arr<bool>>&& e, arr<int>& d);

   public:
    Trie() = default;
    ~Trie() = default;

    std::shared_ptr<Node> root = std::make_shared<Node>();

    void insert(const std::string& s);

    bool query(const std::string& s);
};

std::string s[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }

    auto trie = std::make_unique<Trie>();
    for (int i = 1; i <= n; i++) {
        trie->insert(s[i]);
    }

    std::vector<std::string> ans;
    for (int i = 1; i <= n; i++) {
        if (trie->query(s[i])) {
            ans.push_back(s[i]);
        }
    }

    std::cout << ans.size() << '\n';
    std::for_each(ans.begin(), ans.end(),
                  [](const std::string& s) { std::cout << s << '\n'; });

    return 0;
}

void Trie::insert(const std::string& s) {
    auto c = root;
    std::for_each(s.begin(), s.end(), [&c](const char& i) {
        c = (c->son[i] ? c->son[i] : (c->son[i] = std::make_shared<Node>()));
    });
    c->v = true;
}

void Trie::topos(const arr<arr<bool>>&& e, arr<int>& d) {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (!d[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int p = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (e[p][i]) {
                d[i]--;
                if (!d[i]) {
                    q.push(i);
                }
            }
        }
    }
}

bool Trie::query(const std::string& s) {
    arr<arr<bool>> e{};
    arr<int> d{};

    auto c = root;
    for (const auto& i : s) {
        if (c->v) {
            return false;
        }
        for (char j = 'a'; j <= 'z'; j++) {
            if (i != j and c->son.find(j) != c->son.end() and
                !e[i - 'a'][j - 'a']) {
                e[i - 'a'][j - 'a'] = true;
                d[j - 'a']++;
            }
        }
        c = c->son[i];
    }
    topos(std::move(e), d);

    for (char i = 'a'; i <= 'z'; i++) {
        if (d[i - 'a']) {
            return false;
        }
    }
    return true;
}