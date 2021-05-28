#include <iostream>

const int MAX_N = 500010;

long long nums[MAX_N], sum[MAX_N << 2];

void create(int k, int l, int r);

void mod(int k, int l, int r, int x, int y, int c);

long long query(int k, int l, int r, int p);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> nums[i];
    }

    while (m--) {
        int op, x, y, k;
        std::cin >> op;

        switch (op) {
            case 1:
                std::cin >> x >> y >> k;
                mod(1, 1, n, x, y, k);
                break;
            case 2:
                std::cin >> x;
                std::cout << query(1, 1, n, x) << '\n';
                break;
            default:
                break;
        }
    }

    return 0;
}

void create(int k, int l, int r) {
    if (l == r) {
        sum[k] = nums[l];
    } else {
        int mid = (l + r) / 2;
        create(k * 2, l, mid);
        create(k * 2 + 1, mid + 1, r);
        sum[k] = 0;
    }
}

void mod(int k, int l, int r, int x, int y, int c) {
    if (l > y or r < x) {
        return;
    }
    if (l >= x and r <= y) {
        sum[k] += c;
    } else {
        int mid = (l + r) / 2;
        mod(k * 2, l, mid, x, y, c);
        mod(k * 2 + 1, mid + 1, r, x, y, c);
    }
}

long long query(int k, int l, int r, int p) {
    if (l == r) {
        return sum[k];
    } else {
        int mid = (l + r) / 2;
        if (p <= mid) {
            return query(k * 2, l, mid, p) + sum[k];
        } else {
            return query(k * 2 + 1, mid + 1, r, p) + sum[k];
        }
    }
}