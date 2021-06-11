#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib> //abort()
#include <cstdio> //snprintf()
#include <ctime>
#include <algorithm> //sort()
using std::endl;
using std::cin;
using std::cout;
using std::string; 
using std::vector;
long get_a_target_long(){
long target = 0;

    cout << "target (0~" << RAND_MAX/10000 << "):";
    cin >> target;
    return target;
}
string get_a_target_string(){
long target;
char buf[10];

    cout << "target (0~" << RAND_MAX/10000 << "):";
    cin >> target;
    snprintf(buf,10,"%ld",target);
    return string(buf);
}
int compareLongs(const void* a,const void* b){
    return (*(long*)a - *(long*)b);
}
int compareStrings(const void* a,const void* b){
    if(*(string*)a > *(string*)b)return 1;
    else if(*(string*)a < *(string*)b) return -1;
    else return 0;
}
namespace jj02{
    void test_vector(long& value){
        cout << "\ntest_vector()..........\n";
    
    vector<string> c;
    char buf[10];
    clock_t timeStart =clock();
        for(long i = 0; i < value; ++i){
            try{
                snprintf(buf,10,"%d",rand()/10000);
                c.push_back(string(buf));
            }
            catch(std::exception& p){
                cout << "i=" << i << " " << p.what() << endl;
                        
                abort();
            }
        }
        cout << "mill-seconds: " << (clock() - timeStart) << endl;
        cout << "vector.size() = " << c.size() << endl;
        cout << "vector.front() = " << c.front() << endl;
        cout << "vector.back() = " << c.back() << endl;
        cout << "vector.data() = " << c.data() << endl;
        cout << "vector.capacity = " << c.capacity() << endl;
    
    string target = get_a_target_string();
        {
        timeStart = clock();
    auto pItem = std::find(c.begin(),c.end(),target);  //循序查找
        cout << "std::find(), micro-seconds : " << (clock()-timeStart) << endl;          //一个clock大约是1us
        cout << "std::find(), seconds : " << (double)(clock()-timeStart)/CLOCKS_PER_SEC << endl;
        if(pItem != c.end()) cout << "found, " << *pItem << endl;
        else cout << "not found!" << endl;
        }
        {
        timeStart = clock();
        sort(c.begin(),c.end());
    string* pItem = (string*)bsearch(&target,(c.data()),c.size(),sizeof(string),compareStrings);  //二分查找
        cout << "sort() + bsearch(), micro-seconds : " << (clock()-timeStart) << endl;
        cout << "sort() + bsearch(), seconds : " << (double)(clock()-timeStart)/CLOCKS_PER_SEC << endl;
        if(pItem != NULL)cout << "found, " << *pItem << endl;
        else cout << "not found!" << endl;
        }
    }
    
}

int main(){
    long value = 1000000;
    jj02::test_vector(value);
}