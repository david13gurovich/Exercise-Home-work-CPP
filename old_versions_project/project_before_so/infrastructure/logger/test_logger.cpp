#include <cstdlib> /* EXIT_SUCCESS */

#include "logger.hpp"
#include "test.hpp"

using namespace ilrd;

TestResult TestCount();
TestResult TestFile();

int main()
{
	TestCount();
	TestFile();

	return (TEST_PASS);
}


TestResult TestCount()
{
	Logger *log = Logger::InstaceLogger(Logger::ERROR, &std::cout);
	
	*log << Logger::ERROR << "has params "  << std::endl;
	*log << Logger::WARNING << "no need to write" << std::endl;

	Logger *log2 = Logger::InstaceLogger(Logger::WARNING, &std::cout);
	*log2 << Logger::ERROR << "has params"<< std::endl;
	*log2 << Logger::WARNING << "need to write"<< std::endl;
	*log2 << Logger::DEBUG << "no need to write"<< std::endl;
	
	return (TEST_PASS);
}

TestResult TestFile()
{

	return (TEST_PASS);
}

