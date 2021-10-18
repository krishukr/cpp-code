#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

typedef long long ll;

template <typename T>
T read();

class Random {
   private:
    ll seed;

   public:
    Random(ll s) { this->seed = s; }

    ll rand(ll m) {
        ll res = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return res % m + 1;
    }
};

class ODT {
   protected:
    struct Node {
        ll l;
        ll r;
        mutable ll w;

        inline bool operator<(const Node &n) const { return l < n.l; }
    };

    std::set<Node> s;

    ll quick_pow(ll a, ll b, ll p) {
        a %= p;
        ll res = 1;
        while (b) {
            if (b & 1) {
                res = res * a % p;
            }
            a = a * a % p;
            b >>= 1;
        }
        return res;
    }

    auto spilt(ll x) {
        auto it = s.lower_bound((Node){x, 0, 0});
        if (it != s.end() and it->l == x) {
            return it;
        }
        it--;

        auto l = it->l, r = it->r, w = it->w;
        s.erase(it);
        s.insert((Node){l, x - 1, w});
        return s.insert((Node){x, r, w}).first;
    }

   public:
    void create(ll l, ll r, ll w) { s.insert((Node){l, r, w}); }

    void build(ll l, ll r, ll w) {
        auto itr = spilt(r + 1), itl = spilt(l);
        s.erase(itl, itr);
        s.insert((Node){l, r, w});
    }

    void mod(ll l, ll r, ll v) {
        auto itr = spilt(r + 1), itl = spilt(l);
        while (itl != itr) {
            itl->w += v;
            itl++;
        }
    }

    ll kth(ll l, ll r, ll k) {
        std::vector<std::pair<ll, ll>> res;
        auto itr = spilt(r + 1), itl = spilt(l);

        while (itl != itr) {
            res.push_back(std::make_pair(itl->w, itl->r - itl->l + 1));
            itl++;
        }
        std::sort(res.begin(), res.end());

        for (auto i : res) {
            k -= i.second;
            if (k <= 0) {
                return i.first;
            }
        }
        return -1;
    }

    ll sum(ll l, ll r, ll x, ll y) {
        ll res = 0;
        auto itr = spilt(r + 1), itl = spilt(l);

        while (itl != itr) {
            res += (itl->r - itl->l + 1) % y * quick_pow(itl->w, x, y) % y;
            res %= y;
            itl++;
        }

        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    ll n = read<ll>(), m = read<ll>(), seed = read<ll>(), vm = read<ll>();
    auto *random = new Random(seed);
    auto *odt = new ODT();

    for (int i = 1; i <= n; i++) {
        ll x = random->rand(vm);
        odt->create(i, i, x);
    }

    while (m--) {
        int op = random->rand(4);
        ll l = random->rand(n), r = random->rand(n), x, y;
        if (l > r) {
            std::swap(l, r);
        }

        if (op == 3) {
            x = random->rand(r - l + 1);
        } else {
            x = random->rand(vm);
        }

        if (op == 4) {
            y = random->rand(vm);
        }

        if (op == 1) {
            odt->mod(l, r, x);
        }
        if (op == 2) {
            odt->build(l, r, x);
        }
        if (op == 3) {
            std::cout << odt->kth(l, r, x) << '\n';
        }
        if (op == 4) {
            std::cout << odt->sum(l, r, x, y) << '\n';
        }
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