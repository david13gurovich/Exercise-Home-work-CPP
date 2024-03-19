#include <ctime>
#include "suprise.hpp"

namespace ilrd
{

Surprise **surpriseSons = (Surprise **)malloc(2000);

void InitsurpriseSons()
{
    surpriseSons[0] = new Surprise;
/*     surpriseSons[1] = new System;
    surpriseSons[2] = new File; */
 }

Surprise::Surprise()
{
    InitsurpriseSons();
}

Surprise::~Surprise()
{}

Surprise *GetRandom()
{
    srand(time(NULL));
    int randSurprise = rand() % 1; 

    return (surpriseSons[2]/* [randSurprise] */);
}
}

int main()
{
    using namespace ilrd;
    
 /*    Surprise *s = GetRandom();
    // s->SurpriseMe();

    delete s; */

    InitsurpriseSons();

    return 0;
}