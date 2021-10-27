#include <bits/stdc++.h>

typedef long long ll;

struct L {
    std::string ne;
    ll bg;
    ll ed;
    ll st;
};

ll calc(ll bg, ll ed, ll sp);

const int MOD = 1e9 + 7;

int main() {
    freopen("code.in", "r", stdin);
    freopen("code.out", "w", stdout);

    std::stack<L> loop;
    std::string s;
    std::getline(std::cin, s);
    std::getline(std::cin, s);
    std::getline(std::cin, s);

    while (s.find("ans=(ans+1)%mod") == s.npos) {
        ll bg = 0, ed = 0, st = 0;
        auto *ne = new char[255];
        if (std::count(s.begin(), s.end(), ',') == 1) {
            st = 1;
            sscanf(s.data(), " for %s in range(%lld,%lld): ", ne, &bg, &ed);
        } else {
            sscanf(s.data(), " for %s in range(%lld,%lld,%lld): ", ne, &bg, &ed,
                   &st);
        }

        if (st < 0) {
            std::swap(bg, ed);
            st = -st;
        }

        loop.push((L){ne, bg, ed, st});

        std::getline(std::cin, s);
    }

    ll ans = 1;
    while (!loop.empty()) {
        auto p = loop.top();
        loop.pop();
        // printf("%s with begin at %lld end at %lld step with %lld\n",
        //        p.ne.data(), p.bg, p.ed, p.st);

        ans *= calc(p.bg, p.ed, p.st);
        ans %= MOD;
    }

    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ll calc(ll bg, ll ed, ll sp) { return std::ceil(1.0 * (ed - bg) / sp); }
