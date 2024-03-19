#include <iostream>

class X
{
    public:
    explicit X();
    operator int();
    operator unsigned int();

    private:
    int m_a;
};

X::X() : m_a(7) {std::cout << "default" << std::endl;}

X::operator int()
{
    std::cout << "int" << std::endl;
    return m_a;
}

X::operator unsigned int()
{
    std::cout << "unsigned" << std::endl;
    return m_a;
}

void Fifi(double x_)
{
   std::cout << x_ << std::endl;
}

int main()
{
    X x1;

    // Fifi(9);
    Fifi(x1);
    
    return 0;
}


