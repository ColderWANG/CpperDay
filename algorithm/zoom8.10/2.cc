#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int tot, ptot;
map<string, int> name;// 公司name
map<string, int> pname;// 人name
map<int, int> mp;
int fa[N], sz[N];
int getfa(int u){
    return fa[u] != u ? fa[u] = getfa(fa[u]) : u;
}
void join(int u,int v){
    int f1 = getfa(u), f2 = getfa(v);
    if(f1 != f2){
        fa[f2] = fa[f1];
        sz[f1] += sz[f2];
        sz[f2] = 0;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;
    int type, m;
    string in, bu;
    tot = q;
    for(int i = 1; i <= q; i++){
        cin >> type;
        if(type == 1){
            cin >> in >> m;
            int thisroot = i;
            pname[in] = thisroot;
            fa[thisroot] = thisroot;
            sz[thisroot] = 0;
            vector<int> tonari;
            
            for(int i = 0; i < m; i++){
                cin >> bu;
                if(name.find(bu) == name.end()){         //股票第一次出现，在并查集中注册节点，节点的父节点是自己，大小是1，哈希索引是 ++tot
                    name[bu] = ++tot;
                    fa[name[bu]] = name[bu];
                    sz[name[bu]] = 1;
                }
                tonari.push_back(name[bu]);
                join(thisroot, name[bu]);
            }
            mp[thisroot] = tonari.size();
        }else{
            cin >> in;
            if(pname.find(in) == pname.end()){
                cout<<"error\n";
                continue;
            }
            int pid = pname[in];
            int total = sz[getfa(pid)];
            int tonari = mp[pid];
            cout<<total - tonari<<"\n";
        }
    }
}
/*
5
1 Alice 2
Zoom Apple
2 Bob
2 Alice
1 Bob 2
Apple Microsoft
2 Bob
*/