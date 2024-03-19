CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = logger.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: gdp
gdp: CPPFLAGS += -std=c++98 -g
gdp: all

.PHONY: all
all: a.out
a.out: logger.o test_logger.o
	$(CC) ${CPPFLAGS} $^ -o $@ -lboost_system
logger.o: logger.cpp logger.hpp
	$(CC) -c $(CPPFLAGS) logger.cpp -o $@ 
test_logger.o: test_logger.cpp logger.hpp ~/git/cpp/utils/test.hpp
	$(CC) -c $(CPPFLAGS) -I ~/git/cpp/utils/ test_logger.cpp -o $@ 

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
