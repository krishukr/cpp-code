#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>

using ll = __int128_t;

constexpr int MAX_N = 2000050;
constexpr ll HB = 131;

ll h2[MAX_N];

class Solution {
   private:
    int vis[31], cr[31];

    int a[MAX_N], b[MAX_N], c[MAX_N], s1[MAX_N], s2[MAX_N];
    ll h1[MAX_N];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

std::string s;

std::ostream& operator<<(std::ostream& o, const ll& x) {
    if (x < 0) {
        return (o << '-' << (-x));
    }
    if (x > 9) {
        o << (x / 10);
    }
    return (o << (int)(x % 10));
}

int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    h2[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        h2[i] = h2[i - 1] * HB;
    }

    int T;
    std::cin >> T;
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void Solution::solve() {
    std::cin >> s;
    int n = s.length();

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        c[i] = s[i - 1] - 'a' + 1;
        cr[c[i]] ^= 1;

        if (cr[c[i]]) {
            s1[i] = s1[i - 1] + 1;
        } else {
            s1[i] = s1[i - 1] - 1;
        }
        a[i] = s1[i];
    }

    memset(cr, 0, sizeof(cr));
    for (int i = n; i > 0; i--) {
        cr[c[i]] ^= 1;

        if (cr[c[i]]) {
            s2[i] = s2[i + 1] + 1;
        } else {
            s2[i] = s2[i + 1] - 1;
        }
        b[i] = s2[i];
    }

    for (int i = 1; i <= n; i++) {
        h1[i] = h1[i - 1] * HB + ll(1) * c[i];
    }

    for (int i = 2; i <= n; i++) {
        for (int j = a[i - 1]; j <= 26; j++) {
            vis[j]++;
        }
        for (int j = i; j < n and h1[i] == h1[j] - h1[j - i] * h2[i]; j += i) {
            ans += vis[b[j + 1]];
        }
    }

    std::cout << ans << '\n';
}
