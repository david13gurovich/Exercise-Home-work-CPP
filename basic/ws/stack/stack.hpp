#ifndef ILRD_RD61_STACK_HPP
#define ILRD_RD61_STACK_HPP

namespace ilrd
{

template <typename DataType>

class Stack
{

public:
    explicit Stack();
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    ~Stack();

    void Push(DataType data);
    void Pop();
    DataType Top() const;
    size_t Count() const;
    bool IsEmpty() const;

    class Node
    {
    public:
        explicit Node();
        explicit Node(DataType data, const Node* next);

        DataType GetData() const;
        bool HasNext() const;
        const Node &GetNext() const;

        const DataType m_data;
        const Node *m_next;
        void SetNext(const Node *new_next);        
    };

private:
    void ClearStack();
    void CpyStack(const Stack::Node *srcNode);
    Node m_dummy;
};

#include "stack.tpp"

}

#endif
