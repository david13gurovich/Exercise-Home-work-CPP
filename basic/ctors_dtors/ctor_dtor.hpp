struct X
{
    explicit X();
    explicit X(int a_, int b_);
    ~X();
    X(const X& other);
    X& operator = (const X& other_);

    int m_a;
    const int m_b;
};

struct Y
{
   X m_x;
   int m_i;
};

struct Counter 
{
    void Dec();

    int m_a;
    int m_b;
    int max_limit;
};


