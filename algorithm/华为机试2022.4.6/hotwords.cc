#include <bits/stdc++.h>

using namespace std;

#define umap unordered_map

int n, k;
int no;
vector<string> words;
umap<string, int> id; // map word to id

void process(string& line, umap<int, int>& cnt, umap<int, int>& rank) {
    int r = 0;
    int i = 0;
    while (i < line.size()) {
        while (i < line.size() && line[i] == ' ') ++i;
        int st = i;
        while (i < line.size() && line[i] != ' ') ++i;
        string w = line.substr(st, i - st);
        if (!id.count(w)) {
            id[w] = no++;
            words.push_back(w);
        }
        cnt[id[w]]++;
        if (!rank.count(id[w])) {
            rank[id[w]] = r;
        }
        ++r;
    }
}

int main() {
    cin >> n >> k;
    string line;
    getline(cin, line); // 去掉尾部的 \n

    umap<int, int> title_cnt, text_cnt, rank_1, rank_2;
    no = 0;

    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        process(line, title_cnt, rank_1);
        getline(cin, line);
        process(line, text_cnt, rank_2);
    }

    auto cmp = [&](string& s1, string& s2) {
        int i = id[s1], j = id[s2];
        int f1 = 3 * title_cnt[i] + text_cnt[i], f2 = 3 * title_cnt[j] + text_cnt[j];
        if (f1 != f2) return f1 > f2;
        else if (title_cnt[i] != title_cnt[j]) return title_cnt[i] > title_cnt[j];
        else if (text_cnt[i] != text_cnt[j]) return text_cnt[i] > text_cnt[j];
        else if (rank_1[i] != rank_1[j]) return rank_1[i] > rank_1[j];
        else return rank_2[i] > rank_2[j];
    };
    sort(words.begin(), words.end(), cmp);

    for (int i = 0; i < k; ++i) {
        cout << words[i];
        if (i != k-1) cout << " ";
        else cout << endl;
    }
    return 0;
}