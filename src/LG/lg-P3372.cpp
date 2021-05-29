#include <iostream>

const int MAX_N = 100010;

long long nums[MAX_N << 2], sum[MAX_N << 2], tag[MAX_N << 2];

void create(int k, int l, int r);

void mod(int k, int l, int r, int x, int y, int c);

long long query(int k, int l, int r, int x, int y);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> nums[i];
    }
    create(1, 1, n);

    while (m--) {
        int op, x, y, k;
        std::cin >> op;

        switch (op) {
            case 1:
                std::cin >> x >> y >> k;
                mod(1, x, y, 1, n, k);
                break;
            case 2:
                std::cin >> x >> y;
                std::cout << query(1, x, y, 1, n) << "\n";
                break;
            default:
                break;
        }
    }

    return 0;
}

/*
    @param k: 当前节点位置
    @param l: 左端点
    @param r: 右端点
*/
void create(int k, int l, int r) {
    if (l == r) {
        sum[k] = nums[l];
    } else {
        int mid = (l + r) / 2;
        create(k * 2, l, mid);
        create(k * 2 + 1, mid + 1, r);
        sum[k] = sum[k * 2] + sum[k * 2 + 1];
    }
}

/*
    @param k: 当前节点位置
    @param l: 修改范围左端点
    @param r: 修改范围右端点
    @param x: 线段树左端点
    @param y: 线段树右端点
    @param c: 修改值
*/
void mod(int k, int l, int r, int x, int y, int c) {
    if (l <= x and y <= r) {
        sum[k] += (y - x + 1) * c;
        tag[k] += c;
    } else {
        int mid = (x + y) / 2;
        if (tag[k] and x != y) {
            sum[k * 2] += tag[k] * (mid - x + 1);
            sum[k * 2 + 1] += tag[k] * (y - mid);
            tag[k * 2] += tag[k];
            tag[k * 2 + 1] += tag[k];
            tag[k] = 0;
        }
        if (l <= mid) {
            mod(k * 2, l, r, x, mid, c);
        }
        if (r > mid) {
            mod(k * 2 + 1, l, r, mid + 1, y, c);
        }
        sum[k] = sum[k * 2] + sum[k * 2 + 1];
    }
}

/*
    @param k: 当前节点位置
    @param l: 查询范围左端点
    @param r: 查询范围右端点
    @param x: 线段树左端点
    @param y: 线段树右端点
*/
long long query(int k, int l, int r, int x, int y) {
    if (l <= x and y <= r) {
        return sum[k];
    }
    long long mid = (x + y) / 2;
    if (tag[k]) {
        sum[k * 2] += tag[k] * (mid - x + 1);
        sum[k * 2 + 1] += tag[k] * (y - mid);
        tag[k * 2] += tag[k];
        tag[k * 2 + 1] += tag[k];
        tag[k] = 0;
    }
    long long res = 0;
    if (l <= mid) {
        res = query(k * 2, l, r, x, mid);
    }
    if (r > mid) {
        res += query(k * 2 + 1, l, r, mid + 1, y);
    }
    return res;
}