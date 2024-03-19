CC=g++
CPPFLAGS=-pedantic -Wall -Wextra
SRCS = stack.cpp test_stack.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: a.out
a.out: test_stack.o string.o
	$(CC) ${CPPFLAGS} $^ -o $@

test_stack.o: test_stack.cpp stack.hpp stack.tpp ../../string/string.hpp 
	$(CC) -c $(CPPFLAGS) test_stack.cpp -I ../../string -o $@ 

string.o: ../../string/string.cpp ../../string/string.hpp
	$(CC) -c $(CPPFLAGS) ../../string/string.cpp -I ../../string -o $@

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
