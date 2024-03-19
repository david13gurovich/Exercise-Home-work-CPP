template<class T>
class BasicIterator
{    
public:
{
    BasicIterator(Bitset<N, STORAGE> *bitset, size_t index);
    ~BasicIterator() {}

    T operator*() const;
    bool operator==(BaseIterator &other) const;
    bool operator!=(BaseIterator &other) const;
    void operator++();
    void operator--();
}
private:
    Bitset<N, STORAGE> *m_bitSet;
    size_t index;
};

typedef BasicIterator<bool> CIterator;
typedef BasicIterator<BitProxy&> NonCIterator;

BasicIterator::BasicIterator(Bitset<N, STORAGE> *bitSet, size_t index)
: m_bitSet(bitSet), m_index(index)
{}




/*
template <size_t N, class STORAGE>
Bitset<N, STORAGE>::BaseIterator::BaseIterator(Bitset<N, STORAGE>::BitProxy bp)
    : m_bitProx(bp) {}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::BaseIterator::operator==(BaseIterator &other) const
{
    return (m_bitProx == other.m_bitProx && 
            (m_bitProx.GetIndex() == other.m_bitProx.GetIndex()));
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::BaseIterator::operator!=(BaseIterator &other) const
{
    return !(*this == other);
}

template <size_t N, class STORAGE>
void Bitset<N, STORAGE>::NonCIterator::operator++()
{
    ++this->m_bitProx.GetIndex();
}

template <size_t N, class STORAGE>
void Bitset<N, STORAGE>::NonCIterator::operator--()
{
    --this->m_bitProx.GetIndex();
}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::BitProxy &Bitset<N, STORAGE>::NonCIterator::operator*()
{
    return (this->m_bitProx); 
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::CIterator::operator*() const
{
    size_t index = this->m_bitProx.m_index;
    
    return (this->m_bitProx.IsSet(index)); 
}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::NonCIterator Bitset<N, STORAGE>::Begin() 
{   
    return (NonCIterator(BitProxy(this, 0)));
}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::NonCIterator Bitset<N, STORAGE>::End() 
{   
    return (NonCIterator(BitProxy(this, N)));
}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::CIterator Bitset<N, STORAGE>::CBegin() const
{   
    return (CIterator(BitProxy(this, 0)));
}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::CIterator Bitset<N, STORAGE>::CEnd() const
{   
    return (CIterator(BitProxy(this, N)));
}

 */

