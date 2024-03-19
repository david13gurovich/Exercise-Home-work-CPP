#include <cstdlib> 
#include <iostream>
#include <fstream>      // std::ofstream

#include "test.hpp"
#include "logger.hpp"

TestResult TestCout(char *argv[]);
TestResult TestFile(char *argv[]);
TestResult TestStdErr(char *argv[]); 

using namespace ilrd;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::ostream& destType(std::cout);
		Logger *log = Logger::InstaceLogger(Logger::ERROR, &destType);
		*log << Logger::ERROR << "add paramter";
		std::cout << "add paramter: ./a.out 1" << std::endl;
		return (EXIT_FAILURE);
	}
	
 	TestCout(argv);
	TestFile(argv);
	TestStdErr(argv); 

	return (EXIT_SUCCESS);
}

TestResult TestCout(char *argv[])
{
	int severity = std::atoi(argv[1]); //need to send 1
	std::ostream& destType(std::cout); 
	Logger *log = Logger::InstaceLogger(static_cast<Logger::Severity>(severity), 
																	&destType);
	
	*log << Logger::DEBUG << "not suppuse to write" << std::endl;
	*log << Logger::INFO << "not suppuse to write"<< std::endl;
	*log << Logger::WARNING << "suppuse to write"<< std::endl;
	*log << Logger::ERROR << "con" << "cat"<< std::endl;

	return (TEST_PASS);
} 

TestResult TestFile(char *argv[])
{
	int severity = std::atoi(argv[1]); //need to send 1
	std::ofstream logFile;
	logFile.open("log_file.txt");
	std::ostream& destType(logFile); 
	Logger *log = Logger::InstaceLogger(static_cast<Logger::Severity>(severity), 
																	&destType);	
	*log << Logger::DEBUG << "not suppuse to write" << std::endl;
	*log << Logger::INFO << "not suppuse to write"<< std::endl;
	*log << Logger::WARNING << "suppuse to write"<< std::endl;
	*log << Logger::ERROR << "con" << "cat"<< std::endl;

	system("diff -s to_cmp.txt log_file.txt");

	logFile.close();

	return (TEST_PASS);
} 

TestResult TestStdErr(char *argv[])
{
	int severity = std::atoi(argv[1]); //need to send 1
	std::ostream& destType(std::cerr); 
	Logger *log = Logger::InstaceLogger(static_cast<Logger::Severity>(severity), 
																	&destType);	
	
	*log << Logger::DEBUG << "not suppuse to write" << std::endl;
	*log << Logger::INFO << "not suppuse to write"<< std::endl;
	*log << Logger::WARNING << "suppuse to write"<< std::endl;
	*log << Logger::ERROR << "con" << "cat"<< std::endl;

	system("diff -s to_cmp.txt log_file.txt");

	return (TEST_PASS);
}  