#include <iostream>
#include <cstdlib> //exit 

using namespace std;

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "this is a bad dog")
        : runtime_error(s_) {}
};

class X
{
public:
    X(){ std::cout << "X Ctor" << std::endl; }
    ~X() { std::cout << "X Dtor" << std::endl; }
};

void Fifi() throw(int, BadDog)
{ 
    throw 3;
    throw BadDog("Bad Pup");
    cerr<<"fifi() after throw"<<endl;
}

void Foo()
{ 
    X x1;
    Fifi();
    cerr<<"Foo() after Fifi()"<<endl;
}

void Bar()
{ 
    Foo(); 
    cerr<<"Bar() after Foo()"<<endl;
}

int main()
{
    try
    {
        // double *d = new double[1000000000000000000];
        Bar();
    }

    catch(bad_alloc)
    {
        cerr<<"Out of memory! exiting."; 
    }

    catch(BadDog b)
    {
        cerr<<"Bad dog exception: "<<b.what(); 
    }

    catch(exception& r)
    {
        cerr<<"unknown exception: "<<r.what(); 
    }
    
    catch(...)
    {
        cerr<<"... : exception "; 
    }
    
    return (0);
}
