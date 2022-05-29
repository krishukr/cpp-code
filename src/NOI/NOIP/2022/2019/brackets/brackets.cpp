#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 500050;

int fa[MAX_N];
int l[MAX_N];
ll f[MAX_N], g[MAX_N];

int main() {
    freopen("brackets.in", "r", stdin);
    freopen("brackets.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    for (int i = 2; i <= n; i++) {
        std::cin >> fa[i];
    }

    ll ans{};
    for (int i = 1; i <= n; i++) {
        f[i] = f[fa[i]];
        l[i] = l[fa[i]];
        if (s[i - 1] == '(') {
            l[i] = i;
        } else if (s[i - 1] == ')' and l[i]) {
            g[i] = g[fa[l[i]]] + 1;
            l[i] = l[fa[l[i]]];
            f[i] += g[i];
        }
        ans ^= (1ll * i * f[i]);
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}