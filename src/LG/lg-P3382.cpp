#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-9;

int n;
double a[14];

double sum(double x);

int main() {
    double l, r, k;
    cin >> n >> l >> r;
    for (int i = n; i >= 0; i--) {
        cin >> a[i];
    }
    while (r - l >= eps) {
        k = (r - l) / 3.0;
        double p1 = l + k, p2 = r - k;
        sum(p1) > sum(p2) ? (r = p2) : (l = p1);
    }
    cout << l;

    return 0;
}

double sum(double x) {
    double s = 0;
    for (int i = n; i >= 0; i--) {
        s = s * x + a[i];
    }

    return s;
}