#ifndef ILRD_RD61_SHARED_PTR_HPP
#define ILRD_RD61_SHARED_PTR_HPP

#include <cstddef> //size_t

namespace ilrd
{
template <typename T> 
class SharedPtr
{
public:    
    explicit SharedPtr(T *const ptr = NULL);
    SharedPtr(const SharedPtr& other);
    ~SharedPtr();

    template <typename D>
    SharedPtr(const SharedPtr<D>& other); 

    template <typename D>
    SharedPtr<T>& operator=(const SharedPtr<D>& other); 

    template <typename D, typename U> 
    friend bool operator==(const SharedPtr<U>& sp, const SharedPtr<D>& other);

    template <typename D> 
    friend class SharedPtr;
    
    template <typename U> 
    friend class SharedPtr;

    SharedPtr& operator=(const SharedPtr& other);
    T& operator*() const; 
    T* operator->() const;  
    bool operator!=(const SharedPtr& other) const;
    operator bool() const;
    T& GetPtr() const;
    size_t GetCount() const;
        
private:
    void DealWithLastRef();
    template <typename D>
    SharedPtr& AssignmentConv(const SharedPtr<D>& other);

    T *m_ptr;
    size_t *m_count;
};

template <typename T>
template <typename D>
SharedPtr<T>::SharedPtr(const SharedPtr<D>& other) 
:m_ptr(other.m_ptr), m_count(other.m_count)
{
    __sync_add_and_fetch((size_t *)m_count, 1);
}

template <typename T>
SharedPtr<T>::SharedPtr(T *const ptr)
: m_ptr(ptr), m_count(new size_t(1))
{}

template <typename T>
void SharedPtr<T>::DealWithLastRef()
{
    if (0 == *m_count)
    {
        delete m_ptr;
        delete m_count;
    }
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    __sync_sub_and_fetch((size_t *)m_count, 1);
    DealWithLastRef();
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other)
: m_ptr(other.m_ptr), m_count(other.m_count)
{
    __sync_add_and_fetch((size_t *)m_count, 1);
}

template <typename T>
template <typename D>
SharedPtr<T>& SharedPtr<T>::AssignmentConv(const SharedPtr<D>& other)
{
    __sync_sub_and_fetch((size_t *)m_count, 1);
    __sync_add_and_fetch((size_t *)other.m_count, 1);
    DealWithLastRef();
    
    m_ptr = other.m_ptr;
    m_count = other.m_count;

    return (*this);
}

template <typename T>
template <typename D>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<D>& other)
{
    return (AssignmentConv(other));
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
{
    return (AssignmentConv(other));
}

template <typename T>
T& SharedPtr<T>::operator*() const
{ 
    return (*m_ptr); 
} 

template <typename T>
T* SharedPtr<T>::operator->() const
{ 
    return (m_ptr); 
}  

template <typename D, typename U>
bool operator==(const SharedPtr<U>& sp, const SharedPtr<D>& other) 
{ 
    return (other.m_ptr == sp.m_ptr); 
}

template <typename T>
bool SharedPtr<T>::operator!=(const SharedPtr& other) const
{ 
    return !(*this == other); 
}

template <typename T>
SharedPtr<T>::operator bool() const 
{ 
    return (NULL != m_ptr); 
} 

template <typename T>
size_t SharedPtr<T>::GetCount() const
{ 
    return (*m_count); 
}

template <typename T>
T& SharedPtr<T>::GetPtr() const
{ 
    return (m_ptr); 
}

}

#endif 