#ifndef ILRD_RD61_NEW_DELETE_HPP
#define ILRD_RD61_NEW_DELETE_HPP

typedef int DataType;

struct Stack
{
public:
    explicit Stack();
    ~Stack();

    void Push(DataType data);
    void Pop();
    DataType Top() const;
    size_t Count() const;
    bool IsEmpty() const;

    struct Node
    {
        explicit Node();
        explicit Node(DataType data, const Node* next);

        DataType GetData() const;
        bool HasNext() const;
        const Node &GetNext() const;

        const DataType m_data;
        const Node *m_next;
        
        //NOT PART OF THE API 
        void SetNext(const Node *new_next);
    };

    Node m_dummy;
};

#endif
