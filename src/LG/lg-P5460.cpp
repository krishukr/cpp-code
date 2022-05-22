#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

constexpr int MAX_N = 100050;

struct R {
    std::string ip;
    int op;
} r[MAX_N];

struct Q {
    std::string ip;
    int idx;
} qa[MAX_N];

std::vector<int> dq[MAX_N], aq[MAX_N];
int ans[MAX_N];

class Trie {
   private:
    struct Node {
        bool v;
        int son[2];
        int t;
        int a;
    } trie[MAX_N << 5];

    void pushdown(const int& x);

   public:
    Trie() = default;
    ~Trie() = default;

    int cnt = 1;

    void mod(const std::string& s, const int& mv);

    int query(const std::string& s);
};

int main() {
    std::ios::sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::string op;
        std::cin >> op >> r[i].ip;
        r[i].op = (op[0] == 'A' ? 1 : -1);
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> qa[i].ip;
        qa[i].idx = i;

        int l, r;
        std::cin >> l >> r;
        aq[r].push_back(i);
        dq[l].push_back(i);
    }

    auto trie = std::make_unique<Trie>();
    for (int i = 1; i <= n; i++) {
        trie->mod(r[i].ip, r[i].op);
        for (const auto& j : aq[i]) {
            ans[qa[j].idx] += trie->query(qa[j].ip);
        }
        for (const auto& j : dq[i]) {
            ans[qa[j].idx] -= trie->query(qa[j].ip);
        }
    }
    for (int i = 1; i <= q; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

#define lc trie[x].son[0]
#define rc trie[x].son[1]

void Trie::pushdown(const int& x) {
    if (!lc) {
        lc = ++cnt;
    }
    if (!rc) {
        rc = ++cnt;
    }
    if (trie[x].t) {
        if (!trie[lc].v) {
            trie[lc].t += trie[x].t;
            trie[lc].a += trie[x].t;
        }
        if (!trie[rc].v) {
            trie[rc].t += trie[x].t;
            trie[rc].a += trie[x].t;
        }
        trie[x].t = 0;
    }
}

void Trie::mod(const std::string& s, const int& mv) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - '0';
        pushdown(c);
        c = trie[c].son[x];
    }
    trie[c].v += mv;
    trie[c].a += 1;
    trie[c].t += 1;
}

int Trie::query(const std::string& s) {
    int c = 1;
    for (const auto& i : s) {
        const auto x = i - '0';
        pushdown(c);
        c = trie[c].son[x];
    }
    return trie[c].a;
}

#undef lc
#undef rc