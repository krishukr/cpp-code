#include <cstdio>
#include <iostream>
#include <memory>

#define int long long

constexpr int MAX_N = 2200050;
constexpr int MAX_L = 21;

class Trie {
   private:
    struct Node {
        int siz;
        int son[2];
        int a;
        int t;
    } trie[MAX_N << 1];

    int cnt;

    void seg_merge(const int& x);

    void pushdown(const int& x);

   public:
    Trie() = default;
    ~Trie() = default;

    int build(const int x, const int d);

    void mod(int x, int d, const int& mx, const int& my, const int& mv);

    int query(const int& r, const int& mx, const int& my);
};

int a[MAX_N];
int n, m;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

signed main() {
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    auto trie = std::make_unique<Trie>();
    const int root = trie->build(0, 0);

    int la{};
    while (m--) {
        int op, x, y;
        read(op, x, y);
        op = (op + la) % 2 + 1;
        y &= (1 << x) - 1;

        if (op == 1) {
            trie->mod(root, 0, x, y, read<int>());
        } else {
            la = trie->query(root, x, y);
            std::cout << la << '\n';
        }
    }

    return 0;
}

#define lc trie[x].son[0]
#define rc trie[x].son[1]

void Trie::seg_merge(const int& x) { trie[x].a = trie[lc].a + trie[rc].a; }

void Trie::pushdown(const int& x) {
    if (trie[x].t) {
        trie[lc].a += trie[lc].siz * trie[x].t;
        trie[lc].t += trie[x].t;
        trie[rc].a += trie[rc].siz * trie[x].t;
        trie[rc].t += trie[x].t;
        trie[x].t = 0;
    }
}

int Trie::build(const int x, const int d) {
    int c = ++cnt;
    if (d == MAX_L) {
        if (x <= n) {
            trie[c].a = a[x];
            trie[c].siz = (int)((bool)(x));
        }
        return c;
    }
    trie[c].son[0] = build(x, d + 1);
    trie[c].son[1] = build(x | (1 << d), d + 1);
    trie[c].siz = trie[trie[c].son[0]].siz + trie[trie[c].son[1]].siz;
    seg_merge(c);
    return c;
}

void Trie::mod(int x, int d, const int& mx, const int& my, const int& mv) {
    if (d >= mx) {
        trie[x].a += trie[x].siz * mv;
        trie[x].t += mv;
        return;
    }
    pushdown(x);
    mod(trie[x].son[(int)((bool)(my & (1 << d)))], d + 1, mx, my, mv);
    seg_merge(x);
}

int Trie::query(const int& r, const int& mx, const int& my) {
    int x = r;
    for (int d = 0; d < mx; d++) {
        pushdown(x);
        x = trie[x].son[(int)((bool)(my & (1 << d)))];
    }
    return trie[x].a;
}

#undef lc
#undef rc

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