#include <iostream> // cout
#include "template.hpp"

int main()
{
    int arr[12];

    std::cout /* << Max<int>(3,5) << " " */
        << Max<double>(3.7, 12.9) << " ";
    std::cout << Max<int*>(arr, arr+8) << std::endl;
    // std::cout << Max('a', 'b') << std::endl;
    return (0);
}

