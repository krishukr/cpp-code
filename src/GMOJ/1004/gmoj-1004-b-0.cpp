#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

typedef long long ll;

const int MAX_N = 500050;

ll a[MAX_N];
std::set<std::pair<int, int>> ansp;
std::vector<int> ans;

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    int l, r, m = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        l = r = i;
        while (l - 1 > 0) {
            if (!(a[l - 1] % a[i])) {
                l--;
            } else {
                break;
            }
        }
        while (r + 1 <= n) {
            if (!(a[r + 1] % a[i])) {
                r++;
            } else {
                break;
            }
        }
        m = std::max(m, r - l);
        ansp.insert(std::make_pair(l, r));
    }

    for (auto i : ansp) {
        if (i.second - i.first == m) {
            cnt++;
            ans.push_back(i.first);
        }
    }

    std::cout << cnt << ' ' << m << '\n';
    for (auto i : ans) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

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