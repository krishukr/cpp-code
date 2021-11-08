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
        int l;
        int r;
        mutable ll w;

        inline bool operator<(const Node &n) const { return l < n.l; }
    };

    std::set<Node> s;

    auto spilt(int x) {
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
    ODT() = default;
    ~ODT() = default;

    void create(int l, int r, ll w) { s.insert((Node){l, r, w}); }

    void build(int l, int r, ll w) {
        auto itr = spilt(r + 1), itl = spilt(l);
        s.erase(itl, itr);
        s.insert((Node){l, r, w});
    }

    void mod(int l, int r, ll v) {
        auto itr = spilt(r + 1), itl = spilt(l);
        while (itl != itr) {
            itl->w += v;
            itl++;
        }
    }

    int count(int l, int r, ll k) {
        int ans = 0;
        auto itr = spilt(r + 1), itl = spilt(l);
        while (itl != itr) {
            if (itl->w <= k) {
                ans++;
            }
            itl++;
        }
        return ans;
    }
};

const int MAX_N = 100050;
const int MOD = 998244353;

ll fact[MAX_N];

ll quick_pow(ll a, ll b);

ll combination(ll n, ll m);

int main() {
    freopen("cook.in", "r", stdin);
    freopen("cook.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    auto *odt = new ODT();
    fact[0] = 1;

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        odt->create(i, i, x);
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    while (m--) {
        int op = read<int>(), l = read<int>(), r = read<int>();
        if (op == 1) {
            int x = read<int>();
            odt->mod(l, r, x);
        } else {
            int y = read<int>(), k = read<int>();
            int x = odt->count(l, r, y);
            ll ans = 0;

            for (int i = 0; i <= k; i++) {
                if (i > x) {
                    break;
                }
                ans += combination(x, i);
                ans %= MOD;
            }
            std::cout << ans << '\n';
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll combination(ll n, ll m) {
    if (n < m) {
        return 0;
    } else {
        return fact[n] * quick_pow(fact[m], MOD - 2) % MOD *
               quick_pow(fact[n - m], MOD - 2) % MOD;
    }
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