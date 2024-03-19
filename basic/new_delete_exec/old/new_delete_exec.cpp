#include <iostream> /* size_t */
#include <limits> /* max_int */

#include "new_delete_exec.hpp"

static const int DUMMY_DATA = std::numeric_limits<int>::max();

Stack::Node::Node()
: m_data(DUMMY_DATA), m_next(NULL) {} 

Stack::Node::Node(DataType data, const Node* next)
: m_data(data), m_next(next) {}

DataType Stack::Node::GetData() const
{
    return (m_data);
}

bool Stack::Node::HasNext() const
{
    return (NULL != &GetNext()); 
}

const Stack::Node& Stack::Node::GetNext() const 
{
    return (*m_next);
}

Stack::Stack()
: m_dummy() {}

Stack::~Stack()
{
   while (!IsEmpty())
   {
        Pop();
   }
}

void Stack::Push(DataType data)
{
    const Node *newNode = new Node(data, &m_dummy.GetNext());
    m_dummy.SetNext(newNode);
}

DataType Stack::Top() const
{
    return (m_dummy.GetNext().GetData());
}

size_t Stack::Count() const
{
    const Node *runner = &m_dummy.GetNext(); 
    size_t count = 0;

    for( ; NULL != runner; runner = &runner->GetNext(), count++);

    return (count);
}

bool Stack::IsEmpty() const
{
    return (NULL == &m_dummy.GetNext()); 
}

void Stack::Pop()
{
    if (IsEmpty())
    {
        return;
    }
    
    const Node *toPop = &m_dummy.GetNext();
    m_dummy.SetNext(&toPop->GetNext());
    delete toPop;
}

void Stack::Node::SetNext(const Node *new_next)
{
    m_next = new_next;
}

