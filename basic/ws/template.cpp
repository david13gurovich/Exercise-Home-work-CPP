#include <iostream> // cout
#include "template.hpp"

// bool a()
// {
//     int x = 1;
//     int y = 2;
//     return y > x ? true :  false;
// }

int main()
{
    int x = 5;
    int y = 3;
    std::cout << Max<void *>(&x,&y) << " ";
    // std::cout << Max(3, 'b') << std::endl;
    // std::cout << a() << std::endl;
    return (0);
}

