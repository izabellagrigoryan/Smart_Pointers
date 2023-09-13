// Unique_Ptr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T>
struct MyDeleter 
{
    MyDeleter() = default;
    MyDeleter(const MyDeleter&) = default;

    void operator()(T* ptr) const 
    {
        std::cout << "Deleting: " << *ptr << std::endl;
        delete ptr; 
    }
};

template<class T, class Deleter = MyDeleter<T>>
class unique_ptr
{
    Deleter mydeleter = Deleter();
    T* m_ptr;
public:
    explicit unique_ptr(T* ptr) :m_ptr(ptr)
    {
        std::cout << "This is constructor" << std::endl;
    }
    unique_ptr(T* ptr, const Deleter& deleter) : m_ptr(ptr), mydeleter(deleter) {}
    ~unique_ptr() { mydeleter(m_ptr); }
    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other) noexcept
    {
        m_ptr = other;
        std::cout << "This is move constructor" << std::endl;
    }

    unique_ptr& operator=(const unique_ptr&& other) noexcept
    {
        if (this != &other) 
        {
            delete m_ptr;
            m_ptr = other;
        }
        std::cout << "This is move assignment operator" << std::endl;
        return *this;
    }

    T get_ptr()
    {
        return *m_ptr;
    }

    T* operator->()
    {
        return m_ptr;
    }

    T& operator*()
    {
        return *m_ptr;
    }

    Deleter get_deleter() const noexcept 
    { 
        return mydeleter; 
    }

    explicit operator bool() 
    { 
        return m_ptr != nullptr; 
    }

};

int main()
{
    unique_ptr<int> u_ptr(new int(5));
    std::cout << u_ptr.get_ptr() << std::endl;

    return 0;
}
