#include <cstdio>
#include <iostream>

typedef long long ll;

template <typename T>
T read();

class Basis {
   private:
    typedef long long ll;

    const static int SIZE = 55;

   protected:
    ll p[SIZE];

   public:
    void insert(ll x) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (!p[i]) {
                    p[i] = x;
                    return;
                } else {
                    x ^= p[i];
                }
            }
        }
    }

    ll query() {
        ll ans = 0;
        for (int i = SIZE - 1; i >= 0; i--) {
            ans = std::max(ans, ans ^ p[i]);
        }
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    Basis* basis = new Basis();

    for (int i = 1; i <= n; i++) {
        ll x = read<ll>();
        basis->insert(x);
    }

    std::cout << basis->query() << '\n';

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
};