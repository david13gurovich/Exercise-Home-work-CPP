CC=arm-linux-gnueabi-g++
CPPFLAGS= -std=c++11 -pedantic-errors -Wall -Wextra -g -I ../../Downloads/boost_1_62_0

.PHONY: all
all: server.out

server.out: server.o logger.o console.o udp_server.o tcp_server.o reactor.o register.o
	$(CC) ${CPPFLAGS} $^ -o $@ -L ../../../Downloads/boost_1_62_0/stage/lib/ -lboost_system

server.o: server.c console.h tcp_server.h udp_server.h ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp
	$(CC) -c $(CPPFLAGS) server.c -I ../infrastructure/register/ -I ../infrastructure/include/ -I ../infrastructure/factory -o $@

console.o: console.c console.h ../infrastructure/logger/logger.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp ./base_console.hpp ./dervied_console.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/logger/ -I ../infrastructure/include/ -I ../infrastructure/factory/ -I ../infrastructure/register/ console.c -o $@

udp_server.o: udp_server.c udp_server.h ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/include/common_types.hpp ../infrastructure/register/exception.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ -I ../infrastructure/register udp_server.c -o $@

tcp_server.o: tcp_server.c tcp_server.h ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/include/common_types.hpp 
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ tcp_server.c -o $@

logger.o: ../infrastructure/logger/logger.cpp ../infrastructure/logger/logger.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ ../infrastructure/logger/logger.cpp -o $@

reactor.o: ../infrastructure/register/register.cpp ../infrastructure/include/register_inc.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/reactor/handler.hpp ../infrastructure/include/logger_inc.hpp ../infrastructure/reactor/wrapper_handler_excepation.hpp ../infrastructure/reactor/wrapper_handler_read.hpp ../infrastructure/reactor/wrapper_handler_write.hpp ../infrastructure/reactor/cfunc_call_back.hpp ../infrastructure/reactor/functor_call_back.hpp ../infrastructure/reactor/member_func_call_back.hpp ../infrastructure/include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) ../infrastructure/reactor/reactor.cpp -I ../infrastructure/include/ -o $@

register.o: ../infrastructure/register/register.cpp ../infrastructure/include/register_inc.hpp ../infrastructure/include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ ../infrastructure/register/register.cpp -o $@

.PHONY: clean
clean:
	rm -f *.o
