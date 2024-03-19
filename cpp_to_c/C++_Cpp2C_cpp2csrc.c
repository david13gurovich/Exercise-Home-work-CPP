#include <stdio.h> /* print */
#include <stdlib.h> /*  malloc, free */

#define UNUSED(a) ((void)(a))

struct VTablePublicTransport;
struct VTableMinibus;
struct VTableTaxi;
struct VTableSpecialTaxi;
struct PublicTransport;
struct Minibus;
struct Taxi;
struct SpecialTaxi;

int get_ID(struct PublicTransport *const this);
static void print_count();
static void publicTransport_print_count();
static void minibus_print_count();
struct Minibus *MMaxPTransport(struct Minibus *t1, struct Minibus *t2);
struct PublicTransport *PTMaxPTransport(struct PublicTransport *t1,
                                        struct PublicTransport *t2);
void CCtorMinibus(struct Minibus *const this, struct Minibus *const other);
void CCtorPublicTransport(struct PublicTransport *const this, 
                        const struct PublicTransport *other);
void CCtorSpecialTaxi(struct SpecialTaxi *const this, 
                        struct SpecialTaxi *const other);
void CCtorTaxi(struct Taxi *const this, struct Taxi *const other);
void CtorMinibus(struct Minibus *const this);
void CtorPublicTransport(struct PublicTransport *const this);
void CtorSpecialTaxi(struct SpecialTaxi *const this);
void CtorTaxi(struct Taxi *const this);
void DtorMinibus(struct Minibus *const this);
void DtorPublicTransport(struct PublicTransport *const this);
void DtorSpeciaTaxi(struct SpecialTaxi *const this);
void DtorTaxi(struct Taxi *const this);
void displayMinibus(struct Minibus *const this);
void displayPublicTransport(struct PublicTransport *const this);
void SpeciadisplayTaxi(struct SpecialTaxi *const this);
void displayTaxi(struct Taxi *const this);
void wash(struct Minibus *const this, int minutes);

/* structs */
struct VTablePublicTransport
{
    void (*Dtor)(struct PublicTransport* const this);
    void (*display)(struct PublicTransport *const this);
};

struct PublicTransport
{
    struct VTablePublicTransport *v_table;
    int m_license_plate;
};

struct VTableMinibus
{
    void (*Dtor)(struct Minibus* const this);
    void (*display)(struct Minibus *const this);
    void (*wash)(struct Minibus *const this, int minutes);
};

struct Minibus
{
    struct VTableMinibus *v_table;
    int m_license_plate;
    int m_numSeats;
};

struct VTableTaxi
{
    void (*Dtor)(struct Taxi* const this);
    void (*display)(struct Taxi *const this); 
};

struct Taxi
{
    struct VTableTaxi *v_table;
    int m_license_plate;
};

struct VTableSpecialTaxi
{
    void (*Dtor)(struct SpecialTaxi* const this);
    void (*display)(struct SpecialTaxi *const this); 
};

struct SpecialTaxi
{
    struct VTableSpecialTaxi *v_table;
    int m_license_plate;
};

/* global v_tables */
struct VTablePublicTransport g_v_table = {DtorPublicTransport, displayPublicTransport};
struct VTableMinibus g_v_table_minibus = {DtorMinibus, displayMinibus, wash};
struct VTableTaxi g_v_table_taxi = {DtorTaxi, displayTaxi};
struct VTableSpecialTaxi g_v_table_special_taxi = {DtorSpeciaTaxi, SpeciadisplayTaxi};


int PublicTransport_s_count = 0; 

/*********************** PublicTransport ***********************/

/* ctor */
void CtorPublicTransport(struct PublicTransport *const this)
{
    ++PublicTransport_s_count;
    this->m_license_plate = PublicTransport_s_count;
    this->v_table = &g_v_table;
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

/* cctor */
void CCtorPublicTransport(struct PublicTransport *const this, 
                        const struct PublicTransport *other) 
{    
    UNUSED(other);
    ++PublicTransport_s_count;
    this->m_license_plate = PublicTransport_s_count;
    this->v_table = &g_v_table;

    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

/* dtor */
void DtorPublicTransport(struct PublicTransport *const this)
{
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
    --PublicTransport_s_count;
}

/* display */
void displayPublicTransport(struct PublicTransport *const this) 
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

static void print_count()
{
    printf("PublicTransport_s_count %d\n", PublicTransport_s_count);
}

static void publicTransport_print_count()
{
    print_count();
}

static void minibus_print_count()
{
    print_count();
}

int get_ID(struct PublicTransport *const this)
{
    return this->m_license_plate;
}

/********************** Minibus ***********************/

/* ctor */
void CtorMinibus(struct Minibus *const this)
{
    this->m_numSeats = 20;
    CtorPublicTransport((struct PublicTransport *const)this);
    this->v_table = &g_v_table_minibus;
    printf("Minibus::Ctor()\n");
}

/* cctor */
 void CCtorMinibus(struct Minibus *const this, 
                    struct Minibus *const other)
{
    this->m_numSeats = other->m_numSeats;
    CCtorPublicTransport((struct PublicTransport *)this, 
                        (struct PublicTransport *)other); 
    this->v_table = &g_v_table_minibus;
    printf("Minibus::CCtor()\n");
}

/* dtor */
void DtorMinibus(struct Minibus *const this)
{
    printf("Minibus::Dtor()\n");
    this->v_table = (struct VTableMinibus *)&g_v_table;
    DtorPublicTransport((struct PublicTransport *const )this);
}

/* display */
void displayMinibus(struct Minibus *const this)
{
    printf("Minibus::display() ID: %d ", get_ID((struct PublicTransport *)this));
    printf("num seats: %d\n", this->m_numSeats);
}

void wash(struct Minibus *const this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, 
            get_ID((struct PublicTransport *)this));
}

/********************** taxi ***********************/

/* ctor */
void CtorTaxi(struct Taxi *const this)
{
    CtorPublicTransport((struct PublicTransport *const)this);
    this->v_table = &g_v_table_taxi;
    printf("Taxi::Ctor()\n");
}

/* cctor */
void CCtorTaxi(struct Taxi *const this, struct Taxi *const other)
{
    CCtorPublicTransport((struct PublicTransport *)this, 
                        (struct PublicTransport *)other);
    this->v_table = &g_v_table_taxi;
    printf("Taxi::CCtor()\n");
}

/* dtor */
void DtorTaxi(struct Taxi *const this)
{
    printf("Taxi::Dtor()\n");
    this->v_table = (struct VTableTaxi *)&g_v_table;
    DtorPublicTransport((struct PublicTransport *const )this);
}

/* display */
void displayTaxi(struct Taxi *const this)
{
    printf("displayTaxi::display() ID: %d\n", 
            get_ID((struct PublicTransport *)this));
}

/********************** special taxi ***********************/

/* ctor */
void CtorSpecialTaxi(struct SpecialTaxi *const this)
{
    CtorTaxi((struct Taxi *const) this);
    this->v_table = &g_v_table_special_taxi;
    printf("SpecialTaxi::Ctor()\n");
}

/* cctor */
void CCtorSpecialTaxi(struct SpecialTaxi *const this, struct SpecialTaxi *const other)
{
    CCtorTaxi((struct Taxi *)this, (struct Taxi *)other);
    this->v_table = &g_v_table_special_taxi;
    printf("SpecialTaxi::CCtor()\n");
}

/* dtor */
void DtorSpeciaTaxi(struct SpecialTaxi *const this)
{
    printf("DtorSpeciaTaxi::Dtor()\n");
    this->v_table = (struct VTableSpecialTaxi *)&g_v_table;
    DtorTaxi((struct Taxi *const) this);
}

/* display */
void SpeciadisplayTaxi(struct SpecialTaxi *const this)
{
    printf("SpeciaTaxi::display() ID: %d\n", get_ID((struct PublicTransport *)this));
}

/*********************** print info ***********************/

void PrintInfoPublicTransport(struct PublicTransport *a)
{
    a->v_table->display(a);
}

void PrintInfoV()
{
    printf("Print Info void\n");
    print_count();
}

void PrintInfoMinibus(struct Minibus *m)
{
    m->v_table->wash(m, 3);
}

void PrintInfoI(struct PublicTransport *this, int i)
{
    struct Minibus ret_mini;
    
    UNUSED(i);

    CtorMinibus(&ret_mini);
    printf("print_info(int i)\n");
    displayMinibus(&ret_mini);
    CCtorPublicTransport(this, (struct PublicTransport *)&ret_mini);
    DtorMinibus(&ret_mini);
}

void taxi_display(struct Taxi s)
{
    displayTaxi(&s);
}

/********************** my_test ***********************/

void MyTest()
{
    struct PublicTransport p;
    struct PublicTransport cpy_p;   
   
    struct Minibus m;
    struct Minibus cpy_m; 
    
    struct Taxi t;
    struct Taxi cpy_t_taxi;
    
    struct SpecialTaxi st;
    struct SpecialTaxi cpy_st;

    struct PublicTransport ret_print_info;
    struct Taxi ret_taxi_display, cpy_ret_taxi_display; 

    /* public transport */
    printf("************** public transport **************\n");
    CtorPublicTransport(&p);
    CCtorPublicTransport(&cpy_p, &p);
    print_count(&p);
    print_count(&cpy_p);
    get_ID(&p);
    get_ID(&cpy_p);
    PrintInfoPublicTransport(&p);
    PrintInfoPublicTransport(&cpy_p);
    p.v_table->display(&p);
    cpy_p.v_table->display(&cpy_p);
    p.v_table->Dtor(&p);
    cpy_p.v_table->Dtor(&cpy_p);
    printf("\n"); 

    /* minibus */
    printf("************** minibus **************\n");
    CtorMinibus(&m);
    CCtorMinibus(&cpy_m, &m);
    get_ID((struct PublicTransport *)&m);
    get_ID((struct PublicTransport *)&cpy_m);
    print_count((struct PublicTransport *)&m);
    print_count((struct PublicTransport *)&cpy_m);
    PrintInfoMinibus(&m);
    PrintInfoMinibus(&cpy_m);
    cpy_m.v_table->display(&cpy_m);
    cpy_m.v_table->wash(&cpy_m, 10);
    cpy_m.v_table->Dtor(&cpy_m);
    m.v_table->display(&m);
    m.v_table->wash(&m, 5);
    m.v_table->Dtor(&m);
    printf("\n"); 

    /* taxi */
    printf("************** taxi **************\n");
    CtorTaxi(&t);
    CCtorTaxi(&cpy_t_taxi, &t);
    get_ID((struct PublicTransport *)&t);
    get_ID((struct PublicTransport *)&cpy_t_taxi);
    print_count((struct PublicTransport *)&t);
    print_count((struct PublicTransport *)&cpy_t_taxi);
    t.v_table->display(&t);
    t.v_table->Dtor(&t);
    cpy_t_taxi.v_table->display(&cpy_t_taxi);
    cpy_t_taxi.v_table->Dtor(&cpy_t_taxi);
    printf("\n");
 
     /* Special taxi */
     printf("************** Special taxi **************\n");
    CtorSpecialTaxi(&st);
    CCtorSpecialTaxi(&cpy_st, &st);
    get_ID((struct PublicTransport *)&st);
    get_ID((struct PublicTransport *)&cpy_st);
    print_count((struct PublicTransport *)&st);
    print_count((struct PublicTransport *)&cpy_st);
    st.v_table->display(&st);
    st.v_table->Dtor(&st);
    cpy_st.v_table->display(&cpy_st);
    cpy_st.v_table->Dtor(&cpy_st);
    printf("\n");

    printf("********** print info with int type **********\n");
    PrintInfoI(&ret_print_info, 3);
    ret_print_info.v_table->display(&ret_print_info);
    ret_print_info.v_table->Dtor(&ret_print_info);

    printf("************** taxi display **************\n");
    CtorTaxi(&ret_taxi_display);
    CCtorTaxi(&cpy_ret_taxi_display, &ret_taxi_display);
    taxi_display(cpy_ret_taxi_display);
    cpy_ret_taxi_display.v_table->Dtor(&cpy_ret_taxi_display);
    ret_taxi_display.v_table->Dtor(&ret_taxi_display); 
}

void *operator_new(size_t sizeof_type)
{
    return (malloc(sizeof_type));
}

void operator_delete(void *to_delete)
{
    free(to_delete);
}

void *operator_new_arr(size_t total_bytes)
{
    return (malloc(total_bytes));
}

void operator_delete_arr(void *to_delete)
{
    free(to_delete);
}

/********************** main ***********************/

int main()
{
    struct Minibus arr3[4];
    struct Minibus m2;
    struct Minibus m;
    struct PublicTransport *array[3];
    struct PublicTransport arr2[3];
    struct SpecialTaxi st;
    struct Taxi *arr4;

    union reused
    {
        int i;
        struct PublicTransport pt_tmp;
        struct Minibus m_tmp;
        struct Taxi t_tmp;
    } reused;

    /*  struct PublicTransport *p;
    p = new(sizeof(*p));
    CtorPublicTransport(p);
    (*(struct VTablePublicTransport **)(p))->Dtor(p);*/
    
    CtorMinibus(&m);
    PrintInfoMinibus(&m); 
    
    PrintInfoI(&reused.pt_tmp, 3);
    displayPublicTransport(&reused.pt_tmp);
    DtorPublicTransport(&reused.pt_tmp);

    array[0] = operator_new(sizeof(struct Minibus));
    array[1] = operator_new(sizeof(struct Taxi));
    array[2] = operator_new(sizeof(struct Minibus));

    CtorMinibus((struct Minibus *)array[0]);
    CtorTaxi((struct Taxi *)array[1]);
    CtorMinibus((struct Minibus *)array[2]);

    for(reused.i = 0; reused.i < 3; ++reused.i)
    {
        array[reused.i]->v_table->display(array[reused.i]);  
    }

    for (reused.i = 0; reused.i < 3; ++reused.i) 
    {
        array[reused.i]->v_table->Dtor(array[reused.i]);
        operator_delete(array[reused.i]);
    }

    CtorMinibus(&reused.m_tmp);
    CCtorPublicTransport(arr2, (struct PublicTransport *)&reused.m_tmp);
    DtorMinibus(&reused.m_tmp);
    CtorTaxi(&reused.t_tmp);
    CCtorPublicTransport(arr2 + 1, (struct PublicTransport *)&reused.t_tmp);
    DtorTaxi(&reused.t_tmp);
    CtorPublicTransport(arr2 + 2);

    for(reused.i = 0; reused.i < 3; ++reused.i)
    {
        displayPublicTransport(arr2 + reused.i);       
    }
    
    PrintInfoPublicTransport(arr2);
    publicTransport_print_count();

    CtorMinibus(&m2);
    minibus_print_count();

    for(reused.i = 0; reused.i < 4; ++reused.i) 
    {
        CtorMinibus(arr3 + reused.i);
    }

    arr4 = operator_new_arr(4 * sizeof(struct Taxi) + sizeof(size_t));
    *(size_t *)arr4 = 4;
    arr4 = (struct Taxi *)((size_t *)arr4 + 1);

    for(reused.i = 0; reused.i < 4; ++reused.i)
    {
        CtorTaxi(arr4 + reused.i);
    }

    for (reused.i = *((size_t *)arr4 - 1) - 1; reused.i >= 0; --reused.i)
    {
        (arr4 + reused.i)->v_table->Dtor(arr4 + reused.i);
    }
    
    operator_delete_arr((size_t *)arr4 - 1);  

    printf("%d\n", 2);    
    printf("%d\n", 2);    

    CtorSpecialTaxi(&st);
    CCtorTaxi(&reused.t_tmp ,(struct Taxi *)&st);
    displayTaxi(&reused.t_tmp);
    DtorTaxi(&reused.t_tmp);
    DtorSpeciaTaxi(&st);

    for(reused.i = 3; reused.i >= 0; --reused.i) 
    {
        arr3[reused.i].v_table->Dtor(arr3 + reused.i);
    }

    m2.v_table->Dtor(&m2);
    
    for(reused.i = 2; reused.i >= 0; --reused.i) 
    {
        arr2[reused.i].v_table->Dtor(arr2 + reused.i);
    }

    m.v_table->Dtor(&m);

    return (EXIT_SUCCESS);
}
