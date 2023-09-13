// Auto_Ptr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T>
class auto_ptr
{
    T* m_ptr;
public:
    auto_ptr(T* ptr) :m_ptr(ptr)
    {
        std::cout << "This is constructor" << std::endl;
    }

    ~auto_ptr()
    {
        delete m_ptr;
        m_ptr = nullptr;
        std::cout << "This is destructor" << std::endl;
    }

    auto_ptr(auto_ptr& other) {
        m_ptr = other.release();
        std::cout << "This is copy constructor" << std::endl;
    }

    auto_ptr& operator=(const auto_ptr& other) {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.release();
        }
        std::cout << "This is operator assignment" << std::endl;
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

    T* release()
    {
        T* temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr)
    {
        if (m_ptr != p) {
            delete m_ptr;
            m_ptr = p;
        }
    }

};


int main()
{
    auto_ptr<int> a_ptr(new int(5));
    std::cout << a_ptr.get_ptr() << std::endl;
}
