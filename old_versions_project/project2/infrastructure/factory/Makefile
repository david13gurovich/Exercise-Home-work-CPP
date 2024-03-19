CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = factory.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: gdp
gdp: CPPFLAGS += -std=c++98 -g
gdp: all
.PHONY: all
all: factory.out

factory.out: test_factory.o logger.o
	$(CC) ${CPPFLAGS} $^ -o $@ -lboost_system

test_factory.o: test_factory.cpp factory.hpp ../include/test.hpp ../reactor/wrapper_handler_excepation.hpp ../reactor/wrapper_handler_write.hpp ../reactor/wrapper_handler_read.hpp ../include/common_types.hpp ../reactor/handler.hpp ../include/call_back_base.hpp ../register/exception.hpp 
	$(CC) -c $(CPPFLAGS) -I ../include/ -I ../reactor/ -I ../register/ test_factory.cpp -o $@

logger.o: ../logger/logger.cpp ../logger/logger.hpp
	$(CC) -c $(CPPFLAGS) -I ../include/ ../logger/logger.cpp -o $@

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
	rm -f *.o