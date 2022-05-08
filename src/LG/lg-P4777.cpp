#include <cstdio>
#include <iostream>
#include <memory>

using ll = __int128_t;

class EXCRT {
   private:
    int n;
    std::unique_ptr<ll[]> a, b;

   protected:
    ll ex_gcd(ll a, ll b, ll& x, ll& y);

   public:
    EXCRT() = default;
    EXCRT(const int n, std::unique_ptr<ll[]> a, std::unique_ptr<ll[]> b) {
        this->n = n;
        this->a = std::move(a);
        this->b = std::move(b);
    }
    ~EXCRT() = default;

    ll ex_crt();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

std::ostream& operator<<(std::ostream& o, const ll& a) {
    if (a < 0) {
        return (o << '-' << (-a));
    }
    if (a > 9) {
        o << (a / 10);
    }
    return (o << (int)(a % 10));
}

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    auto a = std::make_unique<ll[]>(n + 10), b = std::make_unique<ll[]>(n + 10);
    for (int i = 1; i <= n; i++) {
        read(a[i], b[i]);
    }

    auto solution = std::make_unique<EXCRT>(n, std::move(a), std::move(b));
    std::cout << solution->ex_crt() << '\n';

    return 0;
}

ll EXCRT::ex_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll ans = ex_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return ans;
}

ll EXCRT::ex_crt() {
    ll a1 = a[1], b1 = b[1];
    for (int i = 2; i <= n; i++) {
        ll a2 = a[i], b2 = b[i];
        ll A, B, C = b2 - b1;
        ll G = ex_gcd(a1, a2, A, B);
        A = ((A * C / G) % (a2 / G) + (a2 / G)) % (a2 / G);
        b1 += A * a1;
        a1 = a1 * a2 / G;
    }
    return b1;
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