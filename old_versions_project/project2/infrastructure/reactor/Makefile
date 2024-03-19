CC=g++
CPPFLAGS=-pedantic -Wall -Wextra -fpic
SRCS = $(%.cpp)
OBJS = $(SRCS:.cpp=.o)
SHAREDFLAGS=-shared 

.PHONY: gdp
gdp: CPPFLAGS += -std=c++98 -g
gdp: all

.PHONY: all
all: reactor.out reactor register
reactor.out: reactor.o test_reactor.o register.o logger.o handler.hpp
	$(CC) ${CPPFLAGS} $^ -o $@ -L../lib -lreactor -L../lib -lregister -lboost_system -Wl,-rpath=../lib
	cp reactor.out ../bin

.PHONY: reactor
reactor: libreactor.so
libreactor.so: reactor.o 
	$(CC) ${SHAREDFLAGS} $^ -o $@ -lboost_system
	mv libreactor.so ../lib

.PHONY: register
register: libregister.so
libregister.so: register.o
	$(CC) ${SHAREDFLAGS} $^ -o $@ -lboost_system
	mv libregister.so ../lib
	
reactor.o: ../register/register.cpp ../include/register_inc.hpp reactor.hpp handler.hpp ../include/logger_inc.hpp wrapper_handler_excepation.hpp wrapper_handler_read.hpp wrapper_handler_write.hpp cfunc_call_back.hpp functor_call_back.hpp member_func_call_back.hpp ../include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) reactor.cpp -I ../include/ -o $@

register.o: ../register/register.cpp ../include/register_inc.hpp ../include/call_back_base.hpp
	$(CC) -c $(CPPFLAGS) -I ../include/ ../register/register.cpp -o $@

test_reactor.o: test_reactor.cpp ../include/reactor_inc.hpp ../include/test.hpp handler.hpp ../include/logger_inc.hpp 
	$(CC) -c $(CPPFLAGS) -I ../include/ test_reactor.cpp -o $@

logger.o: ../logger/logger.cpp ../include/logger_inc.hpp
	$(CC) -c $(CPPFLAGS) ../logger/logger.cpp -I ../include -o $@

.PHONY: gc11
gc11: CC += -std=c++11 -Werror
gc11: all

.PHONY: gd11
gd11: CC += -std=c++11 -Werror -g
gd11: all

.PHONY: gdpp
gdpp: CPPFLAGS += -std=c++98 -Werror -g
gdpp: all

.PHONY: gcp
gcp: CPPFLAGS += -std=c++98 -Werror -DNDEBUG -O3
gcp: all

.PHONY: debug
debug:
	echo $(TARGET_LIB)

.PHONY: clean
clean:
	rm -f *.o *.so *.out ../lib/*.so
