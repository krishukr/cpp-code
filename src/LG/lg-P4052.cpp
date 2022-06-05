#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 10050;
constexpr int MOD = 10007;

class Trie {
   private:
    struct Node {
        int son[32];
        bool v;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

    int f[150][MAX_N];

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

    int query(int m);
};

template <typename T>
T quick_pow(T a, T b);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto trie = std::make_unique<Trie>();
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        trie->insert(std::move(s));
    }
    trie->build();
    std::cout << trie->query(m) << '\n';

    return 0;
}

void Trie::insert(const std::string&& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - 'A';
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
        for (int i = 0; i < 26; i++) {
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

int Trie::query(int m) {
    f[0][1] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= cnt; j++) {
            for (int k = 0; k < 26; k++) {
                if (!trie[trie[j].son[k]].v) {
                    f[i + 1][trie[j].son[k]] += f[i][j];
                    f[i + 1][trie[j].son[k]] %= MOD;
                }
            }
        }
    }
    int r = quick_pow(26, m);
    for (int i = 1; i <= cnt; i++) {
        r = (r - f[m][i] + MOD) % MOD;
    }
    return r;
}

template <typename T>
T quick_pow(T a, T b) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}