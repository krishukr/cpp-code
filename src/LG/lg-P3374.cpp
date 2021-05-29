#include <iostream>

const int MAX_N = 500010;

int c[MAX_N];
int n;

int inline low_bit(int x);

void mod(int pos, int w);

int query(int pos);

int main() {
    std::ios::sync_with_stdio(false);

    int m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        mod(i, x);
    }

    while (m--) {
        int op, x, y;
        std::cin >> op >> x >> y;
        switch (op) {
            case 1:
                mod(x, y);
                break;
            case 2:
                std::cout << query(y) - query(x - 1) << "\n";
                break;
            default:
                break;
        }
    }

    return 0;
}

int inline low_bit(int x) { return x & (-x); }

void mod(int pos, int w) {
    while (pos <= n) {
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