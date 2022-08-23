#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
vector<int> mp[N];
int cred[N], cblue[N], n;
string color;
ll ans;
void dfs(int u,int fa){
    cred[u] = cred[fa];
    cblue[u] = cblue[fa];
    if(color[u] == 'R'){
        cred[u]++;
    }else{
        cblue[u]++;
    }
    // cout<<u<<" "<<cred[u]<<" "<<cblue[u]<<endl;
    ans += abs(cred[u] - cblue[u]);
    for(auto v:mp[u]){
        if(v == fa) continue;
        dfs(v, u);
    }
    return;
}
int main() {
    cin >> n >> color;
    //color = " "+color;
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }
    dfs(1,0);
    cout<<ans<<endl;
}