#include <stdio.h>
#include <dlfcn.h>

void my_func()
{
	void *handle;
	void (*bar2)(void);

	handle = dlopen("./libfoo.so",  RTLD_NOW);
	if (NULL == handle)
	{
		puts("handle\n");
		return;
	}
	*(void **)(&bar2) = dlsym(handle,"Foo");
	if (bar2) 
	{
		bar2();
	}
	else
	{
		puts("Function not found");
	}
	
	dlclose(handle);
}

int main()
{
	my_func();
	
	return 0;
}

