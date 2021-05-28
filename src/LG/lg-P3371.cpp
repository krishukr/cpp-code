#include <iostream>

using namespace std;

const int MAX_N = 10001;
const int MAX_M = 500001;
int from[MAX_M], to[MAX_M], cost[MAX_M];
long long dis[MAX_N];

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        cin >> from[i] >> to[i] >> cost[i];
    }
    for (int i = 1; i <= n; i++) {
        dis[i] = 2147483647;
    }
    dis[s] = 0;
    bool flag;
    for (int i = 1; i < n; i++) {
        flag = false;
        for (int j = 1; j <= m; j++) {
            if (dis[to[j]] > dis[from[j]] + cost[j]) {
                dis[to[j]] = dis[from[j]] + cost[j];
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << " ";
    }

    return 0;
}