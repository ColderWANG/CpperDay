#include <bits/stdc++.h>

using namespace std;
int find_max(int i1, int i2, const vector<int>& v){
    if(i1 < 0 || i2 >= v.size() || i1 > i2)return -1;
    int maxx = 0;
    for(int i = i1; i <= i2; i++){
        if(v[i] > maxx)maxx = v[i];
    }
    return maxx;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    string s,t;
    int n;
    stringstream ss;
    vector<int> v_stu;
    getline(cin,s);
    getline(cin,s);
    ss.str(s);
    while(getline(ss,t,' ')){
        n = stoi(t);
        v_stu.push_back(n);
    }
    while(getline(cin,s)){
        string s1,s2,s3;
        int n2,n3,maxg;
        ss.clear();
        ss.str(s);
        ss >> s1 >> s2 >> s3;
        n2 = stoi(s2);
        n3 = stoi(s3);
        if(s1 == "Q"){
            maxg = find_max(n2-1, n3-1, v_stu);
            cout << maxg << endl;
        }
        else if(s1 == "U"){
            v_stu[n2-1] = n3;
        }
    }
}