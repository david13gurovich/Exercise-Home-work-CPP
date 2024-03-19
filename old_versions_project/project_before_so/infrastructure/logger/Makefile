CC=arm-linux-gnueabi-g++
CPPFLAGS= -I ~/Downloads/boost_1_62_0
LFLAGS  = -L ~/Downloads/boost_1_62_0/stage/lib/

test : test_logger.o logger.o logger.hpp 
	$(CC) -g -o test.out $(LFLAGS) test_logger.o logger.o -lboost_system

logger.o : logger.cpp logger.hpp
	$(CC) -c -g -o logger.o $(CPPFLAGS) logger.cpp -I ~/Downloads/boost_1_62_0/

test_logger.o : test_logger.cpp logger.hpp  
	$(CC) -c -g -o test_logger.o $(CPPFLAGS) test_logger.cpp -I ../include -I ~/Downloads/boost_1_62_0/stage/lib

clean :
	rm test_logger.o logger.o