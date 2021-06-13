//未完成

#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 100010;

int tree[MAX_N][27], exi[MAX_N], nxt[MAX_N];
int tot, ans;

void init();

void bfs();

void insert(std::string s);

void search(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        init();

        int n;
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            std::string s;
            std::cin >> s;
            insert(s);
        }
        bfs();
        std::string s;
        std::cin >> s;
        search(s);
        std::cout << ans << '\n';
    }

    return 0;
}

void init() {
    memset(tree, 0, sizeof(tree));
    memset(exi, 0, sizeof(exi));
    tot = 1, ans = 0;
    for (int i = 0; i < 26; i++) {
        tree[0][i] = 1;
        tree[1][i] = 0;
    }
}

void bfs() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) {
        tree[0][i] = 0;
    }
    q.push(1);
    nxt[1] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (!tree[x][i]) {
                tree[x][i] = tree[nxt[x]][i];
            } else {
                q.push(tree[x][i]);
                nxt[tree[x][i]] = tree[nxt[x]][i];
            }
        }
    }
}

void insert(std::string s) {
    int x = 1;
    for (int i = 0; i < s.length(); i++) {
        int ch = s[i] - 'a';
        if (!tree[x][ch]) {
            tree[x][ch] = ++tot;
        }
        x = tree[x][ch];
    }
    exi[x]++;
}

void search(std::string s) {
    int x = 1;
    for (int i = 0; i < s.length(); i++) {
        int ch = s[i] - 'a';
        int j = tree[x][ch];
        while (j > 1) {
            ans += exi[j];
            exi[j] = 0;
            j = nxt[j];
        }
        x = tree[x][ch];
    }
}
