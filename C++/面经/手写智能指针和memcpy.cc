#include <iostream>

using namespace std;
/*               手写智能指针                   */
template<typename T>
class SharedPtr{
private:
    T* ptr_;
    int* count_;
public:   
    SharedPtr(T* ptr) : ptr_(ptr),count_(new int(1)){}    
    //1. 拷贝构造函数
    SharedPtr(const SharedPtr<T>& p) : ptr_(p.ptr_),count_(p.count_){
        ++(*count_);
    } 
    //2. 析构函数
    ~SharedPtr(){
        if(*count_ == 1){
            delete ptr_;
            delete count_;
        }else{
            --(*count_);
        }
    }
    //3. 三个重载操作符 赋值、解引用、箭头
    SharedPtr<T>& operator=(const SharedPtr<T>& p){
        //排除自我赋值
        if(ptr_ != p.ptr_){
            if(--(*count_) == 0){    //智能指针原内存检测是否需要释放
                if(ptr_) delete ptr_;
            }else{
                ptr_ = p.ptr_;
                count_ = p.count_;
                ++(*count_);
            }
        }
        return *this;
    }
    T& operator*(){
        return *ptr_;
    }
    T* operator->(){
        return ptr_;
    }
};
/*           unique_ptr实现                      */
#include <utility>
#include <stddef.h>

template <typename T>
class Unique_ptr
{
public:
    constexpr Unique_ptr() noexcept = default;
    constexpr Unique_ptr(nullptr_t) noexcept : Unique_ptr() {}
    explicit Unique_ptr(T *ptr) noexcept : ptr_{ptr} {}
    Unique_ptr(const Unique_ptr &) = delete; // unique_ptr的特性不允许拷贝
    Unique_ptr(Unique_ptr &&rhx) noexcept : ptr_{rhx.release()} {}

    ~Unique_ptr() noexcept
    {
        delete ptr_;
    }

    Unique_ptr &operator=(const Unique_ptr &) = delete; // unique_ptr的特性不允许拷贝
    constexpr Unique_ptr &operator=(nullptr_t)
    {
        this->reset();
        return *this;
    }
    Unique_ptr &operator=(Unique_ptr &&rhx) noexcept
    {
        this->reset(rhx.release());
        return *this;
    }

    T *release() noexcept
    {
        return std::exchange(ptr_, nullptr); //返回当前指针指向地址，并置当前指针为空
    }
    T *get() const noexcept
    {
        return ptr_;
    }
    void reset(T *ptr) noexcept
    {
        delete std::exchange(ptr_, ptr); //释放当前指针指向地址内存并传入新的的地址内存
    }
    void swap(Unique_ptr &rhx) noexcept
    {
        std::swap(ptr_, rhx.ptr_);
    }

    T &operator*() const
    {
        return *ptr_;
    }
    T *operator->() const noexcept
    {
        return ptr_;
    }
    operator bool() const noexcept
    {
        return static_cast<bool>(ptr_);
    }

private:
    T *ptr_{nullptr};
};

template <typename T, typename... Args>
auto make_Unique(Args &&...args)
{
    return Unique_ptr<T>{new T(std::forward(args)...)};
}
#include <vector>

int main()
{
    Unique_ptr<std::vector<int>> ptr = make_Unique<std::vector<int>>();
    return 0;
}

/**************************************************/

/* 手写内存拷贝，从 src 复制 size 个字节大小到 dest */
void * memcpy(void * dest, const void * src, size_t size) {
    if(dest == NULL || src == NULL) {
        return  NULL;
    }
    char * pdest = (char *) dest;
    char *psrc = (char * ) src;
    //如果内存重叠，需要从后向前拷贝
    if( pdest > psrc && pdest < psrc+size) {
        pdest = pdest + size - 1;
        psrc = psrc + size - 1;
        while(size -- ) {
            *pdest-- = *psrc--;
        }
    }else {   //内存不重叠
        while(size --) {
            *pdest++ = *psrc++;
        }
    }
    return dest; 
} 
/**************************************************/
int main(int argc, char** argv){
    char res = ' ';
    if(res)cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}