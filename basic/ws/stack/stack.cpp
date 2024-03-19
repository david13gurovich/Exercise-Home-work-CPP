#include <assert.h> // assert
#include <iostream> // size_t 
#include <limits> // max_int 

#include "stack.hpp"

// static const int DUMMY_DATA = std::numeric_limits<int>::max();

// template <typename DataType>
// Stack<DataType>::Node::Node()
// : m_data(DUMMY_DATA), m_next(NULL) {} 

// template <typename DataType>
// Stack<DataType>::Node::Node(DataType data, const Node* next)
// : m_data(data), m_next(next) {}

// template <typename DataType>
// DataType Stack<DataType>::Node::GetData() const
// {
//     return (m_data);
// }

// template <typename DataType>
// bool Stack<DataType>::Node::HasNext() const
// {
//     return (NULL != &GetNext()); 
// }

// template <typename DataType>
// const typename Stack<DataType>::Node& Stack<DataType>::Node::GetNext() const 
// {
//     return (*m_next);
// }

// template <typename DataType>
// Stack<DataType>::Stack()
// {
//     Node m_dummy;
// }

// template <typename DataType>
// void Stack<DataType>::ClearStack()
// {
//    while (!IsEmpty())
//    {
//         Pop();
//    } 
// }

// template <typename DataType>
// Stack<DataType>::~Stack()
// {
//    ClearStack();
// }

// template <typename DataType>
// Stack<DataType>::Stack(const Stack& other)
// : m_dummy()
// {
//     if (other.IsEmpty())
//     {
//         return;
//     }
   
//     CpyStack(&other.m_dummy.GetNext());
// }

// template <typename DataType>
// Stack<DataType>& Stack<DataType>::operator=(const Stack& other)
// {
//     ClearStack();
//     CpyStack(&other.m_dummy.GetNext());

//     return (*this);
// }

// template <typename DataType>
// void Stack<DataType>::CpyStack(const Node *srcNode)
// {
//     DataType to_push = srcNode->GetData();
    
//     if (!srcNode->HasNext())
//     {
//         Push(to_push);
//         return;
//     }
    
//     CpyStack(&srcNode->GetNext());
//     Push(to_push);
// }

// template <typename DataType>
// void Stack<DataType>::Push(DataType data)
// {
//     const Node *newNode = new Node(data, &m_dummy.GetNext());
//     m_dummy.SetNext(newNode);
// }

// template <typename DataType>
// DataType Stack<DataType>::Top() const
// {
//     return (m_dummy.GetNext().GetData());
// }

// template <typename DataType>
// size_t Stack<DataType>::Count() const
// {
//     const Node *runner = &m_dummy.GetNext(); 
//     size_t count = 0;

//     for( ; NULL != runner; runner = &runner->GetNext(), count++);

//     return (count);
// }

// template <typename DataType>
// bool Stack<DataType>::IsEmpty() const
// {
//     return (NULL == &m_dummy.GetNext()); 
// }

// template <typename DataType>
// void Stack<DataType>::Pop()
// {
//     if (IsEmpty())
//     {
//         return;
//     }
    
//     const Node *toPop = &m_dummy.GetNext();
//     m_dummy.SetNext(&toPop->GetNext());
//     delete toPop;
// }

// template <typename DataType>
// void Stack<DataType>::Node::SetNext(const Node *new_next)
// {
//     m_next = new_next;
// }

