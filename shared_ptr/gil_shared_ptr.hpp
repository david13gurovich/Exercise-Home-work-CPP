#ifndef ILRD_RD61_SHARED_PTR_HPP
#define ILRD_RD61_SHARED_PTR_HPP

#include <cstddef>

namespace ilrd
{
template <class T>

class SharedPtr
{
public:
    explicit SharedPtr(); 
    explicit SharedPtr(T *const ptr); /* defult paramter*/
    SharedPtr(const SharedPtr& other);
    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr& other);
    
    /* add inline, 20-24 lines */
    T& operator*() {return (*m_ptr);}
    T* operator->() {return (m_ptr);}
    bool operator!=(const SharedPtr& other){return m_ptr != other.m_ptr;} /* they told dont do java style */
    bool operator==(const SharedPtr& other){return m_ptr == other.m_ptr;} /* they told dont do java style */
    operator bool() const {return (NULL != m_ptr);}/* they told dont do java style */

private:
    void CheckIfUsed(); /* bad name */
    // add enter:
    
    T *m_ptr;
    size_t *m_count;

};

template <class T>
SharedPtr<T>::SharedPtr()
    : m_ptr(NULL), m_count(new size_t(1))
    {}

template <class T>
SharedPtr<T>::SharedPtr(T *const ptr)
    : m_ptr(ptr), m_count(new size_t(1))
    {}

template <class T>
SharedPtr<T>::~SharedPtr()
    {
        --(*m_count);
        CheckIfUsed();
    }

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
    {
        --(m_count);
        ++(*(other.m_count)); /* why not ++*other.m_count */
        CheckIfUsed();
        m_count = other.m_count;
        m_ptr = other.m_ptr;
    }

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& other)
    : m_ptr(other.m_ptr), m_count(other.m_count)
    {
        ++(*m_count);/* why not ++*m_count */
    }

template <class T>
void SharedPtr<T>::CheckIfUsed()
{
    if (0 == *m_count)
    {
        delete m_ptr;
        delete m_count;
    }
}
}

#endif