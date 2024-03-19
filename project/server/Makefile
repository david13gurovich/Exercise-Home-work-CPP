.PHONY: gdp
gdp: CC=g++ -std=c++11 
gdp: CPPFLAGS = -g -pedantic -Wall -Wextra -fpic
gdp: server.out libCommandRead.so libCommandWrite.so libCommandClock.so

.PHONY: pi
pi: CC=arm-linux-gnueabi-g++
pi: CPPFLAGS=-std=c++11 -pedantic-errors -Wall -Wextra -g -I ../../../../Downloads/boost_1_62_0
pi: all

server.out: server.o console.o tcp_server.o reactor.o register.o so_loader.o dir_monitor.o main.o logger_configurator.o logger.o dispatcher.o compressor.o
	$(CC) ${CPPFLAGS} $^ -o $@ -lboost_system -ldl -L ../../../../Downloads/boost_1_62_0 -lboost_filesystem -L ../../../../Downloads/boost_1_62_0 -L $(HOME)/zlib/lib -lz
	cp server.out ../bin

libCommandRead.so: read_request.o
	$(CC) -shared -o $@ read_request.o
	mv libCommandRead.so ./commands/

libCommandWrite.so: write_request.o
	$(CC) -shared -o $@ write_request.o
	mv libCommandWrite.so ./commands/

libCommandClock.so: clock.o
	$(CC) -shared -o $@ clock.o
	mv libCommandClock.so ./commands/

libLogger.so: logger.o
	$(CC) -shared -o $@ logger.o
	mv libCommandLogger.so ./commands/

server.o: server.cpp console.hpp tcp_server.h ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp  server.hpp write_request.hpp write_request.cpp read_request.cpp read_request.hpp so_loader.hpp so_loader.cpp clock.hpp ./commands/logger_configuration.hpp 
	$(CC) -c $(CPPFLAGS) server.cpp -I ../infrastructure/register/ -I ../infrastructure/include/ -I ../infrastructure/factory -I ./commands/ -o $@

console.o: console.cpp console.hpp ../infrastructure/logger/logger.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp ./base_console.hpp ./dervied_console.hpp call_back_base_dispatcher.hpp ./commands/logger_configuration.cpp 
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/logger/ -I ../infrastructure/include/ -I ../infrastructure/factory/ -I ../infrastructure/register/ -I ./commands/ console.cpp -o $@

read_request.o: read_request.cpp ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/include/common_types.hpp ../infrastructure/register/exception.hpp read_request.hpp ../infrastructure/reactor/reactor.cpp ../infrastructure/factory/factory.hpp
	$(CC) -c $(CPPFLAGS) -fpic -I ../infrastructure/include/ -I ../infrastructure/register read_request.cpp -I ../infrastructure/factory -o $@

tcp_server.o: tcp_server.c tcp_server.h ../../../cpp/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/include/common_types.hpp 
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ tcp_server.c -o $@

logger.o: ../infrastructure/logger/logger.cpp ../infrastructure/logger/logger.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ ../infrastructure/logger/logger.cpp -o $@

write_request.o: write_request.hpp write_request.cpp ../infrastructure/register/exception.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/reactor/reactor.cpp ../infrastructure/factory/factory.hpp ../infrastructure/include/common_types.hpp
	$(CC) -c $(CPPFLAGS) -fpic write_request.cpp -I ../infrastructure/include/ -I ../infrastructure/register/ -I ../infrastructure/factory/ -o $@

reactor.o: ../infrastructure/register/register.cpp ../infrastructure/include/register_inc.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/reactor/handler.hpp ../infrastructure/include/logger_inc.hpp ../infrastructure/reactor/wrapper_handler_excepation.hpp ../infrastructure/reactor/wrapper_handler_read.hpp ../infrastructure/reactor/wrapper_handler_write.hpp ../infrastructure/reactor/cfunc_call_back.hpp ../infrastructure/reactor/functor_call_back.hpp ../infrastructure/reactor/member_func_call_back.hpp ../infrastructure/include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) ../infrastructure/reactor/reactor.cpp -I ../infrastructure/include/ -o $@

register.o: ../infrastructure/register/register.cpp ../infrastructure/include/register_inc.hpp ../infrastructure/include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ ../infrastructure/register/register.cpp -o $@

so_loader.o: so_loader.hpp so_loader.cpp ../infrastructure/logger/logger.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/include/ -I ../infrastructure/factory/ -I ../infrastructure/register/ so_loader.cpp -o $@

clock.o: clock.hpp clock.cpp server.hpp command.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp ../infrastructure/logger/logger.hpp
	$(CC) -c $(CPPFLAGS) -I ../infrastructure/factory/ -I ../infrastructure/include/ -I ../infrastructure/register/ clock.cpp -o $@

dir_monitor.o: dir_monitor.cpp dir_monitor.hpp ../infrastructure/logger/logger.hpp server.hpp server.cpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp dispatcher.hpp dispatcher.cpp ./commands/logger_configuration.hpp 
	$(CC) -c $(CPPFLAGS) -I ./commands/ -I ../infrastructure/include/ -I ../infrastructure/factory/ -I ../infrastructure/register/ dir_monitor.cpp -o $@

main.o: main.cpp console.hpp tcp_server.h ../infrastructure/logger/logger.hpp ../infrastructure/reactor/reactor.hpp ../infrastructure/factory/factory.hpp ../infrastructure/register/exception.hpp  server.hpp dir_monitor.hpp ./commands/logger_configuration.hpp
		$(CC) -c $(CPPFLAGS) main.cpp -I ../infrastructure/register/ -I ../infrastructure/include/ -I ../infrastructure/factory -I ./commands/ -o $@

logger_configurator.o: ./commands/logger_configuration.cpp ./commands/logger_configuration.hpp ../infrastructure/logger/logger.hpp
		$(CC) -c $(CPPFLAGS) ./commands/logger_configuration.cpp -I ../infrastructure/include/ -o $@
	
dispatcher.o: dispatcher.hpp dispatcher.cpp	
		$(CC) -c $(CPPFLAGS) dispatcher.cpp -o $@

compressor.o: compressor.hpp compressor.cpp server.hpp ../infrastructure/include/common_types.hpp
		$(CC) -c $(CPPFLAGS) -I $(HOME)/zlib/include -I ../infrastructure/factory -I ../infrastructure/include -I ../infrastructure/register -I ../infrastructure/include/ compressor.cpp -o $@

.PHONY: clean
clean:
	rm -f *.o *.so *.out block* *.gch ./commands/*.so
