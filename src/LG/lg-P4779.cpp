#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200010;

int total, from[MAX_N], to[MAX_N], nxt[MAX_N], cost[MAX_N];
int dis[MAX_N];

bool vis[MAX_N];

priority_queue<pair<int, int> > q;

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        to[++total] = y;
        cost[total] = c;
        nxt[total] = from[x];
        from[x] = total;
    }
    for (int i = 1; i <= n; i++) {
        dis[i] = INT_MAX;
    }
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int t = q.top().second;
        q.pop();
        if (vis[t]) {
            continue;
        }
        vis[t] = true;
        for (int i = from[t]; i; i = nxt[i]) {
            int x = to[i], w = cost[i];
            if (dis[x] > dis[t] + w) {
                dis[x] = dis[t] + w;
                q.push(make_pair(-dis[x], x));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << dis[i + 1] << " ";
    }

    return 0;
}