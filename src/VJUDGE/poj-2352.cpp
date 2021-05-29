#include <cstring>
#include <iostream>

const int MAX_N = 32010;

int c[MAX_N], ans[MAX_N];
int n;

int inline low_bit(int x);

void mod(int pos, int w);

int query(int pos);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        ans[query(++x)]++;
        mod(x, 1);
    }
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}

int inline low_bit(int x) { return x & (-x); }

void mod(int pos, int w) {
    while (pos <= MAX_N) {
        c[pos] += w;
        pos += low_bit(pos);
    }
}

int query(int pos) {
    int ans = 0;
    while (pos >= 1) {
        ans += c[pos];
        pos -= low_bit(pos);
    }
    return ans;
}