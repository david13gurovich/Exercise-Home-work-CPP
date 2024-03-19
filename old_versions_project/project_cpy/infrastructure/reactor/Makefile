CC=arm-linux-gnueabi-g++
CPPFLAGS= -std=c++11 -fpic -pedantic-errors -Wall -Wextra -g -I ../../../Downloads/boost_1_62_0
SHAREDFLAGS=-shared 

.PHONY: all
all: reactor.out reactor register
reactor.out: logger.o handler.hpp test_reactor.o
	$(CC) -fpic $^ -o $@ -lboost_system -L ../lib -lreactor -L ../lib -lregister -L ../../../Downloads/boost_1_62_0/stage/lib/ -Wl,-rpath=../lib
	cp reactor.out ../bin

.PHONY: reactor
reactor: libreactor.so
libreactor.so: reactor.o 
	$(CC) ${SHAREDFLAGS} $^ -o $@
	mv libreactor.so ../lib

.PHONY: register
register: libregister.so
libregister.so: register.o
	$(CC) ${SHAREDFLAGS} $^ -o $@
	mv libregister.so ../lib
	
reactor.o: ../register/register.cpp ../include/register_inc.hpp reactor.hpp handler.hpp ../include/logger_inc.hpp wrapper_handler_excepation.hpp wrapper_handler_read.hpp wrapper_handler_write.hpp cfunc_call_back.hpp functor_call_back.hpp member_func_call_back.hpp ../include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) reactor.cpp -I ../include/ -o $@

register.o: ../register/register.cpp ../include/register_inc.hpp ../include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) -I ../include/ ../register/register.cpp -o $@

test_reactor.o: test_reactor.cpp ../include/reactor_inc.hpp ../include/test.hpp handler.hpp ../include/logger_inc.hpp 
	$(CC) -c $(CPPFLAGS) -I ../include/ test_reactor.cpp -o $@

logger.o: ../logger/logger.cpp ../include/logger_inc.hpp 
	$(CC) -c $(CPPFLAGS) ../logger/logger.cpp -I ../include -o $@

.PHONY: clean
clean:
	rm -f *.o *.so *.out ../lib/*.so
