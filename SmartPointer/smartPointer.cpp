//
//  main.cpp
//  20190323
//
//  Copyright
//  https://www.cnblogs.com/wxquare/p/4759020.html
//  unique_ptr“唯一”拥有其所指对象，同一时刻只能有一个unique_ptr指向给定对象（通过禁止拷贝语义、只有移动语义来实现）。
//  weak_ptr是为了配合shared_ptr而引入的一种智能指针，因为它不具有普通指针的行为，没有重载operator*和->,它的最大作用在于协助shared_ptr工作，像旁观者那样观测资源的使用情况。
//  weak_ptr可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。但weak_ptr没有共享资源，它的构造不会引起指针引用计数的增加。
//  使用weak_ptr的成员函数use_count()可以观测资源的引用计数，另一个成员函数expired()的功能等价于use_count()==0,但更快，表示被观测的资源(也就是shared_ptr的管理的资源)已经不复存在。
//  weak_ptr可以使用一个非常重要的成员函数lock()从被观测的shared_ptr获得一个可用的shared_ptr对象， 从而操作资源。
//  但当expired()==true的时候，lock()函数将返回一个存储空指针的shared_ptr。

//  shared_ptr多个指针指向相同的对象。shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。
//  每使用他一次，内部的引用计数加1，每析构一次，内部的引用计数减1，减为0时，自动删除所指向的堆内存。

#include <iostream>
#include <memory>
using namespace std;

template<typename T>
class SmartPointer {
private:
    T* _ptr;
    size_t* _count;
public:
    SmartPointer(T* ptr = nullptr) :_ptr(ptr) {
        if (_ptr) {
            _count = new size_t(1);
        } else {
            _count = new size_t(0);
        }
    }
    
    SmartPointer(const SmartPointer& ptr) {
        if (this != &ptr) {
            this->_ptr = ptr._ptr;
            this->_count = ptr._count;
            (*this->_count)++;
        }
    }
    
    SmartPointer& operator=(const SmartPointer& ptr) {
        if (this->_ptr == ptr._ptr) {
            return *this;
        }
        
        if (this->_ptr) {
            (*this->_count)--;
            if (this->_count == 0) {
                delete this->_ptr;
                delete this->_count;
            }
        }
        
        this->_ptr = ptr._ptr;
        this->_count = ptr._count;
        (*this->_count)++;
        return *this;
    }
    
    T& operator*() {
        assert(this->_ptr == nullptr);
        return *(this->_ptr);
        
    }
    
    T* operator->() {
        assert(this->_ptr == nullptr);
        return this->_ptr;
    }
    
    ~SmartPointer() {
        --*(this->_count);
        if (*(this->_count) == 0) {
            delete this->_ptr;
            delete this->_count;
        }
    }
    
    size_t use_count(){
        return *this->_count;
    }
};

int testSmartPointer() {
    SmartPointer<int> sp(new int(10));
    SmartPointer<int> sp2(sp);
    SmartPointer<int> sp3(new int(20));
    sp2 = sp3;
    std::cout << sp.use_count() << std::endl;
    std::cout << sp3.use_count() << std::endl;
    return 0;
}

int test2(){
    std::shared_ptr<int> sh_ptr = std::make_shared<int>(10);
    std::cout << sh_ptr.use_count() << std::endl;
    
    std::shared_ptr<int> wp2(sh_ptr);
    std::cout << sh_ptr.use_count() << std::endl;
    
    std::weak_ptr<int> wp(sh_ptr);
    std::cout << wp.use_count() << std::endl;
    
    if(!wp.expired()){
        std::cout << "inside" << std::endl;
        std::shared_ptr<int> sh_ptr2 = wp.lock(); //get another shared_ptr
        *sh_ptr = 100;
        std::cout << wp.use_count() << std::endl;
        std::cout << wp.lock().use_count() << std::endl;
        std::cout << sh_ptr.use_count() << std::endl;
        sh_ptr2.reset();
        std::cout << "outside" << std::endl;
    }
    std::cout << wp.use_count() << std::endl;
    return 0;
}

class Child;
class Parent;

class Parent {
private:
    //std::shared_ptr<Child> ChildPtr;
    std::weak_ptr<Child> ChildPtr;
public:
    void setChild(std::shared_ptr<Child> child) {
        this->ChildPtr = child;
    }
    
    void doSomething() {
        //new shared_ptr
        if (this->ChildPtr.lock()) {
            
        }
    }
    
    ~Parent() {
    }
};

class Child {
private:
    std::shared_ptr<Parent> ParentPtr;
public:
    void setPartent(std::shared_ptr<Parent> parent) {
        this->ParentPtr = parent;
    }
    void doSomething() {
        if (this->ParentPtr.use_count()) {
            
        }
    }
    ~Child() {
    }
};

int main() {
    std::weak_ptr<Parent> wpp;
    std::weak_ptr<Child> wpc;
    {
        std::shared_ptr<Parent> p(new Parent);
        std::shared_ptr<Child> c(new Child);
        p->setChild(c);
        c->setPartent(p);
        wpp = p;
        wpc = c;
        std::cout << p.use_count() << std::endl; // 2
        std::cout << c.use_count() << std::endl; // 1
    }
    std::cout << wpp.use_count() << std::endl;  // 0
    std::cout << wpc.use_count() << std::endl;  // 0
    return 0;
}

