#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 700050;
const int MAX_M = 2050;

int tree[MAX_N][35], exi[MAX_N], nxt[MAX_N], ans[MAX_M];
int tot;
std::string s[MAX_M];

int tt[255];  // 字符映射

void init();

void build();

void insert(std::string s, int c);

void query(std::string s);

int main() {
    std::ios::sync_with_stdio(false);
    init();

    int n, m;
    std::cin >> n >> m;

    auto* nam = new std::string[n + 5];
    for (int i = 1; i <= n; i++) {
        int k;
        std::cin >> k;
        std::getline(std::cin, nam[i]);  // 还有换行符未被 cin 读入
        std::getline(std::cin, nam[i]);

        for (int j = 1; j <= k; j++) {
            std::string x;
            std::cin >> x;
            s[i] += x;  // 将每个定式当作一个字符串
        }
        insert(s[i], i);
    }
    build();

    std::string k;
    for (int i = 1; i <= m; i++) {
        std::string s;
        std::cin >> s;
        k += s;  // 同理
    }
    query(k);

    for (int i = 1; i <= n; i++) {
        if (ans[i]) {  // 出现过就输出
            std::cout << nam[i] << '\n';
        }
    }

    return 0;
}

void build() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (tree[0][i]) {
            q.push(tree[0][i]);
        }
    }
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

void init() {
    int cnt = 0;
    for (int i = '1'; i <= '8'; ++i) {
        tt[i] = ++cnt;
    }
    tt['B'] = ++cnt;
    tt['K'] = ++cnt;
    tt['N'] = ++cnt;
    tt['P'] = ++cnt;
    tt['Q'] = ++cnt;
    tt['R'] = ++cnt;
    for (int i = 'a'; i <= 'h'; ++i) {
        tt[i] = ++cnt;
    }
    tt['x'] = ++cnt;
}

void insert(std::string s, int c) {
    int x = 0;
    for (int i = 0; s[i]; i++) {
        int ch = tt[s[i]];
        if (!tree[x][ch]) {
            tree[x][ch] = ++tot;
        }
        x = tree[x][ch];
    }
    exi[x] = c;
}

void query(std::string s) {
    int x = 0;
    for (int i = 0; s[i]; i++) {
        int ch = tt[s[i]];
        x = tree[x][ch];
        for (int j = x; j; j = nxt[j]) {
            ans[exi[j]]++;
        }
    }
}