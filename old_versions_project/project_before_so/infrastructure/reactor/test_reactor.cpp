#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "test.hpp"
#include "reactor_inc.hpp"
#include "register_inc.hpp"
#include "call_back_base.hpp"
#include "cfunc_call_back.hpp"
#include "derived_handler.hpp"
#include "wrapper_handler_read.hpp"
#include "handler.hpp" //Handler

TestResult TestAdd();
TestResult TestUnRegister();
TestResult TestExeptionAdd();
TestResult TestExeptionUn();
TestResult TestHandlerRegister();
TestResult TestStartEventLoop();
TestResult TestMemberFunctionToRegister();
TestResult TestHandlerReactor();
TestResult TestFunctorToReactor();

int main()
{
	/* Register */
	//RUN_TEST(TestAdd);
	//RUN_TEST(TestUnRegister);
	//RUN_TEST(TestExeptionAdd);
	//RUN_TEST(TestExeptionUn);
    //RUN_TEST(TestHandlerRegister);

	/* Reactor */
//	RUN_TEST(TestStartEventLoop);
//	RUN_TEST(TestMemberFunctionToRegister);
//	RUN_TEST(TestHandlerReactor);
	RUN_TEST(TestFunctorToReactor);

	return (EXIT_SUCCESS);
}

void ReadFunc(int a)
{
	(void)a;
}

void WriteFunc(int a)
{
	(void)a;
}

TestResult TestAdd()
{
	int readFds[] = {10, 11, 12};
	int writeFds[] = {20, 21, 22};
	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	
	ilrd::Registrator register1;
    ilrd::CFuncCallBack actionRead(ReadFunc);
    ilrd::CFuncCallBack actionWrite(WriteFunc);
	
	for(int i = 0; i < sizeArr; ++i)
	{
		register1.Register(readFds[i], &actionRead, READ);
		register1.Register(writeFds[i], &actionWrite, WRITE);
	}

	for(int i = 0; i < sizeArr; ++i)
	{
		REQUIRE(register1.DoesExist(readFds[i], READ));
		REQUIRE(register1.DoesExist(writeFds[i], WRITE));
	}
 
	return (TEST_PASS);
}

TestResult TestUnRegister()
{
	int readFds[] = {10, 11, 12};
	int writeFds[] = {20, 21, 22};
	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	
	ilrd::Registrator register1;
    ilrd::CFuncCallBack actionRead(ReadFunc);
    ilrd::CFuncCallBack actionWrite(WriteFunc);
	for(int i = 0; i < sizeArr; ++i)
	{
		register1.Register(readFds[i], &actionRead, READ);
		register1.Register(writeFds[i], &actionWrite, WRITE);
	}

	register1.UnRegister(readFds[0], READ);
	register1.UnRegister(writeFds[0], WRITE);
	REQUIRE(!register1.DoesExist(readFds[0], READ));
	REQUIRE(!register1.DoesExist(writeFds[0], WRITE));

	return (TEST_PASS);
}

TestResult TestExeptionAdd()
{
	int readFds[] = {10, 11, 12};
	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	
	ilrd::Registrator register1;
    ilrd::CFuncCallBack actionRead(ReadFunc);
	
    for(int i = 0; i < sizeArr; ++i)
	{
		register1.Register(readFds[i], &actionRead, READ);
	}

	try
	{
		register1.Register(readFds[1], &actionRead, READ);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (TEST_PASS);
}

TestResult TestExeptionUn()
{
	int readFds[] = {10, 11, 12};
	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	
	ilrd::Registrator register1;
    ilrd::CFuncCallBack actionRead(ReadFunc);
	for(int i = 0; i < sizeArr; ++i)
	{
		register1.Register(readFds[i], &actionRead, READ);
	}
	
	try
	{
		const int nonExistNum = 13;
		register1.UnRegister(nonExistNum, READ); 
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return (TEST_PASS);
}

TestResult TestHandlerRegister()
{
    int readFds[] = {10, 11, 12};
	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	
	ilrd::Registrator register1;
    ilrd::DerviedHandler handler1;
    ilrd::WrapperHandlerRead handlerToTest(&handler1);
	
    for(int i = 0; i < sizeArr; ++i)
	{
		register1.Register(readFds[i], &handlerToTest, READ);
	}

	for(int i = 0; i < sizeArr; ++i)
	{
		REQUIRE(register1.DoesExist(readFds[i], READ));
	} 

    return (TEST_PASS);   
}

void Read(int num)
{
	(void)num;
	int const maxBytesToRead = 20;
	char toRead[maxBytesToRead];
	fgets(toRead, maxBytesToRead, stdin);
	std::cout << toRead << std::endl;
}

void Write(int num)
{
	std::cout << "Write" << num << std::endl;
}

TestResult TestStartEventLoop()
{
	int readFds[] = {10, 11, 12};
	int writeFds[] = {20, 21, 22};
	const int sizeArr = sizeof(writeFds) / sizeof(writeFds[0]);

	std::ostream& destType(std::cout);
	ilrd::Reactor reactor(ilrd::Logger::ERROR, &destType);
		
    for(int i = 0; i < sizeArr; ++i)
	{
		reactor.Register(readFds[i], Read, READ);
		//reactor.Register(writeFds[i], Write, WRITE);
	}

	reactor.StartEventLoop();

    return (TEST_PASS);   
}

int g_numRead = 0;
int g_numWrite = 0;

class FunctionToTestRead
{
public:
	void ReadMemberFunc(int fd)
	{
		(void)fd;
		int const maxBytesToRead = 20;
		char toRead[maxBytesToRead];
		fgets(toRead, maxBytesToRead, stdin);
		std::cout << toRead << std::endl;
	}
};

class FunctionToTestWrite 
{
public:
	void WriteMemberFunc(int fd)
	{
		(void)fd;
		++g_numWrite;
		std::cout << "Write" << g_numWrite << std::endl;
	}
};

TestResult TestMemberFunctionToRegister()
{
	int readFds[] = {10, 11, 12};
	//int writeFds[] = {20, 21, 22};

	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	std::ostream& destType(std::cout);
	ilrd::Reactor reactor(ilrd::Logger::ERROR, &destType);
	FunctionToTestRead objFuncToSend1;
	//FunctionToTestWrite objFuncToSend2;
		
    for(int i = 0; i < sizeArr; ++i)
	{
		reactor.Register(readFds[i], &objFuncToSend1, 
			&FunctionToTestRead::ReadMemberFunc, READ);
	//	reactor.Register(writeFds[i], &objFuncToSend2, 
	//		&FunctionToTestWrite::WriteMemberFunc, WRITE);
	}

	//reactor.StartEventLoop();

    return (TEST_PASS);   
}

TestResult TestHandlerReactor()
{
/*     int readFds[] = {10, 11, 12};
	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	
	std::ostream& destType(std::cout);
	ilrd::Reactor reactor(ilrd::Logger::ERROR, &destType);
    ilrd::Handler handler;
	
    for(int i = 0; i < sizeArr; ++i)
	{
		reactor.Register(readFds[i], &handler, READ);
	}

	reactor.StartEventLoop();  */

    return (TEST_PASS);   
}

class FunctorToPassReactor
{
public:
	void operator()(int fd)
	{
		(void)fd;
		int const maxBytesToRead = 20;
		char toRead[maxBytesToRead];
		fgets(toRead, maxBytesToRead, stdin);
		std::cout << toRead << std::endl;
	}
};


TestResult TestFunctorToReactor()
{
    int readFds[] = {STDIN_FILENO, 10, 11, 12};
	const int sizeArr = sizeof(readFds) / sizeof(readFds[0]);
	
	std::ostream& destType(std::cout);
	ilrd::Reactor reactor(ilrd::Logger::ERROR, &destType);
	FunctorToPassReactor functorToPass;
	
    for(int i = 0; i < sizeArr; ++i)
	{
		reactor.Register(readFds[i], functorToPass, READ);
	}

	reactor.StartEventLoop(); 

    return (TEST_PASS);   
}