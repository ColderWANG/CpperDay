#include <bits/stdc++.h>

using namespace std;

#define maxn 5050

int m, n;
vector<int> height;

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
    height.resize(m);

    for (int i = 0; i < m; ++i) {
        height[i] = readint();
    }
    height.push_back(0);
    stack<int> st;
    st.push(-1);
    long long ans = 0;
    for (int i = 0; i < m+1; ++i) {
        while (st.top() != -1 && height[st.top()] < height[i]) {
            int h = height[st.top()]; st.pop();
            int pre = st.top();
            h -= min(pre == -1 ? 0 : height[pre], height[i]);
            if (i - pre - 1 >= n && h < 0) {
                int t = (i - pre - 1) / n;
                ans += 1ll * t * (-h);
            }
        }
        st.push(i);
    }
    cout << ans << endl;
    return 0;
}