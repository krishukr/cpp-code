#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll a, b;

int main() {
    cin >> a >> b;
    if (a < b) swap(a, b);
    cout << int(b != int((sqrt(5.0) + 1.0) / 2.0 * (double)(a - b)));

    return 0;
}