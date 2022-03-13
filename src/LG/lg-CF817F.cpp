// 居然卡过了 非常神奇
#pragma GCC optimize(3)
#pragma GCC optimize(2)

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

typedef long long ll;

template <typename T>
T read();

class ODT {
   protected:
    struct Node {
        ll l;
        ll r;
        mutable bool w;

        inline bool operator<(const Node& n) const { return l < n.l; }
    };

    std::set<Node> s;

    auto spilt(ll x) {
        auto it = s.lower_bound((Node){x, 0, 0});
        if (it != s.end() and it->l == x) {
            return it;
        }
        it--;

        auto l = it->l, r = it->r;
        auto w = it->w;
        s.erase(it);
        s.insert((Node){l, x - 1, w});
        return s.insert((Node){x, r, w}).first;
    }

   public:
    void create(ll l, ll r, bool w) { s.insert((Node){l, r, w}); }

    void build(ll l, ll r, bool w) {
        auto itr = spilt(r + 1), itl = spilt(l);
        s.erase(itl, itr);
        s.insert((Node){l, r, w});
    }

    void reverse(ll l, ll r) {
        auto itr = spilt(r + 1), itl = spilt(l);
        for (auto it = itl; it != itr; it++) {
            it->w = !(it->w);
        }
    }

    ll query() {
        for (auto i : s) {
            if (!i.w) {
                return i.l;
            }
        }
        return -1;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    auto* odt = new ODT();
    odt->create(1, 1e18 + 1, false);

    while (n--) {
        int op = read<int>();
        ll l = read<ll>(), r = read<ll>();
        switch (op) {
            case 1:
                odt->build(l, r, true);
                break;
            case 2:
                odt->build(l, r, false);
                break;
            case 3:
                odt->reverse(l, r);
                break;
        }
        std::cout << odt->query() << '\n';
    }

    return 0;
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