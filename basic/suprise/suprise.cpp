#include <ctime> //srand

#include "suprise.hpp"

int const NUM_SURPRISES = 3;

namespace ilrd
{

static void DeleteArr(Surprise **arr)
{
    for(int i = 0; i < NUM_SURPRISES; i++)
    {
       delete arr[i];
    }
}

Surprise::Surprise()
{}

Surprise::~Surprise()
{}

Surprise *GetRandom()
{
    Surprise *surpriseSons[] = {new OnScreen, new Echo, new CreateFile};
    srand(time(0));
    int randSurprise = rand() % NUM_SURPRISES; 
    Surprise *toReturn = surpriseSons[randSurprise];
    surpriseSons[randSurprise] = NULL;

    DeleteArr(surpriseSons);

    return (toReturn);
}
}//ilrd


