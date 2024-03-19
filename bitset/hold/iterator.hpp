class BaseIterator
{
public:
    iterator(BitProxy *bp);
    iterator(const iterator& it);
    virtual ~iterator();
    iterator& operator=(const iterator& it);

    bool operator==(iterator& other) const;
    bool operator!=(iterator& other) const;
    void operator++() const; 
    void operator--() const;

private:
    BitProxy *bp;
};

class NonCIterator : public BaseIterator
{
public:
    NonCIterator(BitProxy *bp);
    NonCIterator(const NonCIterator& it);
    ~NonCIterator();
    NonCIterator& operator=(const NonCIterator& it);

    BitProxy& operator->();
    BitProxy& operator* (); 
};

class CIterator : public BaseIterator
{
public:
    CIterator(BitProxy *bp);
    CIterator(const CIterator& it);
    ~CIterator();
    CIterator& operator=(const CIterator& it);

    bool operator->() const;
    bool operator* () const;
};

