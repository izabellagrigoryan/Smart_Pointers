// Shared_Ptr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

template <typename T>
class shared_ptr
{
    class CB
    {
        T* m_ptr = nullptr;
        unsigned int* count = nullptr;
    public:
        CB(T* ptr)
        {
            m_ptr = new T();
            m_ptr = ptr;
            count = new unsigned int(0);
            increment();
        }

        void increment()
        {
            (*count)++;
        }

        void decrement()
        {
            (*count)--;
        }

        void set_count(unsigned int c)
        {
            *count = c;
        }

        unsigned int get_count() const
        {
            return *count;
        }

        void set(T* ptr)
        {
            m_ptr = ptr;
        }

        T* get() const
        {
            return this->m_ptr;
        }

        void deleter()
        {
            delete count;
        }
    };

    CB* m_cb;

public:
    
    explicit shared_ptr(T& obj)
    {
        m_cb = new CB(obj);
        m_cb->set(obj);
    }

    explicit shared_ptr(T* obj)
    {
        m_cb = new CB(obj);
    }
    
    //copy constructor
    shared_ptr(const shared_ptr& obj)
    {
        m_cb = obj.m_cb;
        T* ptr = obj.m_cb->get();
        this->m_cb->set(ptr);
        unsigned int c = obj.m_cb->get_count();
        this->m_cb->set_count(c);
        if (nullptr != obj.m_cb->get())
        {
            // if the pointer is not null, increment the count
            this->m_cb->increment();
        }
    }

    // copy assignment
    shared_ptr& operator=(const shared_ptr& obj)
    {
        m_cb = obj.m_cb;
        T* ptr = obj.m_cb->get();
        this->m_cb->set(ptr);
        unsigned int c = obj.m_cb->get_count();
        this->m_cb->set_count(c);
        if (nullptr != obj.m_cb->get())
        {
            this->m_cb->increment();
        }
    }

    // move constructor
    shared_ptr(shared_ptr&& obj)
    {
        T* ptr = obj.m_cb->get();
        this->m_cb->set(ptr);
        unsigned int c = obj.m_cb->get_count();
        this->m_cb->set_count(c);
        obj.m_cb->set(nullptr);
        obj.m_cb->set_count(nullptr);
    }

    // move assignment
    shared_ptr& operator=(shared_ptr&& obj)
    {
        T* ptr = obj.m_cb->get();
        this->m_cb->set(ptr);
        unsigned int c = obj.m_cb->get_count();
        this->m_cb->set_count(c);
        obj.m_cb->set(nullptr);
        obj.m_cb->set_count(nullptr);
    }

    T* operator->() const
    {
        return this->m_cb->get();
    }

    T& operator*() const
    {
        return this->m_cb->get();
    }

    unsigned int get_count() const
    {
        unsigned int c = this->m_cb->get_count();
        return c;
    }

    T* get() const
    {
        return this->m_ptr;
    }

    ~shared_ptr() // destructor
    {
        clean();
    }

private:
    void clean()
    {
        m_cb->decrement();
        if (m_cb->get_count() == 0)
        {
            if (nullptr != m_cb->get())
                delete m_cb->get();
            m_cb->deleter();
        }
    }
};

class Box
{
public:
    int length, width, height;
    Box(int length, int width, int height) : length(length), width(width), height(height) {}
    Box() {}
};

int main()
{
    shared_ptr<Box> box(new Box(5, 5, 5));
    std::cout << box.get_count() << std::endl;
    shared_ptr<Box> box1(box);
    std::cout << box1.get_count() << std::endl; 
    shared_ptr<Box> box2(box1);
    std::cout << box1.get_count() << std::endl; 
    std::cout << box2.get_count() << std::endl; 


    shared_ptr<Box> box3(std::move(new Box(6, 6, 6)));
    std::cout << box3.get_count() << std::endl;
    std::cout << box2.get_count() << std::endl;

    return 0;
}
