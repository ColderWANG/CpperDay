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

int lengthOfLongestSubstring(string s) {
    if(s == " ")return 1;
    else if(s.empty())return 0;
    int maxlen = 0;
    string substr;

    for(int i = 0; i < s.size(); i++){
        int index = substr.find(s[i]);
        if(index != string::npos){
            if(substr.size() > maxlen)
                maxlen = substr.size();
            substr = substr.substr(index+1);
            substr+=s[i];
        }
        else{
            substr+=s[i];
        }
    }
    if(substr.size() > maxlen)maxlen = substr.size();
    return maxlen;
}

int main(){
    string s = "abcabcbb";
    int ans = lengthOfLongestSubstring(s);
    cout << ans;
    return 0;
}