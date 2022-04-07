#include <bits/stdc++.h>

using namespace std;

#define maxn 5050

int m, n;
vector<int> g[maxn];
vector<int> ans;
int vis[maxn];
bool open(int x) {
    if (vis[x] == 1) return true;
    else if (vis[x] == -1) return false;
    vis[x] = -1;
    for (auto to : g[x]) {
        if (!open(to)) return false;
    }

    if (x != m) ans.push_back(x);
    vis[x] = 1;
    return true;
}

int readint() {
    int sn = 1;
    char ch = getchar();
    while (!(isdigit(ch) || ch == '-')) ch = getchar();
    int ret = 0;
    if (ch == '-') sn = -1;
    else ret = ch - '0';
    while (isdigit(ch = getchar())) {
        ret = ret * 10 + ch - '0';
    }
    return sn * ret;
}

int main() {
    n = readint(), m = readint();
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i) {
        int num = readint();
        int rely;
        for (int j = 0; j < num; ++j) {
            rely = readint();
            g[i].push_back(rely);
        }
    }

    if (!open(m)) {
        cout << "-1" << endl;
    } else if (ans.empty()) {
        cout << "null" << endl;
    } else {
        for (auto e : ans) {
            cout << e;
            if (e != ans.back()) cout << ",";
            else cout << endl;
        }
    }

    return 0;
}