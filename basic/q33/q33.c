#include <stdio.h>

const int i = 3;
int l = 3;

int main()
{
    int *ip = (int *)&i;
    *ip = 5;
    printf("i: %d, %p\n *ip: %d, %p\n", i, (void *)&i, *ip, (void *)ip);
    printf("%d\n", l);

    return 0;
}