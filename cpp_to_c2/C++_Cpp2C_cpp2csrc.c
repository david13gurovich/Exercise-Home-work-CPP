#include <stdio.h>
#include <stdlib.h>

struct PublicTransport;
struct Minibus;
struct Taxi;
struct SpecialTaxi;
struct PublicConvoy;

void PublicTransport_Dtor(struct PublicTransport *const this);
void PublicTransport_display_V(struct PublicTransport *const this);
void Minibus_Dtor(struct Minibus *const this);
void Minibus_display_V(struct Minibus *const this);
void Minibus_wash_I(struct Minibus *const this, int minutes);
void Taxi_Dtor(struct Taxi *const this);
void Taxi_display_V(struct Taxi *const this);
void SpecialTaxi_Dtor(struct SpecialTaxi *const this);
void SpecialTaxi_display_V(struct SpecialTaxi *const this);
void PublicConvoy_Dtor(struct PublicConvoy *const this);
void PublicConvoy_display(struct PublicConvoy *const this);

void (*PublicTransport_ptr_func[])() = 
{PublicTransport_Dtor, PublicTransport_display_V};

void (*Minibus_ptr_func[])() = 
{Minibus_Dtor, Minibus_display_V, Minibus_wash_I};

void (*Taxi_ptr_func[])() = 
{Taxi_Dtor,  Taxi_display_V};

void (*SpecialTaxi_ptr_func[])() = 
{SpecialTaxi_Dtor, SpecialTaxi_display_V};

void (*PublicConvoy_ptr_func[])() = 
{PublicConvoy_Dtor, PublicConvoy_display};

static int PublicTransport_s_count = 0;

struct PublicTransport
{
    void (**v_table)();
    int m_license_plate;
};

struct Minibus
{
    struct PublicTransport base;
    int m_numSeats;
};

struct Taxi
{
    struct PublicTransport base;
};

struct SpecialTaxi
{
    struct Taxi base;
};

struct PublicConvoy
{
    struct PublicTransport base;
    struct PublicTransport *m_pt1;
    struct PublicTransport *m_pt2;
    struct Minibus m_m;
    struct Taxi m_t;
};

/****************** PublicTransport ************************/

void PublicTransport_Ctor_V(struct PublicTransport *const this)
{
    this->v_table = PublicTransport_ptr_func;
    this->m_license_plate = ++PublicTransport_s_count;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void PublicTransport_Dtor(struct PublicTransport *const this)
{
    (void)this;
    --PublicTransport_s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PublicTransport_CCtor(struct PublicTransport *const this,
                           const struct PublicTransport *const other)
{
    (void)other;
    this->v_table = PublicTransport_ptr_func;
    this->m_license_plate = ++PublicTransport_s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PublicTransport_display_V(struct PublicTransport *const this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

static void PublicTransport_print_count_V()
{
    printf("s_count: %d\n", PublicTransport_s_count);
}

int PublicTransport_get_ID_V(struct PublicTransport *const this)
{
    return this->m_license_plate;
}

/****************** Minibus ************************/

void Minibus_Ctor_V(struct Minibus *const this)
{
    PublicTransport_Ctor_V((struct PublicTransport *)this);
    this->base.v_table = Minibus_ptr_func;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void Minibus_CCtor(struct Minibus *const this, const struct Minibus *const other)
{
    PublicTransport_CCtor((struct PublicTransport *)this,
                          (struct PublicTransport *)other);
    this->base.v_table = Minibus_ptr_func;
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void Minibus_Dtor(struct Minibus *const this)
{
    printf("Minibus::Dtor()\n");
    this->base.v_table = PublicTransport_ptr_func;
    PublicTransport_Dtor((struct PublicTransport *)this);
}

void Minibus_display_V(struct Minibus *const this)
{
    printf("Minibus::display() ID:%d", PublicTransport_get_ID_V((struct PublicTransport *)this));
    printf(" num seats:%d\n", this->m_numSeats);
}

void Minibus_wash_I(struct Minibus *const this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes,
           PublicTransport_get_ID_V((struct PublicTransport *)this));
}

/****************** Taxi ************************/

void Taxi_Ctor_V(struct Taxi *const this)
{
    PublicTransport_Ctor_V((struct PublicTransport *)this);
    this->base.v_table = Taxi_ptr_func;
    printf("Taxi::Ctor()\n");
}

void Taxi_Dtor(struct Taxi *const this)
{
    printf("Taxi::Dtor()\n");
    this->base.v_table = PublicTransport_ptr_func;
    PublicTransport_Dtor((struct PublicTransport *)this);
}

void Taxi_CCtor(struct Taxi *const this, const struct Taxi *const other)
{
    PublicTransport_CCtor((struct PublicTransport *)this,
                          (struct PublicTransport *)other);
    this->base.v_table = Taxi_ptr_func;
    printf("Taxi::CCtor()\n");
}

void Taxi_display_V(struct Taxi *const this)
{
    printf("Taxi::display() ID:%d\n", PublicTransport_get_ID_V((struct PublicTransport *)this));
}

/****************** SpecialTaxi ************************/

void SpecialTaxi_Ctor_V(struct SpecialTaxi *const this)
{
    Taxi_Ctor_V((struct Taxi *)this);
    this->base.base.v_table = SpecialTaxi_ptr_func;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi_CCtor(struct SpecialTaxi *const this,
                       const struct SpecialTaxi *const other)
{
    Taxi_CCtor((struct Taxi *)this, (struct Taxi *)other);
    this->base.base.v_table = SpecialTaxi_ptr_func;
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxi_Dtor(struct SpecialTaxi *const this)
{
    printf("SpecialTaxi::Dtor()\n");
    Taxi_Dtor((struct Taxi *)this);
    this->base.base.v_table = Taxi_ptr_func;
}

void SpecialTaxi_display_V(struct SpecialTaxi *const this)
{
    printf("SpecialTaxi::display() ID:%d\n",
           PublicTransport_get_ID_V((struct PublicTransport *)this));
}

/****************** operators ************************/

void *operator_new(size_t bytes)
{
    return (malloc(bytes));
}

void operator_delete(void *to_free)
{
    free(to_free);
}

void *operator_new_arr(size_t bytes)
{
    return (malloc(bytes));
}

void operator_delete_arr(void *to_free)
{
    free(to_free);
}
/****************** PublicConvoy ************************/

void PublicConvoy_Ctor_V(struct PublicConvoy *const this)
{
    PublicTransport_Ctor_V((struct PublicTransport *)this);
    this->base.v_table = PublicConvoy_ptr_func;
    this->m_pt1 = operator_new(sizeof(struct Minibus));
    Minibus_Ctor_V((struct Minibus *)this->m_pt1);
    this->m_pt2 = operator_new(sizeof(struct Taxi));
    Taxi_Ctor_V((struct Taxi *)this->m_pt2);
    Minibus_Ctor_V(&(this->m_m));
    Taxi_Ctor_V(&(this->m_t));

    printf("PublicConvoy::Ctor()\n");
}

void PublicConvoy_Dtor(struct PublicConvoy *const this)
{
    this->m_pt1->v_table[0](this->m_pt1); 
    operator_delete(this->m_pt1);
    this->m_pt2->v_table[0](this->m_pt2); 
    operator_delete(this->m_pt2);
    printf("PublicConvoy::Dtor()\n");
    Taxi_Dtor(&this->m_t);
    Minibus_Dtor(&this->m_m);
    this->base.v_table = PublicTransport_ptr_func;
    PublicTransport_Dtor((struct PublicTransport *)this);
}

void PublicConvoy_CCtor(struct PublicConvoy *const this,
                        const struct PublicConvoy *const other)
{
    PublicTransport_CCtor((struct PublicTransport *)this,
                          (struct PublicTransport *)other);
    this->base.v_table = PublicConvoy_ptr_func;
    this->m_pt1 = operator_new(sizeof(struct Minibus));
    Minibus_CCtor((struct Minibus *)this->m_pt1, (struct Minibus *)other->m_pt1);
    this->m_pt2 = operator_new(sizeof(struct Taxi));
    Taxi_CCtor((struct Taxi *)this->m_pt2, (struct Taxi *)other->m_pt2);
    Minibus_CCtor(&this->m_m, &other->m_m);
    Taxi_CCtor(&this->m_t, &other->m_t);

    printf("PublicConvoy::CCtor()\n");
}

void PublicConvoy_display(struct PublicConvoy *const this)
{
    this->m_pt1->v_table[1](this->m_pt1);  
    this->m_pt2->v_table[1](this->m_pt2);   
    Minibus_display_V(&this->m_m);
    Taxi_display_V(&this->m_t);
}

/****************** Print info ************************/
void PublicTransport_print_info_P(struct PublicTransport *a)
{
    a->v_table[1](a); 
}

void print_info_V()
{
    PublicTransport_print_count_V();
}

void Minibus_print_info_M(struct Minibus *m)
{
    m->base.v_table[2](m ,3);
}

struct PublicTransport print_info_I(int i)
{
    struct PublicTransport to_ret_cpy_mini;
    struct Minibus ret;
    (void)i;
    Minibus_Ctor_V(&ret);
    printf("print_info(int i)\n");
    Minibus_display_V(&ret);
    PublicTransport_CCtor(&to_ret_cpy_mini, (struct PublicTransport *)&ret);
    Minibus_Dtor(&ret);

    return (to_ret_cpy_mini);
}

void taxi_display(struct Taxi s)
{
    Taxi_display_V(&s);
}

/****************** main ************************/
int main()
{
    struct Minibus m;
    struct Minibus m2;
    struct Minibus arr3[4];
    struct Taxi *arr4;
    struct SpecialTaxi st;
    struct PublicTransport *array[3];
    struct PublicTransport arr2[3];
    struct PublicConvoy *ts1;
    struct PublicConvoy *ts2;
    size_t size_arr4;

    union tmp
    {
        int i;
        struct PublicTransport pt_tmp;
        struct Minibus m_tmp;
        struct Taxi t_tmp;
    } tmp;

    /* minibus m, and print info */
    Minibus_Ctor_V(&m);
    Minibus_print_info_M(&m);
    tmp.pt_tmp = print_info_I(3);
    PublicTransport_display_V(&tmp.pt_tmp);
    PublicTransport_Dtor(&tmp.pt_tmp); 
    
    /* *array[] */
    array[0] = operator_new(sizeof(struct Minibus));
    Minibus_Ctor_V((struct Minibus *)array[0]);
    array[1] = operator_new(sizeof(struct Taxi));
    Taxi_Ctor_V((struct Taxi *)array[1]);
    array [2] = operator_new(sizeof(struct Minibus));
    Minibus_Ctor_V((struct Minibus *)array[2]);

    for (tmp.i = 0; tmp.i < 3; ++tmp.i) 
    {
        (*array[tmp.i]).v_table[1](array[tmp.i]);
    }

    for (tmp.i = 0; tmp.i < 3; ++tmp.i) 
    {   
        (*array[tmp.i]).v_table[0](array[tmp.i]);
        operator_delete((void *)array[tmp.i]);
    } 

    /* arr2 */
    Minibus_Ctor_V(&tmp.m_tmp);
    PublicTransport_CCtor(arr2, (struct PublicTransport *)&tmp.m_tmp);
    Minibus_Dtor(&tmp.m_tmp);
    Taxi_Ctor_V(&tmp.t_tmp);
    PublicTransport_CCtor(arr2 + 1, (struct PublicTransport *)&tmp.t_tmp);
    Taxi_Dtor(&tmp.t_tmp);
    PublicTransport_Ctor_V(arr2 + 2);

    for (tmp.i = 0; tmp.i < 3; ++tmp.i)
    {
        PublicTransport_display_V(arr2 + tmp.i);
    }

    PublicTransport_print_info_P(arr2);
    
   /* print count and minibus2 */
    PublicTransport_print_count_V();
    Minibus_Ctor_V(&m2);
    PublicTransport_print_count_V(); 

    /* arr3 */
    for (tmp.i = 0; tmp.i < 4; ++tmp.i)
    {
        Minibus_Ctor_V(arr3 + tmp.i);
    } 

    /* arr4 */
    arr4 = operator_new_arr(sizeof(struct Taxi) * 4 + sizeof(size_t));
    *(size_t *)arr4 = 4;
    arr4 = (struct Taxi *)((char *)arr4 + sizeof(size_t));
    
    for (tmp.i = 0; tmp.i < 4; ++tmp.i)
    {
        Taxi_Ctor_V(arr4 + tmp.i);
    }

    size_arr4 = *((size_t *)arr4 - 1);
    for (tmp.i = size_arr4 - 1; tmp.i >= 0 ; --tmp.i)
    {
        (*(struct PublicTransport *)arr4).v_table[0](arr4 + tmp.i);
    }
    arr4 = (struct Taxi *)((char *)arr4 - sizeof(size_t));
    operator_delete_arr(arr4);

    printf("%d\n", 2);
    printf("%d\n", 2);
 
    /* SpecialTaxi */
    SpecialTaxi_Ctor_V(&st);
    Taxi_CCtor(&tmp.t_tmp, (struct Taxi *)&st);
    Taxi_display_V(&tmp.t_tmp);
    Taxi_Dtor(&tmp.t_tmp); 

    /* PublicConvoy */
    ts1 = operator_new(sizeof(struct PublicConvoy));
    PublicConvoy_Ctor_V(ts1);
    ts2 = operator_new(sizeof(struct PublicConvoy));
    PublicConvoy_CCtor(ts2, ts1);

    (*(struct PublicTransport *)ts1).v_table[1](ts1);
    (*(struct PublicTransport *)ts2).v_table[1](ts2);
    
    (*(struct PublicTransport *)ts1).v_table[0](ts1);
    operator_delete(ts1); 
    (*(struct PublicTransport *)ts2).v_table[1](ts2);
    (*(struct PublicTransport *)ts2).v_table[0](ts2);
    operator_delete(ts2); 

    /************** dtors **************/

    SpecialTaxi_Dtor(&st);
 
    for (tmp.i = 3; tmp.i >= 0; --tmp.i)
    {
        Minibus_Dtor(arr3 + tmp.i);
    }

    Minibus_Dtor(&m2);

    for (tmp.i = 2; tmp.i >= 0; --tmp.i)
    {
        PublicTransport_Dtor(arr2 + tmp.i);
    }

    Minibus_Dtor(&m);
    
    return (0);
}