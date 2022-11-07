#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <set>

constexpr int MAX_N = 10050;

class ODT {
    struct Node {
        int l;
        int r;
        mutable int w;

        bool operator<(const Node& x) const { return l < x.l; }
    };

    std::set<Node> s;

    std::set<ODT::Node>::iterator split(int x);

   public:
    ODT() = default;
    ODT(int n) { s.insert({1, n, 0}); }
    ~ODT() = default;

    void build(int l, int r, int w);

    int query(int l, int r);
};

int a[MAX_N], b[MAX_N];
bool vis[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        int n, mx{};
        read(n);
        for (int i = 1; i <= n; i++) {
            read(a[i], b[i]);
            mx = std::max(mx, b[i]);
        }

        std::unique_ptr<ODT> odt(new ODT(mx));
        for (int i = 1; i <= n; i++) {
            odt->build(a[i], b[i], i);
        }
        std::cout << odt->query(1, mx) << '\n';
        std::fill(vis + 1, vis + n + 1, false);
    }

    return 0;
}

std::set<ODT::Node>::iterator ODT::split(int x) {
    auto it = s.lower_bound({x, 0, 0});
    if (it != s.end() and it->l == x) {
        return it;
    } else {
        it--;
        const auto l = it->l, r = it->r, w = it->w;
        s.erase(it);
        s.insert({l, x - 1, w});
        return s.insert({x, r, w}).first;
    }
}

void ODT::build(int l, int r, int w) {
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert({l, r, w});
}

int ODT::query(int l, int r) {
    auto itr = split(r + 1), itl = split(l);
    int res{};
    while (itl != itr) {
        if (!vis[itl->w] and itl->w) {
            vis[itl->w] = true;
            res++;
        }
        itl++;
    }
    return res;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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