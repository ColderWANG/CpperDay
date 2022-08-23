### floyd算法
多源有权图最短路径算法
核心思想就是
1. 根据起点终点建立邻接矩阵，G[a][b], 每个元素代表 a 到 b 的距离，对角元为0，其他为正无穷
2. 枚举中间点 k ,如果 G[a][k] + G[k][b] < G[a][b] 则更新 G[a][b]，说明走这个中间点路径短
```cpp
void floyd(){
    for()
}
```
```cpp
//lc 399 除法求职
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_set<string> S;
        unordered_map<string, unordered_map<string, double>> g;
        for (int i = 0; i < equations.size(); i ++ )
        {
            auto a = equations[i][0], b = equations[i][1];
            auto c = values[i];
            g[a][b] = c;
            g[b][a] = 1.0 / c;
            S.insert(a);
            S.insert(b);
        }
        for (auto k: S)    // Floyd算法的核心：先枚举中间点，利用中间点来更新左右点的距离
        {
            for (auto i: S)
            {
                for (auto j: S)
                {
                    if (g[i][k] && g[j][k])
                        g[i][j] = g[i][k] * g[k][j];
                }
            }
        }
        vector<double> res;
        for (auto t: queries)
        {
            auto a = t[0], b = t[1];
            if (g[a][b])
                res.push_back(g[a][b]);
            else
                res.push_back(-1);
        }
        return res;
    }
};
```