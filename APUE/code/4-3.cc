#include <iostream>
#include <apue.h>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]){
    struct stat buf;
    int i;
    string ptr;
    for(i = 1; i < argc; i++){
        cout << argv[i] << ":";
        if(lstat(argv[i],&buf) < 0){
            cout << "lstat error!" << endl;
            continue;
        }
        if(S_ISREG(buf.st_mode))
            ptr = "regular";
        else if(S_ISDIR(buf.st_mode))
            ptr = "directory";
        else if(S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if(S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if(S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if(S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if(S_ISSOCK(buf.st_mode))
            ptr = "socket";
        else
            ptr = "** unknown mode **";
        cout << ptr << endl;
    }
    return 0;
}