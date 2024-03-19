#ifndef ILRD_RD61_BITSET_HPP
#define ILRD_RD61_BITSET_HPP

#include <iostream>  // cout
#include <algorithm> // transform, for_each, copy, equal

namespace ilrd
{
template <size_t N, class STORAGE = unsigned long>
class Bitset
{
    template <size_t N1, class STORAGE1>
    friend bool operator==(const Bitset<N1, STORAGE1> &bs1,
                           const Bitset<N1, STORAGE1> &bs2);

    template <size_t N1, class STORAGE1>
    friend bool operator!=(const Bitset<N1, STORAGE1> &bs1,
                           const Bitset<N1, STORAGE1> &bs2);
    class BitProxy
    {
        friend std::ostream &operator<<(std::ostream &os,
                                        const Bitset<N, STORAGE>::BitProxy &b)
        {
            return (os << b.m_bitset->IsSet(b.m_index));
        }

      public:
        explicit BitProxy(Bitset<N, STORAGE> *bitset, size_t index);
        // BitProxy(const BitProxy &other) = default
        // ~BitProxy() = default

        BitProxy &operator=(bool b);
        BitProxy &operator=(const BitProxy &other);
        bool operator==(const BitProxy &other) const;
        bool operator==(bool b) const;
        bool operator!=(const BitProxy &other) const;
        bool operator!=(bool b) const;

        Bitset<N, STORAGE> *GetBitSet() const { return m_bitset; }
        size_t GetIndex() const { return m_index; }
        size_t& GetIndex() { return m_index; }

      private:
        Bitset<N, STORAGE> *m_bitset;
        size_t m_index;
    };

  public:
    class BaseIterator
    {
      public:
        explicit BaseIterator(BitProxy bp);
        virtual ~BaseIterator() {};
        //BaseIterator(const BaseIterator &it) = default
        //BaseIterator &operator=(const BaseIterator &it)  = default

        bool operator==(BaseIterator &other) const;
        bool operator!=(BaseIterator &other) const;

      protected:
        BitProxy m_bitProx;
    };

    class NonCIterator : public BaseIterator
    {
      public:
        explicit NonCIterator(BitProxy bp)
        : BaseIterator(bp) {}
        //NonCIterator(const NonCIterator &it) = default
        //~NonCIterator() {}

        BitProxy &operator*();
        void operator++();
        void operator--();

      private:
        NonCIterator &operator=(const NonCIterator &it);
    };

    class CIterator : public BaseIterator
    {
      public:
        explicit CIterator(BitProxy bp)
        : BaseIterator(bp) {}
        //CIterator(const CIterator &it) = default
        //CIterator &operator=(const CIterator &it) = default
        //~CIterator() {}

        bool operator*() const;
    };

    explicit Bitset();
    ~Bitset() {}
    Bitset &operator=(const Bitset &other_);
    Bitset(const Bitset &other_);

    void SetBit(size_t index);
    void ResetBit(size_t index);
    bool IsSet(size_t index) const;
    bool IsAllSet() const;
    bool IsAllReset() const;
    void FlipBit(size_t index);
    void FlipAll();
    size_t CountSetBits() const;
    size_t Size() const;
    Bitset &operator|=(const Bitset &other_);
    Bitset &operator&=(const Bitset &other_);
    Bitset &operator^=(const Bitset &other_);

    BitProxy operator[](size_t index);
    bool operator[](size_t index) const;

    CIterator CBegin() const;
    NonCIterator Begin();
    CIterator CEnd() const;
    NonCIterator End();

  private:
    size_t BitIndexInByte(size_t index) const;
    size_t indexInArr(size_t index) const;
    void ChangeBit(BitProxy &bp, bool b);

    static const int m_bitsInOneByte = 8;
    static const int m_bitsInIndex = sizeof(STORAGE) * m_bitsInOneByte;
    static const size_t m_numElements = (N / m_bitsInIndex) + ((N % m_bitsInIndex == 0) ? 0 : 1);

    STORAGE m_arr[m_numElements];
};

template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator~(const Bitset<N, STORAGE> &bS1);
template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator|(const Bitset<N, STORAGE> &bS1,
                             const Bitset<N, STORAGE> &bS2);
template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator&(const Bitset<N, STORAGE> &bS1,
                             const Bitset<N, STORAGE> &bS2);
template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator^(const Bitset<N, STORAGE> &bS1,
                             const Bitset<N, STORAGE> &bS2);

class CtorInit
{
  public:
    CtorInit(int n) { (void)n; }
    int operator()(int n) const
    {
        (void)n;
        return 0;
    }
};

template <size_t N, class STORAGE>
Bitset<N, STORAGE>::Bitset()
{
    std::transform(m_arr, m_arr + m_numElements, m_arr, CtorInit(0));
}

template <size_t N, class STORAGE>
Bitset<N, STORAGE>::Bitset(const Bitset &other)
{
    std::copy(other.m_arr, other.m_arr + m_numElements, m_arr);
}
template <size_t N, class STORAGE>
Bitset<N, STORAGE> &Bitset<N, STORAGE>::operator=(const Bitset &other)
{
    std::copy(other.m_arr, other.m_arr + m_numElements, m_arr);

    return (*this);
}

template <size_t N, class STORAGE>
size_t Bitset<N, STORAGE>::BitIndexInByte(size_t index) const
{
    return (index % m_bitsInIndex);
}

template <size_t N, class STORAGE>
size_t Bitset<N, STORAGE>::indexInArr(size_t index) const
{
    return (index / m_bitsInIndex);
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::IsSet(size_t index) const
{
    STORAGE mask = 0X01;

    return (m_arr[indexInArr(index)] & mask << BitIndexInByte(index));
}

template <size_t N, class STORAGE>
void Bitset<N, STORAGE>::SetBit(size_t index)
{
    STORAGE mask = 0X01;
    mask = mask << BitIndexInByte(index);
    m_arr[indexInArr(index)] |= mask;
}

template <size_t N, class STORAGE>
void Bitset<N, STORAGE>::ResetBit(size_t index)
{
    STORAGE mask = 0X01;
    mask = mask << BitIndexInByte(index);
    m_arr[indexInArr(index)] &= ~mask;
}

template <size_t N, class STORAGE>
void Bitset<N, STORAGE>::FlipBit(size_t index)
{
    STORAGE mask = 0X01;
    mask = mask << BitIndexInByte(index);
    m_arr[indexInArr(index)] ^= mask;
}

template <size_t N, class STORAGE>
size_t Bitset<N, STORAGE>::Size() const
{
    return (N);
}

class CountBitsOn
{
  public:
    explicit CountBitsOn(size_t *count) : m_count(count) {}
    //    ~CountBitsOn() {} = default

    void operator()(unsigned char x) { *m_count += CountBits(x); }
    static unsigned char CountBits(unsigned char x);

  private:
    size_t *m_count;

    static const unsigned char cm1 = 0x55;
    static const unsigned char cm2 = 0x33;
    static const unsigned char cm4 = 0x0f;
};

unsigned char CountBitsOn::CountBits(unsigned char x)
{
    x = (x & cm1) + ((x >> 1) & cm1);
    x = (x & cm2) + ((x >> 2) & cm2);
    x = (x & cm4) + ((x >> 4) & cm4);

    return x;
}

template <size_t N, class STORAGE>
size_t Bitset<N, STORAGE>::CountSetBits() const
{
    size_t res = 0;
    CountBitsOn obj(&res);

    std::for_each(reinterpret_cast<const unsigned char *>(m_arr),
                  reinterpret_cast<const unsigned char *>(m_arr) +
                      m_numElements * sizeof(STORAGE),
                  obj);

    return (res);
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::IsAllSet() const
{
    return (CountSetBits() == N);
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::IsAllReset() const
{
    return (CountSetBits() == 0);
}

template <class STORAGE>
class Flip
{
  public:
    explicit Flip() {}
    // ~Flip() {} = default
    void operator()(STORAGE &x) { x = ~x; }
};

template <size_t N, class STORAGE>
void Bitset<N, STORAGE>::FlipAll()
{
    size_t remainder = N % m_bitsInIndex;
    size_t isRemainder = !!remainder;
    STORAGE mask = 0;
    mask = ~mask;
    mask = mask << remainder;
    mask = ~mask;

    std::for_each(m_arr, m_arr + m_numElements - isRemainder, Flip<STORAGE>());
    m_arr[m_numElements - 1] ^= mask;
}

template <size_t N, class STORAGE>
bool operator==(const Bitset<N, STORAGE> &bs1, const Bitset<N, STORAGE> &bs2)
{
    return (std::equal(bs1.m_arr, bs1.m_arr + bs1.m_numElements, bs2.m_arr));
}

template <size_t N, class STORAGE>
bool operator!=(const Bitset<N, STORAGE> &bs1, const Bitset<N, STORAGE> &bs2)
{
    return (!(bs1 == bs2));
}

template <class STORAGE>
class BitwiseOperatorOr
{
  public:
    // BitwiseOperatorOr() = default
    // ~BitwiseOperatorOr() = default

    STORAGE operator()(STORAGE x1, STORAGE x2)
    {
        return (x1 | x2);
    }
};

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::BitProxy::operator==(const BitProxy &other) const
{
    return (m_bitset->IsSet(m_index) == other.m_bitset->IsSet(other.m_index));
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::BitProxy::operator==(bool b) const
{
    return (m_bitset->IsSet(m_index) == b);
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::BitProxy::operator!=(const BitProxy &other) const
{
    return !(*this == other);
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::BitProxy::operator!=(bool b) const
{
    return !(*this == b);
}

template <size_t N, class STORAGE>
Bitset<N, STORAGE> &Bitset<N, STORAGE>::operator|=(const Bitset &other)
{
    std::transform(m_arr, m_arr + m_numElements, other.m_arr, m_arr,
                   BitwiseOperatorOr<STORAGE>());

    return (*this);
}

template <class STORAGE>
class BitwiseOperatorAnd
{
  public:
    // BitwiseOperatorAnd() = default
    // ~BitwiseOperatorAnd() = default

    STORAGE operator()(STORAGE x1, STORAGE x2)
    {
        return (x1 & x2);
    }
};

template <size_t N, class STORAGE>
Bitset<N, STORAGE> &Bitset<N, STORAGE>::operator&=(const Bitset &other)
{
    std::transform(m_arr, m_arr + m_numElements, other.m_arr, m_arr,
                   BitwiseOperatorAnd<STORAGE>());
    return (*this);
}

template <class STORAGE>
class BitwiseOperatorXor
{
  public:
    // BitwiseOperatorXor() = default
    // ~BitwiseOperatorXor() = default

    STORAGE operator()(STORAGE x1, STORAGE x2)
    {
        return (x1 ^ x2);
    }
};

template <size_t N, class STORAGE>
Bitset<N, STORAGE> &Bitset<N, STORAGE>::operator^=(const Bitset &other)
{
    std::transform(m_arr, m_arr + m_numElements, other.m_arr, m_arr,
                   BitwiseOperatorXor<STORAGE>());
    return (*this);
}

template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator|(const Bitset<N, STORAGE> &bS1, const Bitset<N, STORAGE> &bS2)
{
    Bitset<N, STORAGE> cpyBs1(bS1);

    return (cpyBs1 |= bS2);
}

template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator&(const Bitset<N, STORAGE> &bS1, const Bitset<N, STORAGE> &bS2)
{
    Bitset<N, STORAGE> cpyBs1(bS1);

    return (cpyBs1 &= bS2);
}
template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator^(const Bitset<N, STORAGE> &bS1, const Bitset<N, STORAGE> &bS2)
{
    Bitset<N, STORAGE> cpyBs1(bS1);

    return (cpyBs1 ^= bS2);
}

template <size_t N, class STORAGE>
Bitset<N, STORAGE> operator~(const Bitset<N, STORAGE> &bS1)
{
    Bitset<N, STORAGE> copyBs1(bS1);
    copyBs1.FlipAll();

    return (copyBs1);
}

template <size_t N, class STORAGE>
bool Bitset<N, STORAGE>::operator[](size_t index) const
{
    STORAGE mask = 0X01;
    mask = mask << BitIndexInByte(index);

    return (m_arr[indexInArr(index)] & mask);
}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::BitProxy Bitset<N, STORAGE>::operator[](size_t index)
{
    return (BitProxy(this, index));
}

template <size_t N, class STORAGE>
void Bitset<N, STORAGE>::ChangeBit(BitProxy &bp, bool b)
{
    ResetBit(bp.GetIndex());
    STORAGE mask = b;
    mask = mask << BitIndexInByte(bp.GetIndex());
    m_arr[indexInArr(bp.GetIndex())] |= mask;
}

template <size_t N, class STORAGE>
Bitset<N, STORAGE>::BitProxy::BitProxy(Bitset<N, STORAGE> *bitset, size_t index)
    : m_bitset(bitset), m_index(index) {}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::BitProxy &Bitset<N, STORAGE>::BitProxy::operator=(bool b)
{
    m_bitset->ChangeBit(*this, b);

    return (*this);
}

template <size_t N, class STORAGE>
typename Bitset<N, STORAGE>::BitProxy &Bitset<N, STORAGE>::BitProxy::operator=(const BitProxy &other)
{
    m_bitset->ChangeBit(*this, other.GetBitSet()->IsSet(m_index));

    return (*this);
}

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

} //namespace ilrd

#endif
