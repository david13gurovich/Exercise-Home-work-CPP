.PHONY: gdp
gdp: CC=g++
gdp: CPPFLAGS =-pedantic -Wall -Wextra -fpic
gdp: server.out libCommandRead.so libCommandWrite.so

.PHONY: pi
pi: CC=arm-linux-gnueabi-g++
pi: CPPFLAGS=-std=c++11 -pedantic-errors -Wall -Wextra -g -I ../../Downloads/boost_1_62_0
pi: all

server.out: server.o logger.o console.o tcp_server.o reactor.o register.o
	$(CC) ${CPPFLAGS} $^ -o $@ -lboost_system -ldl
	cp server.out ../bin

libCommandRead.so: read_request.o reactor.o register.o
	$(CC) -shared -o $@ read_request.o
	mv libCommandRead.so ../infrastructure/lib/

libCommandWrite.so: write_request.o
	$(CC) -shared -o $@ write_request.o
	mv libCommandWrite.so ../infrastructure/lib/

server.o: server.cpp console.h tcp_server.h ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp  server.hpp write_request.hpp write_request.cpp read_request.cpp read_request.hpp ../infrastructure/reactor/reactor.cpp
	$(CC) -c $(CPPFLAGS) server.cpp -I ../infrastructure/register/ -I ../infrastructure/include/ -I ../infrastructure/reactor -I ../infrastructure/factory -o $@

console.o: console.c console.h ../infrastructure/logger/logger.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp ./base_console.hpp ./dervied_console.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/logger/ -I ../infrastructure/include/ -I ../infrastructure/factory/ -I ../infrastructure/register/ console.c -o $@

read_request.o: read_request.cpp ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/include/common_types.hpp ../infrastructure/register/exception.hpp read_request.hpp 
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ -I ../infrastructure/register read_request.cpp -o $@

tcp_server.o: tcp_server.c tcp_server.h ../../../cpp/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/include/common_types.hpp 
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ tcp_server.c -o $@

logger.o: ../infrastructure/logger/logger.cpp ../infrastructure/logger/logger.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ ../infrastructure/logger/logger.cpp -o $@

write_request.o: write_request.hpp write_request.cpp ../infrastructure/register/exception.hpp
	$(CC) -c $(CPPFLAGS) write_request.cpp -I ../infrastructure/include/ -I ../infrastructure/register/ -o $@

reactor.o: ../infrastructure/register/register.cpp ../infrastructure/include/register_inc.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/reactor/handler.hpp ../infrastructure/include/logger_inc.hpp ../infrastructure/reactor/wrapper_handler_excepation.hpp ../infrastructure/reactor/wrapper_handler_read.hpp ../infrastructure/reactor/wrapper_handler_write.hpp ../infrastructure/reactor/cfunc_call_back.hpp ../infrastructure/reactor/functor_call_back.hpp ../infrastructure/reactor/member_func_call_back.hpp ../infrastructure/include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) ../infrastructure/reactor/reactor.cpp -I ../infrastructure/include/ -o $@

register.o: ../infrastructure/register/register.cpp ../infrastructure/include/register_inc.hpp ../infrastructure/include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ ../infrastructure/register/register.cpp -o $@

.PHONY: clean
clean:
	rm -f *.o *.so *.out block* *.gch
