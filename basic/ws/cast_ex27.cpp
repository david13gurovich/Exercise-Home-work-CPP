#include <iostream>
#include "q27.hpp"

/* typedef struct List List;
typedef struct Person Person;
 */
struct List
{
    char name;
    int key;
};

struct Person
{
    int age;
};

void *ll_find(List *ll,int key)
{
    void *pv = 0;
    
    return (pv);
}

void Foo(List *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    //Person *p = (Person *)ll;
    
    Person *p = static_cast <Person*>(vv);
    p->age = age;
    std::cout << p->age << std::endl; 
}

int main()
{
    /* List a;
    a.name = 'a';
    a.key = 3;
    Foo(&a, 10, 12); 
 */
   int b = 7;
   double c = static_cast <int>(b); 

    char d = '.';
    d = static_cast <char> (b);
    std::cout << d << std::endl;  

    bool f = static_cast <bool> (b); 
    std::cout << f << std::endl; 

   /*  int *e;
    e = static_cast <char *> (&d); */

    return 0;
}

