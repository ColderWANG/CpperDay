#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib> //abort()
#include <cstdio> //snprintf()
#include <ctime>
#include <algorithm> //sort() find()
#include <map>
#include <list>

#include <cstddef>
#include <memory> //内含std::allocator
#include <ext/array_allocator.h>   
#include <ext/mt_allocator.h>       //多线程
#include <ext/debug_allocator.h>    //调试
#include <ext/pool_allocator.h>     //内存池
#include <ext/bitmap_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/new_allocator.h>

using std::endl;
using std::cin;
using std::cout;
using std::string; 
using std::vector;
using std::multimap;
using std::list;

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
    void test_multimap(long& value){
        cout << "\ntest_multimap()...............\n";
    multimap<long,string> c;
    char buf[10];
    
    clock_t timeStart =clock();
        for(long i = 0; i < value; ++i){
            try{
                snprintf(buf,10,"%d",rand()/10000);
                //multimap 不可以使用[]做insertion
                c.insert(std::pair<long,string>(i,buf));    //pair函数组成对
            }
            catch(std::exception& p){
                cout << "i=" << i << " " << p.what() << endl;     
                abort();
            }
        }
        cout << "micro-seconds : " << (clock()-timeStart) << endl;
        cout << "multimap.size() = " << c.size() <<endl;
        cout << "multimap.max_size() = " << c.max_size() << endl;

    long target = get_a_target_long();
        timeStart = clock();
    auto pItem = c.find(target);
        cout << "c.find(), micro-seconds : " << (clock()-timeStart) << endl;
        if(pItem != c.end()) cout << "found, value= " << (*pItem).second << endl;  //(*pItem).second 取出 pair 的第二个元素
        else cout << "not found! " << endl;
    }
}
namespace jj20{
    void test_list_with_special_allocator(){
        cout << "\ntest_list_with_special_allocator()...";

    list<string,std::allocator<string>> c1;
    list<string,__gnu_cxx::malloc_allocator<string>> c2;
    list<string,__gnu_cxx::new_allocator<string>> c3;
    list<string,__gnu_cxx::__pool_alloc<string>> c4;
    list<string,__gnu_cxx::__mt_alloc<string>> c5;
    list<string,__gnu_cxx::bitmap_allocator<string>> c6;
    //list<string,__gnu_cxx::array_allocator<string>> c7;
    //list<string,__gnu_cxx::debug_allocator<string>> c8;
    int choice;
    long value;

        cout << "select: ";
        cin >> choice;
        if(choice != 0){
            cout << "how many elements: ";
            cin >> value;
        }

    char buf[10];
    clock_t timeStart = clock();

        for(long i = 0; i < value; ++i){
            try{
                snprintf(buf,10,"%ld",i);
                switch(choice){
                    case 1: c1.push_back(string(buf));break;
                    case 2: c2.push_back(string(buf));break;
                    case 3: c3.push_back(string(buf));break;
                    case 4: c4.push_back(string(buf));break;
                    case 5: c5.push_back(string(buf));break;
                    case 6: c6.push_back(string(buf));break;
                    //case 7: c7.push_back(string(buf));break;
                    //case 8: c8.push_back(string(buf));break;
                    default:break;
                }
            }
            catch(std::exception& p){
                cout << "i = " << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "a lot of push_back(), micro-seconds :" << (clock() - timeStart) << endl;
    }
}
int main(){
    long value = 1000000;
    //jj02::test_vector(value);
    //jj02::test_multimap(value);
    jj20::test_list_with_special_allocator();
}