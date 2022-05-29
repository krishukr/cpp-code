#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 600050;
constexpr int MAX_L = 23;

class Trie {
   private:
    struct Node {
        int son[2];
        int m;
    } trie[MAX_N << 5];

   public:
    Trie() {
        root[0] = ++cnt;
        insert(0, root[0], 0, MAX_L);
        trie[0].m = -1;
    }
    ~Trie() = default;

    int cnt;
    int root[MAX_N];

    void insert(const int& p, const int& c, const int& d, const int k);

    int query(const int& o, const int& v, const int& k);
};

int s[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    auto trie = std::make_unique<Trie>();

    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        s[i] = s[i - 1] ^ x;
        trie->root[i] = ++(trie->cnt);
        trie->insert(trie->root[i - 1], trie->root[i], i, MAX_L);
    }

    while (m--) {
        char op = getchar();
        while (op != 'A' and op != 'Q') {
            op = getchar();
        }
        if (op == 'A') {
            int x;
            read(x);
            n++;
            s[n] = s[n - 1] ^ x;
            trie->root[n] = ++(trie->cnt);
            trie->insert(trie->root[n - 1], trie->root[n], n, MAX_L);
        } else if (op == 'Q') {
            int l, r, x;
            read(l, r, x);
            std::cout << trie->query(trie->root[r - 1], x ^ s[n], l - 1)
                      << '\n';
        }
    }

    return 0;
}

void Trie::insert(const int& p, const int& c, const int& d, const int k) {
    if (k < 0) {
        trie[c].m = d;
        return;
    }
    const int x = (s[d] >> k) & 1;
    if (p) {
        trie[c].son[x ^ 1] = trie[p].son[x ^ 1];
    }
    trie[c].son[x] = ++cnt;
    insert(trie[p].son[x], trie[c].son[x], d, k - 1);
    trie[c].m = std::max(trie[trie[c].son[0]].m, trie[trie[c].son[1]].m);
}

int Trie::query(const int& o, const int& v, const int& k) {
    int c = o;
    for (int i = MAX_L; i >= 0; i--) {
        const int x = (v >> i) & 1;
        if (trie[trie[c].son[x ^ 1]].m >= k) {
            c = trie[c].son[x ^ 1];
        } else {
            c = trie[c].son[x];
        }
    }
    return v ^ s[trie[c].m];
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