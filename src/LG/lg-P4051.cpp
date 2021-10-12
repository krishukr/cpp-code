#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 2000050;

std::string d;
int s[MAX_N];
int rnk[MAX_N], fpk[MAX_N], spk[MAX_N], cnt[MAX_N];
int n, m;

void sort();

void suffix_sort();

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> d;
    int t = d.size();
    for (int i = 0; i < t; i++) {
        s[i] = d[i];
    }
    n = 2 * t;
    for (int i = t; i < n; i++) {
        s[i] = s[i - t];
    }

    suffix_sort();

    for (int i = 1; i <= n; i++) {
        if (fpk[i] <= t) {
            std::cout << (char)s[fpk[i] + t - 2];
        }
    }

    return 0;
}

void sort() {
    for (int i = 0; i <= m; i++) {
        cnt[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        cnt[rnk[i]]++;
    }
    for (int i = 1; i <= m; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n; i > 0; i--) {
        fpk[cnt[rnk[spk[i]]]--] = spk[i];
    }
}

void suffix_sort() {
    m = 256;
    for (int i = 1; i <= n; i++) {
        rnk[i] = s[i - 1] - '0';
        spk[i] = i;
    }
    sort();

    for (int w = 1, p = 0; p < n; w *= 2) {
        p = 0;
        for (int i = 1; i <= w; i++) {
            spk[++p] = n - w + i;
        }
        for (int i = 1; i <= n; i++) {
            if (fpk[i] > w) {
                spk[++p] = fpk[i] - w;
            }
        }

        sort();
        std::swap(spk, rnk);

        rnk[fpk[1]] = p = 1;
        for (int i = 2; i <= n; i++) {
            rnk[fpk[i]] = (spk[fpk[i - 1]] == spk[fpk[i]] and
                           spk[fpk[i - 1] + w] == spk[fpk[i] + w])
                              ? p
                              : ++p;
        }

        m = p;
    }
}
