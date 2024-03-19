#include "suprise.hpp"

int main()
{
    using namespace ilrd;
    
    Surprise *sur = GetRandom();
    sur->SurpriseMe();

    delete sur;

    return 0;
}