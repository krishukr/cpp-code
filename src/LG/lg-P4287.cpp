#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 1500050;

std::string d, s;
int re[MAX_N];
int n, ans;

void init();

void manacher();

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> s;

    init();
    manacher();
    std::cout << ans << '\n';

    return 0;
}

void init() {
    d.resize(2 * n + 10);
    d[0] = d[1] = 'A';
    for (int i = 0; i < n; i++) {
        d[i * 2 + 2] = s[i];
        d[i * 2 + 3] = 'A';
    }
    n = 2 * n + 2;
    d[n] = 0;
}

void manacher() {
    int r = 0, mid = 0;
    for (int l = 1; l < n; l++) {
        if (l < r) {
            re[l] = std::min(re[mid * 2 - l], re[mid] + mid - l);
        } else {
            re[l] = 1;
        }

        while (d[l + re[l]] == d[l - re[l]]) {
            re[l]++;
        }

        if (re[l] + l > r) {
            if (l & 1) {
                for (int j = std::max(r, l + 4); j < l + re[l]; j++) {
                    if (!(j - l & 3) and re[l - (j - l) / 2] > (j - l) / 2) {
                        ans = std::max(ans, j - l);
                    }
                }
            }

            r = re[l] + l;
            mid = l;
        }
    }
}