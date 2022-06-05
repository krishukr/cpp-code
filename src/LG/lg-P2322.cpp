#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 1005;
constexpr int MAX_M = 2000050;

class Trie {
   private:
    struct Node {
        int son[32];
        int v;
    } trie[MAX_N];

    int nxt[MAX_N];
    int cnt;

    int fa[MAX_M], ans[MAX_M];
    bool vis[MAX_N][MAX_M];

   public:
    Trie() {
        for (int i = 0; i < 32; i++) {
            trie[0].son[i] = 1;
        }
        cnt = 1;
        vis[1][1] = true;
    }
    ~Trie() = default;

    void insert(const std::string&& s, const int idx);

    void build();

    std::string solve(const int n);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto trie = std::make_unique<Trie>();
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        trie->insert(std::move(s), i);
    }
    trie->build();
    std::cout << trie->solve(n) << '\n';

    return 0;
}

void Trie::insert(const std::string&& s, const int idx) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - 'A';
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].v |= (1 << idx);
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
                trie[trie[c].son[i]].v |= trie[trie[nxt[c]].son[i]].v;
                q.push(trie[c].son[i]);
            } else {
                trie[c].son[i] = trie[nxt[c]].son[i];
            }
        }
    }
}

std::string Trie::solve(const int n) {
    int x{}, tot{};
    std::queue<int> q1, q2;
    q1.push(1);
    q2.push(1);
    while (!q1.empty()) {
        const auto c = q1.front(), d = q2.front();
        q1.pop();
        q2.pop();

        if (d == ((1 << (n + 1)) - 1)) {
            std::string res;
            while (x) {
                res.push_back(ans[x] + 'A');
                x = fa[x];
            }
            std::reverse(res.begin(), res.end());
            return res;
        }

        for (int i = 0; i < 26; i++) {
            if (vis[trie[c].son[i]][d | trie[trie[c].son[i]].v]) {
                continue;
            } else {
                vis[trie[c].son[i]][d | trie[trie[c].son[i]].v] = true;
                q1.push(trie[c].son[i]);
                q2.push(d | trie[trie[c].son[i]].v);
                tot++;
                fa[tot] = x;
                ans[tot] = i;
            }
        }
        ++x;
    }
    throw std::runtime_error("No Solution");
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}