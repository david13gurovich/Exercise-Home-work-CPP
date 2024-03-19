CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = rcstring.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: a.out
a.out: rcstring.o test_rcstring.o
	$(CC) ${CPPFLAGS} $^ -o $@

rcstring.o: rcstring.cpp rcstring.hpp
	$(CC) -c $(CPPFLAGS) rcstring.cpp -o $@

test_rcstring.o: test_rcstring.cpp rcstring.hpp ../utils/test.hpp 
	$(CC) -c $(CPPFLAGS) -I ../utils/ test_rcstring.cpp -o $@

.PHONY: gc11
gc11: CC += -std=c++11 -Werror
gc11: all

.PHONY: gd11
gd11: CC += -std=c++11 -Werror -g
gd11: all

.PHONY: gdp
gdp: CPPFLAGS += -g
gdp: all

.PHONY: gdpp
gdpp: CPPFLAGS += -Werror -g
gdpp: all

.PHONY: gcp
gcp: CPPFLAGS += -Werror -DNDEBUG -O3
gcp: all

.PHONY: debug
debug:
	echo $(TARGET_LIB)

.PHONY: clean
clean:
	rm -f *.o *.d
