#include <stdlib.h>
#include <stdio.h>

struct X;
struct XVtable;
struct Y;
struct YVtable;

void DtorX(struct X *const this);
void DtorY(struct Y *const this);

struct XVtable
{
    void (*Dtor)(struct X* const this); 
};

struct X
{
    struct XVtable *v_table; 
    double m_a; 
};

struct YVtable
{
    void (*Dtor)(struct Y* const this); 
};

struct Y
{
    struct YVtable *v_table;
    double m_a; 
    int m_b; 
};

struct XVtable g_v_table = {DtorX};
struct YVtable g_v_table_y = {DtorY};

/* ctor */
void CtorX(struct X *const this)
{
    this->v_table = &g_v_table;
    printf("X::Ctor()\n");
}

void CtorY(struct Y *const this)
{
    CtorX((struct X *) this);
    this->v_table = &g_v_table_y;

    printf("Y::Ctor()\n");
}

void DtorX(struct X *const this)
{
    printf("X::Dtor()\n");
}

void DtorY(struct Y *const this)
{
    DtorX((struct X *)this);
    printf("Y::Dtor()\n");
}

int main()
{
    int i = 0;
   struct X* xp = malloc(sizeof(struct Y) * 2);
   
   for(i = 0; i < 2; ++i)
   {
       CtorY((struct Y *)&xp[i]);
   }

    printf("%lu\n", sizeof(struct X));
    printf("%lu\n", sizeof(struct Y));
   
   for(i = 1; i >= 0; --i)
   {
       xp[i].v_table->Dtor(&xp[i]);
 }
   free(xp);

    return 0;
}
