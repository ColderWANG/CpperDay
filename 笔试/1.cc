#include <bits/stdc++.h>

using namespace std;

// s 给定，inow-1 表示字符串中当前位置， path 路径，side 邻接表, cnt 表示计数
void dfs(const string& s, int inow, string &path, unordered_map<int,vector<int>> side, int cnt){
    if(path.size() == 3){
        if((path[0] != path[1]) && (path[1] == path[2]))cnt++;
        return;
    }
    vector<int> next = side[inow];
    for(int i = ; i <= next.size(); ++i){
        path += next[]
    }
}

int main(){
    int n;
    unordered_map<int,vector<int>> side;
    string s;
    cin >> n >> s;
    for(int i = 0; i < n; ++i){
        int x,y;
        cin >> x >> y;
        side[x].push_back(y);
        side[y].push_back(x);
    }
    string path;
    int res = 0;
    for(int i = 1; i <= s.size(); ++i){
        path += s[i-1];
        dfs(s,i,path,side,res);
        path.erase(path.end()-1);
    }
    return 0;
}