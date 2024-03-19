#include <cstdlib>
#include <stdlib.h> //atoi 
#include <iostream>

#include "point.h"

using namespace std;

int main(int argc, char const *argv[])
{    
    Point a = {}, b = {}, c = {};
    if (argc < 2)
    {
        cout << "add parameter" << endl;
        return 1;
    }

    int max_num = atoi(argv[1]) - 1;
    
    a.x = 2, a.y = 3, a.max_limit = max_num;
    b.x = 1, b.y = 1, b.max_limit = max_num;
    c.x = 10,c.y = 11, c.max_limit = max_num;; 
    
    cout << "'a': " << endl; 
    a.AdjustBy(b); //a (3, 4)
    a.Len(); 
    a.Print('(', ')');

    cout << "'b': " << endl;   
    b.AdjustBy(c); //b(11, 12)
    b.Len();
    b.Print('(', ')');

    cout << "'c': " << endl;   
    c.AdjustBy(a); // c(13, 15)
    c.Len();
    c.Print('(', ')');

    cout << "'a': " << endl;   
    b.AdjustBy(c); //b(24, 27)
    b.Len();
    b.Print('(', ')');

    return (0);
}